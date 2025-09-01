# -*- coding: utf-8 -*-
import numpy as np
from sklearn.datasets import fetch_openml
from sklearn.model_selection import train_test_split
from tqdm import tqdm
import matplotlib.pyplot as plt
import scipy as sp

from types import SimpleNamespace

mnist = fetch_openml('mnist_784')
image = mnist.data.astype(np.float32)
label = mnist.target.astype(np.int64)

# TODO 데이터셋 분배
image_train, image_test, label_train, label_test = train_test_split(
    image, label,
    test_size=10000,       
    stratify=label,        
    random_state=42
)

def one_hot(labels, n_classes=10):
    m = labels.shape[0]
    oh = np.zeros((m, n_classes), dtype=np.float32)
    oh[np.arange(m), labels] = 1.0
    return oh
# TODO 데이터를 이미지 형태로 변경
image_train = np.array(image_train).reshape(-1, 28, 28) 
image_test  = np.array(image_test).reshape(-1, 28, 28)
label_train = one_hot(label_train, n_classes=10)
label_test  = one_hot(label_test , n_classes=10)
print("image_train : ", image_train.shape, "| image_test : ",image_test.shape, "| label_train : ",label_train.shape, "| label_test : ", label_test.shape)
image_train, image_test = image_train/255, image_test/255

# TODO 이미지 plot
# plt.figure()
# for i in range(12):
#     plt.subplot(3,4, i+1)
#     plt.imshow(image_train[i], cmap='gray')
#     plt.title(np.argmax(label_train[i]))
# plt.show()

class ANN:
    # 학습시킬 파라미터는? weight: (input_dim x output_dim) , bias : output_dim --> add_ann_layer
    # 입력한 Layer를 통해 학습할 파라미터를 구할수 있음.
    # 그렇다면 layer가 얼마나 쌓였는지 저장을 해둬야 함.

    def __init__(self):
        self.layers = []
        self.Ytgt = []
        self.Ypred = []
        # name, parameter

        self.input_data = 0   # X
        self.input_target = 0 # Y
        self.input_dims = 0   # Z
        self.n, self.w, self.h = 0, 0, 0
        self.Batch = 0
        self.__layernum = 0

        # backpropagation 을 위한 캐시메모리
        self.cache = []  #

        self.lr = 1e-3
        pass
    
    # TODO 레이어 출력 코드 작성.
    def show(self):
        for i in range(len(self.layers)):
            if self.layers[i].property == 'param':
                print(
                    self.layers[i].name,
                    '\t weight :', self.layers[i].params[f'w{i}'].shape,
                    '\t bias :', self.layers[i].params[f'b{i}'].shape
                )   
            else:
                print(self.layers[i].name)
        pass

    # TODO 입력한 layer의 차원을 저장하기 위한 함수 정의.
    def __add_layer(self, name, dim):
        # activation --> (name, 0)
        layer = SimpleNamespace()        
        # activation
        layer.name = name
        layer.dim = dim
        if layer.name == "flatten":
            layer.property = "function"
        elif dim == 0:
            layer.property = 'activation'
            layer.params = {'act':name}
        else:
            # parameters
            layer.property = 'param'
            layer.params = dict()
            layer.grads = dict()
        # self.layers[i].param & grads
        # self.layers[i].property
        # self.layers[i].name
        # self.layers[i].property
        self.layers.append(layer)
        

    # TODO 파라미터를 저장할 변수는? layer_dims로부터 변수 초기화.
    def __param_init(self):
        #layer의 순서는 i로하고, 파라미터는 하기와 같이 딕셔너리형태로 저장됨.
        # {w1 : (input_dims, output_dims), b1 : (1, output_dims) ....  }
        input_dims = self.input_data.reshape(self.input_data.shape[0], -1).shape[1] 
        nn = len(self.layers)
        for i in range(nn):
            if self.layers[i].property == 'param':
                output_dims = self.layers[i].dim
                self.layers[i].params[f'w{i}'] = np.random.uniform(-1, 1, (input_dims, output_dims))
                self.layers[i].params[f'b{i}'] = np.zeros((1, output_dims))
                self.layers[i].grads[f'w{i}'] = np.zeros((input_dims, output_dims))
                self.layers[i].grads[f'b{i}'] = np.zeros((1, output_dims))
                input_dims = output_dims
                pass
            elif self.layers[i].property=='function' :

                _, input_dims = self.__Flatten(self.input_data)
                continue
            elif self.layers[i].property == 'activation':
                continue

            # TODO layers에 저장할 param & grads 공간 확보.

            #self.layers[i].grad_params[f'b{i}'] =  np.zeros((1, output_dims))
            input_dims = output_dims
        pass

    def __Flatten(self, input):
        output = input.reshape(input.shape[0], -1)
        output_dims = output.shape[1]
        return output, output_dims

    def __Adam(self):
        pass

    def __categorical_cross_entropy(self, Ytgt, Ypred): # Loss는 이거 적용.
        # log (0)을 막기 위해 clip 추가
        Ypred = np.clip(Ypred, 1e-15, 1-1e-15)
        m = Ytgt.shape[0]
        return -np.sum(Ytgt * np.log(Ypred)) / m

    def batchnorm(self):
        pass

    def __sigmoid(self, input):
        output = sp.special.expit(input)
        return output

    def __relu(self, input):
        # relu 구현
        return np.maximum(0, input)

    def __softmax(self, input):
        # softmax 함수 구현.
        exp_input = np.exp(input)
        return exp_input / np.sum(exp_input, axis=1, keepdims=True)
    
    def __add_activation_layer(self, name):
        # TODO activation 레이어에 대해 __add_layer 수행.
        self.__add_layer(name, 0)
        pass

    def __forward(self):
        # TODO mnist 데이터 개수 (60000)에 대해 계산 필요.
        _X = np.array(self.input_data)
        self.cache = [] # iteration 마다 캐시 초기화
        for i in range(0, len(self.layers)):
            # TODO Layer별 Affine, activation 연산
            if self.layers[i].property == 'param':
                ypred = np.matmul(_X, self.layers[i].params[f'w{i}']) + self.layers[i].params[f'b{i}']
                self.cache.append(ypred)
                _X = ypred
            elif self.layers[i].property == 'function': # flatten
                _X, _ = self.__Flatten(_X)
                self.cache.append(_X)
            elif self.layers[i].property == 'activation':
                if self.layers[i].name == 'relu':
                    ypred = self.__relu(_X)
                elif self.layers[i].name == 'softmax':
                    ypred = self.__softmax(_X)
                print(self.layers[i].name) 
                self.cache.append(_X)
                _X = ypred
    
        return ypred 
    
    def __backward(self, loss):
        # backward + softmax
        m = self.Ytgt.shape[0]
        dA = self.cache[len(self.cache) - 1] - self.Ytgt
        dZ = dA
        for i in reversed(range(0, len(self.layers) - 1)):
            if self.layers[i].property == "activation":
                dZ = self.__backward_activation(dA, self.cache[i], self.layers[i].name)
            elif self.layers[i].property == "param":
                d_param_weight = np.matmul(self.cache[i-1].T, dZ)/m
                d_param_bias = np.mean(dZ, axis=0, keepdims=True)
                
                w = self.layers[i].params[f'w{i}']
                d_actvation = np.matmul(dZ, w.T)
                self.layers[i].grads[f'w{i}'] = d_param_weight
                self.layers[i].grads[f'b{i}'] = d_param_bias

    def __backward_activation(self, dA, Z, name):
        if name == "relu":
            dZ = dA.copy()
            dZ[Z<=0] = 0
            return dZ
        
    def __update_params(self):
        lr = self.lr
        num_layer = len(self.layers)
        for i in range(num_layer):
            if self.layers[i].property == 'param':
                self.layers[i].params[f'w{i}'] = self.layers[i].params[f'w{i}'] - lr * self.layers[i].grads[f'w{i}']
                self.layers[i].params[f'b{i}'] = self.layers[i].params[f'b{i}'] - lr * self.layers[i].grads[f'b{i}']
    
## TODO: activation 및 ANN 레이어를 쌓기 위한 정보 입력.
    def Flatten(self):
        self.__add_layer('flatten', 0)

    def add_ann_layer(self, dims):
        self.__add_layer('ANN layers', dims)

    def sigmoid(self):
        self.__add_activation_layer('sigmoid')
        pass

    def relu(self):
        self.__add_activation_layer('relu')
        pass     

    def softmax(self):
        self.__add_activation_layer('softmax')
        pass

    def compile(self):
        self.__param_init()
        # self.param_init = False        
        pass

    def Input(self, size):
        Batch, width, height = size
        self.input_data = np.zeros((Batch, width, height))
        # TODO 입력 데이터의 형태를 받아오고, 해당 데이터 형으로 채우진 매트릭스를 생성 후 self.input_data에 입력.
        pass

    def run(self, X, Y, batchsize = 32):
        # TODO 실재 코드가 돌아가야 하는 부분으로, 위에 기록된 함수들에 저장된 정보를 통해 학습시킬 파라미터들을 선언
        self.input_data = X
        self.Ytgt = Y
        self.Batch = batchsize

        loss_score = []
        
        page = tqdm(range(0, len(X), batchsize))
        for i in page:
            self.input_data = X[i:i+batchsize]
            self.Ytgt = Y[i:i+batchsize]
            
            ypred = self.__forward()
            loss = self.__categorical_cross_entropy(self.Ytgt, ypred)

            self.__backward(loss)
            self.__update_params()
            loss_score.append(loss)
            page.mininterval = 0.5
            page.set_description(f'loss : {loss:.3f}')
        return np.min(loss_score)

# TODO ANN 클래스 선언 (중간까지 작성후 기능들이 원하는 대로 동작하는지 확인이 필요).
test_ANN=ANN()

# TODO 우선 layer를 쌓은 후
test_ANN.Input(size=image_train.shape)
test_ANN.Flatten()
test_ANN.add_ann_layer(128)
test_ANN.relu()
test_ANN.add_ann_layer(10)
test_ANN.softmax()

# TODO 학습 시킬 데이터를 입력
test_ANN.compile()

# TODO 원하는 대로 Layer가 쌓였는지를 확인.
test_ANN.show()

# TODO ANN Mnist 학습루프 설정.
test_ANN.run(X=image_train, Y=label_train)