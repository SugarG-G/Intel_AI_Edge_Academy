import torch
import torch.nn as nn
import torch.optim as optim
import torch.nn.functional as F
from torch.utils.data import DataLoader, Dataset
import torchvision.transforms.v2 as transforms_v2
from torchvision.tv_tensors import BoundingBoxes
from torchvision.datasets import VOCDetection
import torchvision.models as models
import os, shutil
import numpy as np
import matplotlib
matplotlib.use('Agg')  # Non-interactive backend for automatic saving
import matplotlib.pyplot as plt
import matplotlib.patches as patches
from PIL import Image, ImageOps
import kagglehub
import time
import math
import random
from pathlib import Path
from datetime import datetime
import gc
from typing import Dict, List, Tuple, Optional
import warnings
warnings.filterwarnings('ignore')

# ==================== CONFIGURATION MANAGEMENT ====================
class Config:
    """Centralized configuration management"""
    
    # Model Configuration
    NUM_CLASSES = 3
    CLASS_NAMES = ['person', 'cat', 'dog']
    IMG_SIZE = 416
    
    # Training Configuration
    BATCH_SIZE = 16
    NUM_EPOCHS = 30
    LEARNING_RATE = 0.001
    WEIGHT_DECAY = 0.0005
    
    # Progressive Loss Configuration
    LOSS_PHASES = {
        'l1_only': (1, 5),
        'l1_iou': (6, 10),
        'l1_ciou': (11, 20),
        'ciou_dominant': (21, 30)
    }
    
    # Scale Configuration for Multi-scale Detection
    SCALE_RANGES = [
        (0, 80),     # Small objects -> stride 8
        (40, 160),   # Medium objects -> stride 16  
        (80, 416),   # Large objects -> stride 32
    ]
    
    # Detection Configuration
    CONF_THRESHOLD = 0.25
    NMS_THRESHOLD = 0.45
    
    # Visualization Configuration - UPDATED TO 10 SAMPLES
    VIS_SAMPLES = 10  # Changed from 5 to 10
    MAX_SAVED_EPOCHS = 10  # Keep only last 10 epoch images
    
    # System Configuration
    @staticmethod
    def get_num_workers():
        """Get optimal number of workers based on system"""
        if os.name == 'nt':  # Windows
            return 0  # Use single process on Windows to avoid multiprocessing issues
        else:  # Unix-like
            return min(4, os.cpu_count() or 1)

# ==================== DEVICE SETUP ====================
def setup_device():
    """Simple device setup"""
    device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
    print(f"🖥️ Using device: {device}")
    
    if device.type == 'cuda':
        print(f"   GPU: {torch.cuda.get_device_name(0)}")
        
    return device

device = setup_device()

# ==================== YOLOV8 COMPONENTS ====================
class Conv(nn.Module):
    """Standard convolution with BatchNorm and SiLU activation"""
    def __init__(self, c1, c2, k=1, s=1, p=None, g=1):
        super().__init__()
        self.conv = nn.Conv2d(c1, c2, k, s, p or k//2, groups=g, bias=False)
        self.bn = nn.BatchNorm2d(c2)
        self.act = nn.SiLU()
    
    def forward(self, x):
        return self.act(self.bn(self.conv(x)))

class Bottleneck(nn.Module):
    """YOLOv8 Bottleneck with optional shortcut"""
    def __init__(self, c1, c2, shortcut=True, g=1, k=(3, 3), e=0.5):
        super().__init__()
        c_ = int(c2 * e)
        self.cv1 = Conv(c1, c_, k[0], 1)
        self.cv2 = Conv(c_, c2, k[1], 1, g=g)
        self.add = shortcut and c1 == c2
    
    def forward(self, x):
        return x + self.cv2(self.cv1(x)) if self.add else self.cv2(self.cv1(x))

class C2f(nn.Module):
    """YOLOv8's C2f module - Cross Stage Partial with 2 convolutions"""
    def __init__(self, c1, c2, n=1, shortcut=False, g=1, e=0.5):
        super().__init__()
        self.c = int(c2 * e)
        self.cv1 = Conv(c1, 2 * self.c, 1, 1)
        self.cv2 = Conv((2 + n) * self.c, c2, 1)
        self.m = nn.ModuleList(
            Bottleneck(self.c, self.c, shortcut, g, k=(3, 3), e=1.0) for _ in range(n)
        )
    
    def forward(self, x):
        y = list(self.cv1(x).chunk(2, 1))
        y.extend(m(y[-1]) for m in self.m)
        return self.cv2(torch.cat(y, 1))

class SPPF(nn.Module):
    """Spatial Pyramid Pooling - Fast"""
    def __init__(self, c1, c2, k=5):
        super().__init__()
        c_ = c1 // 2
        self.cv1 = Conv(c1, c_, 1, 1)
        self.cv2 = Conv(c_ * 4, c2, 1, 1)
        self.m = nn.MaxPool2d(kernel_size=k, stride=1, padding=k // 2)
    
    def forward(self, x):
        x = self.cv1(x)
        y1 = self.m(x)
        y2 = self.m(y1)
        y3 = self.m(y2)
        return self.cv2(torch.cat((x, y1, y2, y3), 1))

# ==================== YOLOV8 BACKBONE ====================
class YOLOv8Backbone(nn.Module):
    """YOLOv8 Backbone - CSPDarknet style architecture"""
    def __init__(self):
        super().__init__()
        
        # Stem
        self.stem = Conv(3, 64, 3, 2)  # 640 -> 320
        
        # Stage 1
        self.stage1 = nn.Sequential(
            Conv(64, 128, 3, 2),  # 320 -> 160
            C2f(128, 128, n=3, shortcut=True)
        )
        
        # Stage 2  
        self.stage2 = nn.Sequential(
            Conv(128, 256, 3, 2),  # 160 -> 80
            C2f(256, 256, n=6, shortcut=True)
        )
        
        # Stage 3
        self.stage3 = nn.Sequential(
            Conv(256, 512, 3, 2),  # 80 -> 40
            C2f(512, 512, n=6, shortcut=True)
        )
        
        # Stage 4
        self.stage4 = nn.Sequential(
            Conv(512, 1024, 3, 2),  # 40 -> 20
            C2f(1024, 1024, n=3, shortcut=True)
        )
        
        # SPPF
        self.sppf = SPPF(1024, 1024, k=5)
        
        print("   ✅ YOLOv8 Backbone initialized")
        print("   - Channels: [128, 256, 512, 1024]")
        print("   - Strides: [8, 16, 32, 32]")
    
    def forward(self, x):
        """Forward pass returning multi-scale features"""
        x = self.stem(x)
        
        p2 = self.stage1(x)    # 1/8, 128 channels
        p3 = self.stage2(p2)   # 1/16, 256 channels  
        p4 = self.stage3(p3)   # 1/32, 512 channels
        p5 = self.stage4(p4)   # 1/32, 1024 channels
        p5 = self.sppf(p5)
        
        return p2, p3, p4, p5

# ==================== YOLOV8 MODEL WITH NATIVE BACKBONE ====================
class YOLOv8WithNativeBackbone(nn.Module):
    """
    YOLOv8 detector with native YOLOv8 backbone
    """
    def __init__(self, config: Config):
        super().__init__()
        self.config = config
        self.num_classes = config.NUM_CLASSES
        self.img_size = config.IMG_SIZE
        
        print(f"\n📦 Initializing YOLOv8 Model with Native Backbone:")
        print(f"   - Target classes: {self.num_classes} ({', '.join(config.CLASS_NAMES)})")
        print(f"   - Image size: {self.img_size}x{self.img_size}")
        print(f"   - Backbone: Native YOLOv8 CSPDarknet")
        
        # YOLOv8 Backbone
        self.backbone = YOLOv8Backbone()
        
        # Backbone output channels
        self.backbone_channels = [128, 256, 512, 1024]
        
        # Enhanced FPN/PAN Neck
        self._build_neck()
        
        # Detection heads
        self._build_detection_heads()
        
        # Initialize weights
        self._initialize_weights()
        
        # Print model statistics
        self._print_model_stats()
    
    def _build_neck(self):
        """Build enhanced FPN/PAN neck"""
        self.neck = nn.ModuleDict({
            # Upsampling path (FPN)
            'up1': nn.Sequential(
                nn.Upsample(scale_factor=2, mode='nearest'),
                Conv(self.backbone_channels[3], self.backbone_channels[2], 1, 1)
            ),
            'c2f_up1': C2f(self.backbone_channels[2] * 2, self.backbone_channels[2], n=3, shortcut=False),
            
            'up2': nn.Sequential(
                nn.Upsample(scale_factor=2, mode='nearest'),
                Conv(self.backbone_channels[2], self.backbone_channels[1], 1, 1)
            ),
            'c2f_up2': C2f(self.backbone_channels[1] * 2, self.backbone_channels[1], n=3, shortcut=False),
            
            # Downsampling path (PAN)
            'down1': Conv(self.backbone_channels[1], self.backbone_channels[1], k=3, s=2, p=1),
            'c2f_down1': C2f(self.backbone_channels[1] + self.backbone_channels[2], 
                             self.backbone_channels[2], n=3, shortcut=False),
            
            'down2': Conv(self.backbone_channels[2], self.backbone_channels[2], k=3, s=2, p=1),
            'c2f_down2': C2f(self.backbone_channels[2] + self.backbone_channels[3], 
                             self.backbone_channels[3], n=3, shortcut=False)
        })
    
    def _build_detection_heads(self):
        """Build detection heads"""
        head_channels = 256
        
        self.detection_heads = nn.ModuleList([
            self._make_detection_head(self.backbone_channels[1], head_channels),  # P3 - stride 8
            self._make_detection_head(self.backbone_channels[2], head_channels),  # P4 - stride 16
            self._make_detection_head(self.backbone_channels[3], head_channels)   # P5 - stride 32
        ])
        
        self.output_convs = nn.ModuleList([
            nn.Conv2d(head_channels, (self.num_classes + 4 + 1), 1)
            for _ in range(3)
        ])
    
    def _make_detection_head(self, in_channels, out_channels):
        """Create detection head with multiple convolutions"""
        return nn.Sequential(
            Conv(in_channels, out_channels, 3, 1),
            Conv(out_channels, out_channels, 3, 1),
            Conv(out_channels, out_channels, 3, 1)
        )
    
    def _initialize_weights(self):
        """Initialize model weights"""
        # Initialize detection heads
        for head in self.detection_heads:
            for m in head.modules():
                if isinstance(m, nn.Conv2d):
                    nn.init.kaiming_normal_(m.weight, mode='fan_out', nonlinearity='relu')
                    if m.bias is not None:
                        nn.init.constant_(m.bias, 0)
        
        # Initialize output convs with better bias for objectness
        for i, conv in enumerate(self.output_convs):
            if conv.bias is not None:
                # Initialize classification and bbox regression bias to 0
                nn.init.constant_(conv.bias[:self.num_classes], 0)
                nn.init.constant_(conv.bias[self.num_classes:self.num_classes+4], 0)
                # Initialize objectness bias with focal loss prior
                nn.init.constant_(conv.bias[self.num_classes+4], -2.0)
    
    def _print_model_stats(self):
        """Print model statistics"""
        total_params = sum(p.numel() for p in self.parameters())
        trainable_params = sum(p.numel() for p in self.parameters() if p.requires_grad)
        print(f"\n📊 Model Statistics:")
        print(f"   - Total parameters: {total_params:,}")
        print(f"   - Trainable parameters: {trainable_params:,}")
        print(f"   - Memory footprint: ~{total_params * 4 / 1024**2:.1f} MB")
    
    def forward(self, x):
        """Forward pass"""
        # Backbone forward
        p2, p3, p4, p5 = self.backbone(x)
        
        # Neck forward (FPN + PAN)
        # FPN - Upsampling path
        up1 = self.neck['up1'](p5)
        f4 = self.neck['c2f_up1'](torch.cat([up1, p4], 1))
        
        up2 = self.neck['up2'](f4)
        f3 = self.neck['c2f_up2'](torch.cat([up2, p3], 1))
        
        # PAN - Downsampling path
        down1 = self.neck['down1'](f3)
        f4_2 = self.neck['c2f_down1'](torch.cat([down1, f4], 1))
        
        down2 = self.neck['down2'](f4_2)
        f5_2 = self.neck['c2f_down2'](torch.cat([down2, p5], 1))
        
        # Detection heads
        features = [f3, f4_2, f5_2]  # P3, P4, P5
        outputs = []
        
        for i, (feat, head, out_conv) in enumerate(zip(features, self.detection_heads, self.output_convs)):
            x = head(feat)
            x = out_conv(x)
            
            cls = x[:, :self.num_classes]
            bbox = x[:, self.num_classes:self.num_classes+4]
            obj = x[:, self.num_classes+4:self.num_classes+5]
            
            outputs.append({
                'classification': cls,
                'bbox': bbox,
                'objectness': obj,
                'stride': 2 ** (i + 3)  # 8, 16, 32
            })
        
        return outputs

# ==================== IMPROVED DATASET WITH CACHING ====================
class ImprovedVOCPersonCatDogDataset(Dataset):
    """Enhanced VOC Dataset with caching and robust preprocessing"""
    
    def __init__(self, config: Config, image_set='train', augment=True):
        self.config = config
        self.img_size = config.IMG_SIZE
        self.image_set = image_set
        self.augment = augment and (image_set == 'train')
        
        print(f"\n📊 Creating Enhanced {image_set.upper()} Dataset:")
        print(f"   - Image size: {self.img_size}x{self.img_size}")
        print(f"   - Square crop: Based on shorter side")
        print(f"   - Augmentation: {self.augment}")
        
        # Download/load VOC with error handling
        self._load_voc_dataset()
        
        self.classes = {name: idx for idx, name in enumerate(config.CLASS_NAMES)}
        self.num_classes = len(self.classes)
        
        # Cache valid indices
        self._cache_valid_indices()
        
        print(f"   - Valid images: {len(self.valid_idx):,}")
        print(f"   - Classes: {list(self.classes.keys())}")
    
    def _load_voc_dataset(self):
        """Load VOC dataset with enhanced error handling"""
        try:
            voc_path = kagglehub.dataset_download("huanghanchina/pascal-voc-2012")
            
            # Fix directory structure
            voc2012 = os.path.join(voc_path, "VOC2012")
            vocdevkit = os.path.join(voc_path, "VOCdevkit")
            fixed_voc2012 = os.path.join(vocdevkit, "VOC2012")
            
            if os.path.isdir(voc2012) and not os.path.isdir(fixed_voc2012):
                os.makedirs(vocdevkit, exist_ok=True)
                shutil.move(voc2012, fixed_voc2012)
            
            self.voc = VOCDetection(root=voc_path, year='2012', image_set=self.image_set, download=False)
            print(f"   ✅ Loaded VOC2012 {self.image_set} dataset")
            
        except Exception as e:
            print(f"   ❌ Error loading VOC dataset: {e}")
            raise e
    
    def _cache_valid_indices(self):
        """Cache indices of images with target classes"""
        print("   - Caching valid image indices...")
        self.valid_idx = []
        
        for i in range(len(self.voc)):
            try:
                if self._has_target(i):
                    self.valid_idx.append(i)
            except Exception as e:
                print(f"   ⚠️ Warning: Skipping corrupted image {i}: {e}")
                continue
    
    def _has_target(self, idx):
        """Check if image has any target objects"""
        try:
            _, target = self.voc[idx]
            objects = target['annotation'].get('object', [])
            if isinstance(objects, dict):
                objects = [objects]
            
            for obj in objects:
                if obj['name'] in self.classes:
                    return True
            return False
        except:
            return False
    
    def _extract_bboxes_and_classes(self, target):
        """Extract bboxes and class labels with validation"""
        objects = target['annotation'].get('object', [])
        if isinstance(objects, dict):
            objects = [objects]
        
        bboxes = []
        class_labels = []
        
        for obj in objects:
            try:
                name = obj['name']
                if name in self.classes:
                    bbox = obj['bndbox']
                    x1 = max(0, float(bbox['xmin']))
                    y1 = max(0, float(bbox['ymin']))
                    x2 = max(x1 + 1, float(bbox['xmax']))  # Ensure width > 0
                    y2 = max(y1 + 1, float(bbox['ymax']))  # Ensure height > 0
                    
                    # Validate bbox
                    if x2 > x1 and y2 > y1:
                        bboxes.append([x1, y1, x2, y2])
                        class_labels.append(self.classes[name])
            except (KeyError, ValueError, TypeError) as e:
                print(f"   ⚠️ Warning: Invalid bbox data: {e}")
                continue
        
        return bboxes, class_labels
    
    def _square_crop_and_resize(self, image, bboxes, class_labels):
        """Enhanced square cropping with better bbox handling"""
        orig_w, orig_h = image.size
        crop_size = min(orig_w, orig_h)
        
        # Calculate crop position
        if self.augment and crop_size < max(orig_w, orig_h):
            max_x = max(0, orig_w - crop_size)
            max_y = max(0, orig_h - crop_size)
            crop_x = random.randint(0, max_x)
            crop_y = random.randint(0, max_y)
        else:
            crop_x = (orig_w - crop_size) // 2
            crop_y = (orig_h - crop_size) // 2
        
        # Crop image
        image_cropped = image.crop((crop_x, crop_y, crop_x + crop_size, crop_y + crop_size))
        
        # Adjust bboxes
        adjusted_bboxes = []
        adjusted_labels = []
        
        scale_factor = self.img_size / crop_size
        
        for bbox, label in zip(bboxes, class_labels):
            x1, y1, x2, y2 = bbox
            
            # Adjust coordinates relative to crop
            x1_new = max(0, min(crop_size, x1 - crop_x))
            y1_new = max(0, min(crop_size, y1 - crop_y))
            x2_new = max(0, min(crop_size, x2 - crop_x))
            y2_new = max(0, min(crop_size, y2 - crop_y))
            
            # Check if bbox is still valid after cropping
            if x2_new > x1_new and y2_new > y1_new:
                orig_area = (x2 - x1) * (y2 - y1)
                new_area = (x2_new - x1_new) * (y2_new - y1_new)
                
                # Keep bbox if at least 30% of original area remains
                if new_area > 0 and (new_area / orig_area) > 0.3:
                    # Scale to final image size
                    x1_final = x1_new * scale_factor
                    y1_final = y1_new * scale_factor
                    x2_final = x2_new * scale_factor
                    y2_final = y2_new * scale_factor
                    
                    adjusted_bboxes.append([x1_final, y1_final, x2_final, y2_final])
                    adjusted_labels.append(label)
        
        # Resize image
        image_resized = image_cropped.resize((self.img_size, self.img_size), Image.BILINEAR)
        
        return image_resized, adjusted_bboxes, adjusted_labels
    
    def __len__(self):
        return len(self.valid_idx)
    
    def __getitem__(self, idx):
        try:
            real_idx = self.valid_idx[idx]
            image, target = self.voc[real_idx]
            
            # Extract bboxes and labels
            bboxes, class_labels = self._extract_bboxes_and_classes(target)
            
            # Process image and bboxes
            image, bboxes, class_labels = self._square_crop_and_resize(image, bboxes, class_labels)
            
            # Apply augmentations
            if self.augment and len(bboxes) > 0:
                image, bboxes = self._apply_augmentations(image, bboxes)
            
            # Convert to tensor
            transform = transforms_v2.Compose([
                transforms_v2.ToImage(),
                transforms_v2.ToDtype(torch.float32, scale=True),
                transforms_v2.Normalize([0.485, 0.456, 0.406], [0.229, 0.224, 0.225])
            ])
            
            image = transform(image)
            
            # Handle empty bboxes
            if len(bboxes) == 0:
                bboxes = np.zeros((0, 4), dtype=np.float32)
                class_labels = np.array([], dtype=np.int64)
            else:
                bboxes = np.array(bboxes, dtype=np.float32)
                class_labels = np.array(class_labels, dtype=np.int64)
            
            return image, torch.tensor(bboxes, dtype=torch.float32), torch.tensor(class_labels, dtype=torch.long)
            
        except Exception as e:
            print(f"   ⚠️ Warning: Error processing sample {idx}: {e}")
            # Return empty sample
            transform = transforms_v2.Compose([
                transforms_v2.ToImage(),
                transforms_v2.ToDtype(torch.float32, scale=True),
                transforms_v2.Normalize([0.485, 0.456, 0.406], [0.229, 0.224, 0.225])
            ])
            empty_image = transform(Image.new('RGB', (self.img_size, self.img_size), (128, 128, 128)))
            empty_bboxes = torch.zeros((0, 4), dtype=torch.float32)
            empty_labels = torch.zeros((0,), dtype=torch.long)
            return empty_image, empty_bboxes, empty_labels
    
    def _apply_augmentations(self, image, bboxes):
        """Apply data augmentations with bbox adjustment"""
        # Horizontal flip
        if random.random() > 0.5:
            image = image.transpose(Image.FLIP_LEFT_RIGHT)
            for i in range(len(bboxes)):
                x1, y1, x2, y2 = bboxes[i]
                bboxes[i] = [self.img_size - x2, y1, self.img_size - x1, y2]
        
        return image, bboxes

# ==================== ENHANCED LOSS FUNCTIONS ====================
def calculate_iou_stable(pred_boxes, target_boxes):
    """Calculate IoU with numerical stability"""
    eps = 1e-7
    
    # Ensure tensors are on same device and dtype
    pred_boxes = pred_boxes.float()
    target_boxes = target_boxes.float()
    
    x1_inter = torch.max(pred_boxes[:, 0], target_boxes[:, 0])
    y1_inter = torch.max(pred_boxes[:, 1], target_boxes[:, 1])
    x2_inter = torch.min(pred_boxes[:, 2], target_boxes[:, 2])
    y2_inter = torch.min(pred_boxes[:, 3], target_boxes[:, 3])
    
    inter_area = (x2_inter - x1_inter).clamp(min=0) * (y2_inter - y1_inter).clamp(min=0)
    
    pred_area = (pred_boxes[:, 2] - pred_boxes[:, 0]).clamp(min=eps) * \
                (pred_boxes[:, 3] - pred_boxes[:, 1]).clamp(min=eps)
    target_area = (target_boxes[:, 2] - target_boxes[:, 0]).clamp(min=eps) * \
                  (target_boxes[:, 3] - target_boxes[:, 1]).clamp(min=eps)
    
    union_area = pred_area + target_area - inter_area + eps
    iou = inter_area / union_area
    
    return iou.clamp(min=0, max=1)

def calculate_ciou_stable(pred_boxes, target_boxes):
    """Calculate Complete IoU with enhanced numerical stability"""
    eps = 1e-7
    
    # Ensure tensors are on same device and dtype
    pred_boxes = pred_boxes.float()
    target_boxes = target_boxes.float()
    
    # Basic IoU
    iou = calculate_iou_stable(pred_boxes, target_boxes)
    
    # Center coordinates
    pred_cx = (pred_boxes[:, 0] + pred_boxes[:, 2]) / 2
    pred_cy = (pred_boxes[:, 1] + pred_boxes[:, 3]) / 2
    target_cx = (target_boxes[:, 0] + target_boxes[:, 2]) / 2
    target_cy = (target_boxes[:, 1] + target_boxes[:, 3]) / 2
    
    # Center distance squared
    center_dist_sq = (pred_cx - target_cx) ** 2 + (pred_cy - target_cy) ** 2
    
    # Enclosing box diagonal squared
    x1_enclose = torch.min(pred_boxes[:, 0], target_boxes[:, 0])
    y1_enclose = torch.min(pred_boxes[:, 1], target_boxes[:, 1])
    x2_enclose = torch.max(pred_boxes[:, 2], target_boxes[:, 2])
    y2_enclose = torch.max(pred_boxes[:, 3], target_boxes[:, 3])
    
    enclose_diag_sq = ((x2_enclose - x1_enclose) ** 2 + 
                       (y2_enclose - y1_enclose) ** 2).clamp(min=eps)
    
    rho2 = center_dist_sq / enclose_diag_sq
    
    # Aspect ratio consistency
    pred_w = (pred_boxes[:, 2] - pred_boxes[:, 0]).clamp(min=eps)
    pred_h = (pred_boxes[:, 3] - pred_boxes[:, 1]).clamp(min=eps)
    target_w = (target_boxes[:, 2] - target_boxes[:, 0]).clamp(min=eps)
    target_h = (target_boxes[:, 3] - target_boxes[:, 1]).clamp(min=eps)
    
    v = (4 / (math.pi ** 2)) * torch.pow(
        torch.atan(target_w / target_h) - torch.atan(pred_w / pred_h), 2
    )
    
    # Alpha parameter
    with torch.no_grad():
        alpha = v / (1 - iou + v + eps)
    
    ciou = iou - rho2 - alpha * v
    
    # Return loss (1 - ciou) with stability check
    loss = (1 - ciou).clamp(min=0, max=2)
    
    # Handle NaN/Inf values
    if torch.isnan(loss).any() or torch.isinf(loss).any():
        print(f"   ⚠️ Warning: NaN/Inf in CIoU calculation, using fallback")
        return torch.tensor(0.1, device=loss.device, dtype=loss.dtype)
    
    return loss.mean()

class EnhancedProgressiveYOLOv8Loss(nn.Module):
    """Enhanced Progressive YOLOv8 Loss with improved stability and debugging"""
    
    def __init__(self, config: Config):
        super().__init__()
        self.config = config
        self.num_classes = config.NUM_CLASSES
        self.scale_ranges = config.SCALE_RANGES
        
        # Loss functions with improved parameters
        self.bce_cls = nn.BCEWithLogitsLoss(reduction='none')
        self.bce_obj = nn.BCEWithLogitsLoss(reduction='none')
        
        self.current_epoch = 0
        self.debug_mode = True
    
    def set_epoch(self, epoch):
        """Update current epoch for progressive loss"""
        self.current_epoch = epoch
        if epoch > 5:  # Reduce debug output after initial epochs
            self.debug_mode = False
    
    def get_loss_weights(self):
        """Get normalized loss weights based on current epoch"""
        epoch = self.current_epoch
        
        if epoch <= 5:
            # Phase 1: L1 dominant for fast convergence
            weights = {'l1': 0.8, 'iou': 0.2, 'ciou': 0.0}
        elif epoch <= 10:
            # Phase 2: L1 + IoU balanced
            progress = (epoch - 5) / 5
            weights = {'l1': 0.6 - 0.1 * progress, 'iou': 0.3 + 0.1 * progress, 'ciou': 0.1 * progress}
        elif epoch <= 20:
            # Phase 3: Transition to CIoU
            progress = (epoch - 10) / 10
            weights = {'l1': 0.3 * (1 - progress), 'iou': 0.2 * (1 - progress), 'ciou': 0.5 + 0.3 * progress}
        else:
            # Phase 4: CIoU dominant with small L1 component
            weights = {'l1': 0.1, 'iou': 0.1, 'ciou': 0.8}
        
        # Normalize weights to sum to 1.0
        total = sum(weights.values())
        weights = {k: v / total for k, v in weights.items()}
        
        return weights
    
    def should_assign_to_scale(self, bbox_w, bbox_h, scale_idx):
        """Enhanced scale assignment with overlap handling"""
        bbox_size = max(bbox_w, bbox_h)
        min_size, max_size = self.scale_ranges[scale_idx]
        
        # Allow assignment if bbox size is within range
        return min_size <= bbox_size <= max_size
    
    def forward(self, predictions, targets):
        device = predictions[0]['classification'].device
        weights = self.get_loss_weights()
        
        # Debug output for key epochs
        if self.debug_mode and self.current_epoch in [1, 5, 10, 15, 20, 25]:
            print(f"      📊 Loss weights - L1: {weights['l1']:.3f}, "
                  f"IoU: {weights['iou']:.3f}, CIoU: {weights['ciou']:.3f}")
        
        # Initialize loss accumulators
        total_loss = torch.tensor(0.0, device=device)
        cls_loss = torch.tensor(0.0, device=device)
        bbox_loss = torch.tensor(0.0, device=device)
        obj_loss = torch.tensor(0.0, device=device)
        
        num_pos = 0
        scale_stats = {i: 0 for i in range(len(predictions))}
        
        try:
            for scale_idx, pred_dict in enumerate(predictions):
                stride = pred_dict['stride']
                pred_cls = pred_dict['classification']
                pred_bbox = pred_dict['bbox']
                pred_obj = pred_dict['objectness']
                
                batch_size, _, feat_h, feat_w = pred_cls.shape
                
                # Initialize targets
                target_obj = torch.zeros_like(pred_obj, device=device)
                target_cls = torch.zeros_like(pred_cls, device=device)
                target_bbox = torch.zeros_like(pred_bbox, device=device)
                
                pred_boxes_for_loss = []
                target_boxes_for_loss = []
                
                # Process each batch
                for b in range(batch_size):
                    if len(targets[0][b]) == 0:
                        continue
                    
                    bboxes = targets[0][b]
                    labels = targets[1][b]
                    
                    for bbox, label in zip(bboxes, labels):
                        # Skip invalid bboxes
                        if torch.any(torch.isnan(bbox)) or torch.any(torch.isinf(bbox)):
                            continue
                        
                        cx = (bbox[0] + bbox[2]) / 2
                        cy = (bbox[1] + bbox[3]) / 2
                        bbox_w = bbox[2] - bbox[0]
                        bbox_h = bbox[3] - bbox[1]
                        
                        # Skip invalid sizes
                        if bbox_w <= 0 or bbox_h <= 0:
                            continue
                        
                        # Assign to appropriate scale
                        if not self.should_assign_to_scale(bbox_w, bbox_h, scale_idx):
                            continue
                        
                        # Convert to grid coordinates
                        cx_grid = cx / stride
                        cy_grid = cy / stride
                        
                        gx = int(cx_grid.clamp(0, feat_w - 1))
                        gy = int(cy_grid.clamp(0, feat_h - 1))
                        
                        if 0 <= gx < feat_w and 0 <= gy < feat_h:
                            # Set targets
                            target_obj[b, 0, gy, gx] = 1.0
                            target_cls[b, label, gy, gx] = 1.0
                            
                            # Bbox targets (normalized offset and size)
                            target_bbox[b, 0, gy, gx] = (cx_grid - gx).clamp(0, 1)
                            target_bbox[b, 1, gy, gx] = (cy_grid - gy).clamp(0, 1)
                            target_bbox[b, 2, gy, gx] = (bbox_w / stride).clamp(0.1, 4.0)
                            target_bbox[b, 3, gy, gx] = (bbox_h / stride).clamp(0.1, 4.0)
                            
                            # Decode predicted box for IoU calculation
                            pred_cx = (gx + torch.sigmoid(pred_bbox[b, 0, gy, gx])) * stride
                            pred_cy = (gy + torch.sigmoid(pred_bbox[b, 1, gy, gx])) * stride
                            pred_w = torch.sigmoid(pred_bbox[b, 2, gy, gx]) * 4.0 * stride
                            pred_h = torch.sigmoid(pred_bbox[b, 3, gy, gx]) * 4.0 * stride
                            
                            pred_x1 = (pred_cx - pred_w / 2).clamp(0, self.config.IMG_SIZE)
                            pred_y1 = (pred_cy - pred_h / 2).clamp(0, self.config.IMG_SIZE)
                            pred_x2 = (pred_cx + pred_w / 2).clamp(0, self.config.IMG_SIZE)
                            pred_y2 = (pred_cy + pred_h / 2).clamp(0, self.config.IMG_SIZE)
                            
                            pred_boxes_for_loss.append(torch.stack([pred_x1, pred_y1, pred_x2, pred_y2]))
                            target_boxes_for_loss.append(bbox.clamp(0, self.config.IMG_SIZE))
                            
                            num_pos += 1
                            scale_stats[scale_idx] += 1
                
                # Calculate losses for this scale
                # Objectness loss (all samples)
                obj_loss_scale = self.bce_obj(pred_obj, target_obj)
                obj_loss += obj_loss_scale.mean()
                
                # Positive sample losses
                pos_mask = target_obj > 0.5
                
                if pos_mask.sum() > 0:
                    # Classification loss
                    pos_pred_cls = pred_cls[pos_mask.expand_as(pred_cls)].view(-1, self.num_classes)
                    pos_target_cls = target_cls[pos_mask.expand_as(target_cls)].view(-1, self.num_classes)
                    cls_loss_scale = self.bce_cls(pos_pred_cls, pos_target_cls)
                    cls_loss += cls_loss_scale.mean()
                    
                    # Bbox regression losses
                    pos_pred_bbox = pred_bbox[pos_mask.expand_as(pred_bbox)].view(-1, 4)
                    pos_target_bbox = target_bbox[pos_mask.expand_as(target_bbox)].view(-1, 4)
                    
                    # L1 Loss with sigmoid activation
                    pred_bbox_decoded = torch.cat([
                        torch.sigmoid(pos_pred_bbox[:, :2]),  # xy offset
                        torch.sigmoid(pos_pred_bbox[:, 2:]) * 4.0  # wh size
                    ], dim=1)
                    
                    l1_loss = F.l1_loss(pred_bbox_decoded, pos_target_bbox, reduction='mean')
                    
                    # IoU and CIoU losses
                    if len(pred_boxes_for_loss) > 0:
                        pred_boxes_tensor = torch.stack(pred_boxes_for_loss)
                        target_boxes_tensor = torch.stack(target_boxes_for_loss)
                        
                        if weights['iou'] > 0:
                            iou = calculate_iou_stable(pred_boxes_tensor, target_boxes_tensor)
                            iou_loss = (1 - iou).mean()
                        else:
                            iou_loss = torch.tensor(0.0, device=device)
                        
                        if weights['ciou'] > 0:
                            ciou_loss = calculate_ciou_stable(pred_boxes_tensor, target_boxes_tensor)
                        else:
                            ciou_loss = torch.tensor(0.0, device=device)
                    else:
                        iou_loss = torch.tensor(0.0, device=device)
                        ciou_loss = torch.tensor(0.0, device=device)
                    
                    # Combine bbox losses with weights
                    scale_bbox_loss = (weights['l1'] * l1_loss + 
                                     weights['iou'] * iou_loss + 
                                     weights['ciou'] * ciou_loss)
                    bbox_loss += scale_bbox_loss
            
            # Debug output
            if self.debug_mode and (self.current_epoch <= 3 or self.current_epoch % 5 == 0):
                scale_names = ['Small(8)', 'Medium(16)', 'Large(32)']
                for i, count in scale_stats.items():
                    if count > 0:
                        print(f"        Scale {i} {scale_names[i]}: {count} targets")
                print(f"        Total positive samples: {num_pos}")
            
            # Handle edge cases
            if num_pos == 0:
                print(f"        ⚠️ Warning: No positive samples in this batch!")
                return {
                    'total': torch.tensor(0.1, device=device),
                    'cls': torch.tensor(0.0, device=device),
                    'bbox': torch.tensor(0.0, device=device),
                    'obj': obj_loss
                }
            
            # Normalize losses
            cls_loss = cls_loss / max(num_pos, 1)
            bbox_loss = bbox_loss / max(num_pos, 1)
            obj_loss = obj_loss / len(predictions)
            
            # Weighted total loss
            total_loss = obj_loss + cls_loss + 2.0 * bbox_loss
            
            # Check for NaN/Inf
            if torch.isnan(total_loss) or torch.isinf(total_loss):
                print(f"        ❌ NaN/Inf detected in loss! Using fallback values.")
                total_loss = torch.tensor(1.0, device=device)
                cls_loss = torch.tensor(0.1, device=device)
                bbox_loss = torch.tensor(0.1, device=device)
                obj_loss = torch.tensor(0.1, device=device)
            
            return {
                'total': total_loss,
                'cls': cls_loss,
                'bbox': bbox_loss,
                'obj': obj_loss
            }
            
        except Exception as e:
            print(f"        ❌ Error in loss calculation: {e}")
            # Return safe fallback values
            return {
                'total': torch.tensor(1.0, device=device),
                'cls': torch.tensor(0.1, device=device),
                'bbox': torch.tensor(0.1, device=device),
                'obj': torch.tensor(0.1, device=device)
            }

# ==================== ENHANCED DETECTION ====================
def enhanced_detect(model, image, config: Config):
    """Enhanced inference with better post-processing"""
    model.eval()
    
    with torch.no_grad():
        predictions = model(image.unsqueeze(0))
    
    all_boxes = []
    all_scores = []
    all_labels = []
    
    for pred in predictions:
        stride = pred['stride']
        cls_pred = torch.sigmoid(pred['classification'][0])
        bbox_pred = pred['bbox'][0]
        obj_pred = torch.sigmoid(pred['objectness'][0])
        
        h, w = cls_pred.shape[1:]
        
        for y in range(h):
            for x in range(w):
                obj_conf = obj_pred[0, y, x]
                
                if obj_conf > config.CONF_THRESHOLD:
                    cls_scores = cls_pred[:, y, x]
                    cls_id = cls_scores.argmax()
                    cls_conf = cls_scores[cls_id]
                    
                    final_conf = obj_conf * cls_conf
                    
                    if final_conf > config.CONF_THRESHOLD:
                        # Decode bbox
                        cx = (x + torch.sigmoid(bbox_pred[0, y, x])) * stride
                        cy = (y + torch.sigmoid(bbox_pred[1, y, x])) * stride
                        w_box = torch.sigmoid(bbox_pred[2, y, x]) * 4.0 * stride
                        h_box = torch.sigmoid(bbox_pred[3, y, x]) * 4.0 * stride
                        
                        x1 = (cx - w_box / 2).clamp(0, config.IMG_SIZE)
                        y1 = (cy - h_box / 2).clamp(0, config.IMG_SIZE)
                        x2 = (cx + w_box / 2).clamp(0, config.IMG_SIZE)
                        y2 = (cy + h_box / 2).clamp(0, config.IMG_SIZE)
                        
                        # Validate bbox
                        if x2 > x1 and y2 > y1:
                            all_boxes.append([x1.item(), y1.item(), x2.item(), y2.item()])
                            all_scores.append(final_conf.item())
                            all_labels.append(cls_id.item())
    
    # Apply NMS
    if len(all_boxes) > 0:
        from torchvision.ops import nms
        boxes_tensor = torch.tensor(all_boxes)
        scores_tensor = torch.tensor(all_scores)
        labels_tensor = torch.tensor(all_labels)
        
        keep_indices = nms(boxes_tensor, scores_tensor, config.NMS_THRESHOLD)
        
        return boxes_tensor[keep_indices], scores_tensor[keep_indices], labels_tensor[keep_indices]
    
    return torch.tensor([]), torch.tensor([]), torch.tensor([])

# ==================== ENHANCED VISUALIZATION WITH 10 SAMPLES ====================
class VisualizationManager:
    """Manages training visualizations with 10 validation samples and prediction grid display"""
    
    def __init__(self, config: Config, save_dir='training_progress'):
        self.config = config
        self.save_dir = save_dir
        self.max_saved_epochs = config.MAX_SAVED_EPOCHS
        
        os.makedirs(save_dir, exist_ok=True)
        
        # Select fixed validation samples for consistent comparison
        self.fixed_vis_indices = None
    
    def setup_fixed_samples(self, val_dataset):
        """Setup 10 fixed validation samples for consistent visualization"""
        print(f"   📌 Setting up {self.config.VIS_SAMPLES} fixed validation samples...")
        
        # Try to get diverse samples (different classes if possible)
        diverse_samples = []
        class_counts = {i: 0 for i in range(self.config.NUM_CLASSES)}
        
        for i in range(len(val_dataset)):
            try:
                _, _, labels = val_dataset[i]
                if len(labels) > 0:
                    main_class = labels[0].item()
                    # Allow up to 4 samples per class for 10 total samples
                    if class_counts[main_class] < 4:
                        diverse_samples.append(i)
                        class_counts[main_class] += 1
                        
                        if len(diverse_samples) >= self.config.VIS_SAMPLES:
                            break
            except:
                continue
        
        # Fill remaining slots with random samples if needed
        while len(diverse_samples) < self.config.VIS_SAMPLES:
            idx = random.randint(0, len(val_dataset) - 1)
            if idx not in diverse_samples:
                diverse_samples.append(idx)
        
        self.fixed_vis_indices = diverse_samples[:self.config.VIS_SAMPLES]
        print(f"   ✅ Fixed samples selected: {self.fixed_vis_indices}")
    
    def cleanup_old_visualizations(self, current_epoch):
        """Remove old visualization files to save storage"""
        if current_epoch > self.max_saved_epochs:
            old_epoch = current_epoch - self.max_saved_epochs
            old_file = os.path.join(self.save_dir, f'epoch_{old_epoch:03d}.png')
            if os.path.exists(old_file):
                os.remove(old_file)
    
    def draw_prediction_grid(self, ax, image, model, config, alpha=0.1):
        """Draw prediction grid overlay to show where model is looking"""
        try:
            model.eval()
            with torch.no_grad():
                # Get model predictions
                image_tensor = image.to(device)
                predictions = model(image_tensor.unsqueeze(0))
                
                # Process each scale
                for scale_idx, pred in enumerate(predictions):
                    stride = pred['stride']
                    obj_pred = torch.sigmoid(pred['objectness'][0, 0])  # Shape: [H, W]
                    
                    h, w = obj_pred.shape
                    
                    # Create grid
                    for y in range(0, h, max(1, h//20)):  # Sample every few grid points
                        for x in range(0, w, max(1, w//20)):
                            conf = obj_pred[y, x].item()
                            
                            if conf > 0.1:  # Show grid points with some confidence
                                # Convert grid coordinates to image coordinates
                                center_x = (x + 0.5) * stride
                                center_y = (y + 0.5) * stride
                                
                                # Draw grid point with size based on confidence
                                size = max(2, conf * 15)
                                color = 'yellow' if conf > 0.5 else 'orange'
                                
                                circle = plt.Circle((center_x, center_y), size, 
                                                  color=color, alpha=alpha, fill=True)
                                ax.add_patch(circle)
                                
                                # Add small grid square
                                grid_size = stride * 0.8
                                rect = patches.Rectangle(
                                    (center_x - grid_size/2, center_y - grid_size/2), 
                                    grid_size, grid_size,
                                    linewidth=0.5, edgecolor='cyan', 
                                    facecolor='none', alpha=alpha*2
                                )
                                ax.add_patch(rect)
                    
                    # Only show grid for medium scale to avoid clutter
                    if scale_idx == 1:  # Medium scale
                        break
                        
        except Exception as e:
            print(f"      ⚠️ Warning: Could not draw prediction grid: {e}")
    
    def visualize_epoch_results(self, model, val_dataset, epoch):
        """Enhanced epoch visualization with 10 samples and prediction grid"""
        if self.fixed_vis_indices is None:
            self.setup_fixed_samples(val_dataset)
        
        model.eval()
        
        # Create larger figure for 10 samples (5x4 grid)
        fig = plt.figure(figsize=(24, 20))  # Increased size for 10 samples
        
        colors_pred = ['red', 'green', 'blue']
        colors_gt = ['darkred', 'darkgreen', 'darkblue']
        
        detection_stats = {
            'total_gt': 0, 
            'total_pred': 0,
            'class_gt': [0] * self.config.NUM_CLASSES,
            'class_pred': [0] * self.config.NUM_CLASSES
        }
        
        try:
            for plot_idx, data_idx in enumerate(self.fixed_vis_indices, 1):
                image, gt_boxes, gt_labels = val_dataset[data_idx]
                
                # Run detection
                image_tensor = image.to(device)
                with torch.no_grad():
                    pred_boxes, pred_scores, pred_labels = enhanced_detect(model, image_tensor, self.config)
                
                # Update statistics
                detection_stats['total_gt'] += len(gt_boxes)
                detection_stats['total_pred'] += len(pred_boxes)
                
                for label in gt_labels:
                    detection_stats['class_gt'][label.item()] += 1
                for label in pred_labels:
                    detection_stats['class_pred'][label.item()] += 1
                
                # Denormalize image for visualization
                mean = torch.tensor([0.485, 0.456, 0.406]).view(3, 1, 1)
                std = torch.tensor([0.229, 0.224, 0.225]).view(3, 1, 1)
                img_vis = image * std + mean
                img_vis = img_vis.clamp(0, 1).permute(1, 2, 0).numpy()
                
                # Left subplot: Ground Truth
                ax1 = plt.subplot(5, 4, 2*plot_idx - 1)  # 5 rows, 4 columns
                ax1.imshow(img_vis)
                ax1.set_title(f'GT - Sample {plot_idx}', fontsize=10, fontweight='bold')
                ax1.axis('off')
                
                for box, label in zip(gt_boxes, gt_labels):
                    x1, y1, x2, y2 = box
                    rect = patches.Rectangle((x1, y1), x2-x1, y2-y1,
                                            linewidth=2, edgecolor=colors_gt[label],
                                            facecolor='none', linestyle='-')
                    ax1.add_patch(rect)
                    ax1.text(x1, y1-5, f'{self.config.CLASS_NAMES[label]}',
                           color=colors_gt[label], fontsize=8, fontweight='bold',
                           bbox=dict(boxstyle='round,pad=0.3', facecolor='white', alpha=0.7))
                
                # Right subplot: Predictions with Grid
                ax2 = plt.subplot(5, 4, 2*plot_idx)
                ax2.imshow(img_vis)
                ax2.set_title(f'Pred + Grid - Sample {plot_idx}', fontsize=10, fontweight='bold')
                ax2.axis('off')
                
                # Draw prediction grid first (behind predictions)
                self.draw_prediction_grid(ax2, image, model, self.config, alpha=0.15)
                
                # Draw predictions on top
                for box, score, label in zip(pred_boxes, pred_scores, pred_labels):
                    x1, y1, x2, y2 = box
                    rect = patches.Rectangle((x1, y1), x2-x1, y2-y1,
                                            linewidth=2, edgecolor=colors_pred[label],
                                            facecolor='none', linestyle='-')
                    ax2.add_patch(rect)
                    ax2.text(x1, y1-5, f'{self.config.CLASS_NAMES[label]}: {score:.2f}',
                           color=colors_pred[label], fontsize=8, fontweight='bold',
                           bbox=dict(boxstyle='round,pad=0.3', facecolor='white', alpha=0.8))
            
            # Create comprehensive title
            criterion_temp = EnhancedProgressiveYOLOv8Loss(self.config)
            criterion_temp.set_epoch(epoch)
            weights = criterion_temp.get_loss_weights()
            
            class_info = []
            for i, name in enumerate(self.config.CLASS_NAMES):
                class_info.append(f"{name}: GT={detection_stats['class_gt'][i]}, "
                                f"Pred={detection_stats['class_pred'][i]}")
            
            fig.suptitle(f'Epoch {epoch} - YOLOv8 Native Backbone - 10 Fixed Validation Samples\n'
                         f'Loss Weights: L1={weights["l1"]:.2f}, IoU={weights["iou"]:.2f}, CIoU={weights["ciou"]:.2f}\n'
                         f'Total: GT={detection_stats["total_gt"]}, Pred={detection_stats["total_pred"]} | '
                         f'{" | ".join(class_info)}\n'
                         f'Grid: Yellow=High Conf, Orange=Med Conf, Cyan=Detection Grid',
                         fontsize=12, fontweight='bold')
            
            plt.tight_layout()
            
            # Save and cleanup
            save_path = os.path.join(self.save_dir, f'epoch_{epoch:03d}.png')
            plt.savefig(save_path, dpi=150, bbox_inches='tight')  # Higher DPI for better quality
            plt.close()
            
            # Cleanup old files
            self.cleanup_old_visualizations(epoch)
            
            print(f"      📸 10-Sample visualization with prediction grid saved: {save_path}")
            
            return detection_stats
            
        except Exception as e:
            print(f"      ❌ Error in visualization: {e}")
            plt.close('all')
            return {'total_gt': 0, 'total_pred': 0, 'class_gt': [0] * self.config.NUM_CLASSES, 'class_pred': [0] * self.config.NUM_CLASSES}

# ==================== ENHANCED COLLATE FUNCTION ====================
def enhanced_collate_fn(batch):
    """Enhanced collate function with error handling (module level for Windows compatibility)"""
    try:
        images, bboxes, labels = zip(*batch)
        images = torch.stack(images, 0)
        return images, list(bboxes), list(labels)
    except Exception as e:
        print(f"   ⚠️ Warning: Error in collate function: {e}")
        # Return minimal valid batch
        batch_size = len(batch)
        empty_image = torch.zeros((3, Config.IMG_SIZE, Config.IMG_SIZE))
        empty_bbox = torch.zeros((0, 4))
        empty_label = torch.zeros((0,), dtype=torch.long)
        
        return (torch.stack([empty_image] * batch_size),
               [empty_bbox] * batch_size,
               [empty_label] * batch_size)

# ==================== ENHANCED TRAINING WITH EARLY STOPPING ====================
class EarlyStopping:
    """Early stopping to prevent overfitting"""
    
    def __init__(self, patience=7, min_delta=0.001, restore_best_weights=True):
        self.patience = patience
        self.min_delta = min_delta
        self.restore_best_weights = restore_best_weights
        
        self.counter = 0
        self.best_loss = float('inf')
        self.best_epoch = 0
        self.best_model_state = None
    
    def __call__(self, val_loss, model, epoch):
        if val_loss < self.best_loss - self.min_delta:
            self.best_loss = val_loss
            self.best_epoch = epoch
            self.counter = 0
            if self.restore_best_weights:
                self.best_model_state = {k: v.cpu().clone() for k, v in model.state_dict().items()}
            return False
        else:
            self.counter += 1
            if self.counter >= self.patience:
                print(f"\n   🛑 Early stopping triggered after {self.patience} epochs without improvement")
                print(f"   📊 Best validation loss: {self.best_loss:.4f} at epoch {self.best_epoch}")
                
                if self.restore_best_weights and self.best_model_state:
                    print(f"   🔄 Restoring best model weights from epoch {self.best_epoch}")
                    model.load_state_dict({k: v.to(next(model.parameters()).device) 
                                         for k, v in self.best_model_state.items()})
                return True
        return False

def enhanced_train_with_visualization(model, train_loader, val_loader, val_dataset, config: Config):
    """Enhanced training with comprehensive monitoring and early stopping"""
    
    print("\n🏋️ Starting Enhanced Progressive Training with YOLOv8 Native Backbone:")
    print("   📋 Training Features:")
    print("   - Native YOLOv8 CSPDarknet backbone")
    print("   - Progressive loss scheduling (L1 → IoU → CIoU)")
    print("   - Adaptive learning rate with warmup")
    print("   - Early stopping with best model restoration")
    print("   - 10 fixed validation samples for consistent tracking")
    print("   - Prediction grid overlay to visualize model attention")
    print("   - Enhanced error handling and recovery")
    print("   - Cross-platform compatibility (Windows/Linux)")
    
    # Initialize training components
    trainable_params = [p for p in model.parameters() if p.requires_grad]
    optimizer = optim.AdamW(trainable_params, lr=config.LEARNING_RATE, 
                           weight_decay=config.WEIGHT_DECAY, eps=1e-8)
    
    # Learning rate scheduler with warmup
    def get_lr_for_epoch(epoch):
        if epoch <= 3:  # Warmup phase
            return config.LEARNING_RATE * (0.1 + 0.9 * epoch / 3)
        elif epoch <= 10:
            return config.LEARNING_RATE
        elif epoch <= 20:
            return config.LEARNING_RATE * 0.5
        else:
            return config.LEARNING_RATE * 0.1
    
    # Initialize components
    criterion = EnhancedProgressiveYOLOv8Loss(config)
    early_stopping = EarlyStopping(patience=10, min_delta=0.001)
    viz_manager = VisualizationManager(config)
    
    # Training history
    history = {
        'train_loss': [], 'val_loss': [], 'learning_rates': [],
        'detection_stats': []
    }
    
    best_val_loss = float('inf')
    
    # Training loop
    for epoch in range(config.NUM_EPOCHS):
        epoch_start_time = time.time()
        
        # Update learning rate
        new_lr = get_lr_for_epoch(epoch + 1)
        for param_group in optimizer.param_groups:
            param_group['lr'] = new_lr
        
        # Update loss weights
        criterion.set_epoch(epoch + 1)
        
        # Phase transition notifications
        phase_epochs = [1, 6, 11, 21]
        phase_names = ["L1 Dominant", "L1+IoU Balanced", "Transition to CIoU", "CIoU Dominant"]
        if epoch + 1 in phase_epochs:
            phase_idx = phase_epochs.index(epoch + 1)
            print(f"\n{'='*70}")
            print(f"   🔄 PHASE TRANSITION: {phase_names[phase_idx]}")
            print(f"{'='*70}")
        
        print(f"\n{'='*60}")
        print(f"EPOCH {epoch+1}/{config.NUM_EPOCHS} - LR: {new_lr:.6f}")
        print(f"{'='*60}")
        
        # ========== TRAINING PHASE ==========
        model.train()
        train_metrics = {
            'total_loss': 0.0, 'cls_loss': 0.0, 
            'bbox_loss': 0.0, 'obj_loss': 0.0,
            'batch_count': 0, 'successful_batches': 0
        }
        
        for batch_idx, (images, bboxes, labels) in enumerate(train_loader):
            try:
                # Move to device
                images = images.to(device, non_blocking=True)
                bboxes = [b.to(device, non_blocking=True) for b in bboxes]
                labels = [l.to(device, non_blocking=True) for l in labels]
                
                # Skip empty batches
                if all(len(b) == 0 for b in bboxes):
                    continue
                
                optimizer.zero_grad()
                
                # Forward pass
                predictions = model(images)
                losses = criterion(predictions, (bboxes, labels))
                total_loss = losses['total']
                
                # Check for invalid loss
                if torch.isnan(total_loss) or torch.isinf(total_loss):
                    print(f"   ⚠️ Warning: Invalid loss at batch {batch_idx}, skipping...")
                    continue
                
                # Backward pass
                total_loss.backward()
                
                # Gradient clipping
                grad_norm = torch.nn.utils.clip_grad_norm_(trainable_params, max_norm=5.0)
                
                optimizer.step()
                
                # Update metrics
                train_metrics['total_loss'] += total_loss.item()
                train_metrics['cls_loss'] += losses['cls'].item()
                train_metrics['bbox_loss'] += losses['bbox'].item()
                train_metrics['obj_loss'] += losses['obj'].item()
                train_metrics['batch_count'] += 1
                train_metrics['successful_batches'] += 1
                
                # Progress logging
                if batch_idx % 20 == 0:
                    print(f"   Batch [{batch_idx:3d}/{len(train_loader):3d}] "
                          f"Loss: {total_loss.item():.4f} | "
                          f"Cls: {losses['cls'].item():.4f} | "
                          f"Bbox: {losses['bbox'].item():.4f} | "
                          f"Obj: {losses['obj'].item():.4f} | "
                          f"GradNorm: {grad_norm:.2f}")
                
            except Exception as e:
                print(f"   ❌ Error in training batch {batch_idx}: {e}")
                continue
        
        # Calculate training averages
        if train_metrics['successful_batches'] > 0:
            for key in ['total_loss', 'cls_loss', 'bbox_loss', 'obj_loss']:
                train_metrics[key] /= train_metrics['successful_batches']
            
            print(f"\n   📊 Training Summary:")
            print(f"      Loss: {train_metrics['total_loss']:.4f} | "
                  f"Cls: {train_metrics['cls_loss']:.4f} | "
                  f"Bbox: {train_metrics['bbox_loss']:.4f} | "
                  f"Obj: {train_metrics['obj_loss']:.4f}")
            print(f"      Successful batches: {train_metrics['successful_batches']}/{len(train_loader)}")
        
        # ========== VALIDATION PHASE ==========
        model.eval()
        val_metrics = {
            'total_loss': 0.0, 'cls_loss': 0.0,
            'bbox_loss': 0.0, 'obj_loss': 0.0,
            'batch_count': 0
        }
        
        with torch.no_grad():
            for images, bboxes, labels in val_loader:
                try:
                    images = images.to(device, non_blocking=True)
                    bboxes = [b.to(device, non_blocking=True) for b in bboxes]
                    labels = [l.to(device, non_blocking=True) for l in labels]
                    
                    if all(len(b) == 0 for b in bboxes):
                        continue
                    
                    predictions = model(images)
                    losses = criterion(predictions, (bboxes, labels))
                    
                    if not torch.isnan(losses['total']):
                        val_metrics['total_loss'] += losses['total'].item()
                        val_metrics['cls_loss'] += losses['cls'].item()
                        val_metrics['bbox_loss'] += losses['bbox'].item()
                        val_metrics['obj_loss'] += losses['obj'].item()
                        val_metrics['batch_count'] += 1
                
                except Exception as e:
                    print(f"   ⚠️ Warning: Error in validation batch: {e}")
                    continue
        
        # Calculate validation averages
        if val_metrics['batch_count'] > 0:
            for key in ['total_loss', 'cls_loss', 'bbox_loss', 'obj_loss']:
                val_metrics[key] /= val_metrics['batch_count']
            
            print(f"\n   📊 Validation Summary:")
            print(f"      Loss: {val_metrics['total_loss']:.4f} | "
                  f"Cls: {val_metrics['cls_loss']:.4f} | "
                  f"Bbox: {val_metrics['bbox_loss']:.4f} | "
                  f"Obj: {val_metrics['obj_loss']:.4f}")
            
            # Save best model
            if val_metrics['total_loss'] < best_val_loss:
                best_val_loss = val_metrics['total_loss']
                try:
                    torch.save({
                        'epoch': epoch + 1,
                        'model_state_dict': model.state_dict(),
                        'optimizer_state_dict': optimizer.state_dict(),
                        'val_loss': best_val_loss,
                        'config': config.__dict__
                    }, 'best_yolov8_native.pth')
                    print(f"   ✅ Best model saved! Val Loss: {best_val_loss:.4f}")
                except Exception as e:
                    print(f"   ⚠️ Warning: Could not save model: {e}")
            
            # Early stopping check
            if early_stopping(val_metrics['total_loss'], model, epoch + 1):
                break
        
        # ========== VISUALIZATION WITH 10 SAMPLES ==========
        print(f"\n   📸 Generating 10-sample epoch visualization with prediction grid...")
        detection_stats = viz_manager.visualize_epoch_results(model, val_dataset, epoch + 1)
        
        # Update history
        history['train_loss'].append(train_metrics['total_loss'])
        history['val_loss'].append(val_metrics['total_loss'] if val_metrics['batch_count'] > 0 else float('inf'))
        history['learning_rates'].append(new_lr)
        history['detection_stats'].append(detection_stats)
        
        # Epoch timing
        epoch_time = time.time() - epoch_start_time
        print(f"   ⏱️ Epoch completed in {epoch_time:.1f}s")
        
        print(f"   🖼️ Epoch {epoch+1} visualization complete! Moving to next epoch...")
    
    return model, history

# ==================== MAIN EXECUTION ====================
def main():
    """Enhanced main function with comprehensive error handling"""
    print("\n" + "="*70)
    print("🎯 YOLOV8 WITH NATIVE BACKBONE & 10-SAMPLE VISUALIZATION")
    print("   PERSON/CAT/DOG DETECTION - NATIVE YOLOV8 VERSION")
    print("="*70)
    
    try:
        # Initialize configuration
        config = Config()
        
        print(f"\n📋 Configuration Summary:")
        print(f"   - Classes: {config.NUM_CLASSES} ({', '.join(config.CLASS_NAMES)})")
        print(f"   - Image size: {config.IMG_SIZE}x{config.IMG_SIZE}")
        print(f"   - Batch size: {config.BATCH_SIZE}")
        print(f"   - Epochs: {config.NUM_EPOCHS}")
        print(f"   - Learning rate: {config.LEARNING_RATE}")
        print(f"   - Validation samples visualized: {config.VIS_SAMPLES}")
        print(f"   - Workers: {config.get_num_workers()}")
        
        # Create YOLOv8 model with native backbone
        print(f"\n🔧 Creating YOLOv8 Model with Native Backbone...")
        model = YOLOv8WithNativeBackbone(config).to(device)
        
        # Create enhanced datasets
        print(f"\n📚 Loading Enhanced Datasets...")
        train_dataset = ImprovedVOCPersonCatDogDataset(config, 'train', augment=True)
        val_dataset = ImprovedVOCPersonCatDogDataset(config, 'val', augment=False)
        
        # Create enhanced dataloaders
        print(f"\n🔧 Creating Data Loaders...")
        train_loader = DataLoader(
            train_dataset,
            batch_size=config.BATCH_SIZE,
            shuffle=True,
            num_workers=config.get_num_workers(),
            collate_fn=enhanced_collate_fn,
            pin_memory=True if torch.cuda.is_available() else False,
            persistent_workers=True if config.get_num_workers() > 0 else False
        )
        
        val_loader = DataLoader(
            val_dataset,
            batch_size=config.BATCH_SIZE,
            shuffle=False,
            num_workers=config.get_num_workers(),
            collate_fn=enhanced_collate_fn,
            pin_memory=True if torch.cuda.is_available() else False,
            persistent_workers=True if config.get_num_workers() > 0 else False
        )
        
        print(f"\n📊 Dataset Summary:")
        print(f"   - Train samples: {len(train_dataset):,}")
        print(f"   - Val samples: {len(val_dataset):,}")
        print(f"   - Train batches: {len(train_loader):,}")
        print(f"   - Val batches: {len(val_loader):,}")
        
        # Start training
        print(f"\n🚀 Starting Training with Native YOLOv8 Backbone...")
        trained_model, history = enhanced_train_with_visualization(
            model, train_loader, val_loader, val_dataset, config
        )
        
        # Final summary
        print("\n" + "="*70)
        print("✅ YOLOV8 NATIVE BACKBONE TRAINING COMPLETE!")
        print("="*70)
        print("📊 Training Summary:")
        print(f"   - Total epochs: {len(history['train_loss'])}")
        print(f"   - Best validation loss: {min(history['val_loss']) if history['val_loss'] else 'N/A'}")
        print(f"   - Final learning rate: {history['learning_rates'][-1] if history['learning_rates'] else 'N/A'}")
        print("\n📂 Output Files:")
        print("   - Best model: best_yolov8_native.pth")
        print("   - Visualizations: training_progress/ folder")
        print("\n🎯 Features Successfully Applied:")
        print("   ✅ Native YOLOv8 CSPDarknet backbone")
        print("   ✅ Progressive loss scheduling (L1 → IoU → CIoU)")
        print("   ✅ Enhanced error handling and recovery")
        print("   ✅ Early stopping with best model restoration")
        print("   ✅ 10 fixed validation samples for consistent tracking")
        print("   ✅ Prediction grid overlay showing model attention")
        print("   ✅ Comprehensive logging and debugging")
        print("   ✅ Cross-platform compatibility (Windows/Linux)")
        print("   ✅ Automatic epoch progression with image output")
        print("="*70)
        
    except Exception as e:
        print(f"\n❌ Fatal error in main execution: {e}")
        print("   Check system requirements and data availability")
        raise e

if __name__ == "__main__":
    # Windows multiprocessing compatibility
    if os.name == 'nt':
        import multiprocessing
        multiprocessing.set_start_method('spawn', force=True)
    
    main()