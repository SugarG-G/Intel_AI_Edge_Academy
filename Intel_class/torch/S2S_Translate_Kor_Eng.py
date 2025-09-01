import torch
import torch.nn as nn
import numpy as np
import random
import re
import gc
import unicodedata
from transformers import AutoTokenizer
from torch.utils.data import TensorDataset, DataLoader
from tqdm import tqdm

SOS_token = 0
EOS_token = 1
device = "cuda" if torch.cuda.is_available() else "cpu"

def norm_string(s):
    s = unicode_to_ascii(s.lower().strip())
    s = re.sub(r"([.!?])", r" \1", s)
    s = re.sub(r"[^a-zA-Z가-힣ㄱ-ㅎㅏ-ㅣ!?]+", r" ", s)
    return s.strip()

def unicode_to_ascii(s):
    s = re.sub(r'(?i)cc-by.\*$', '', s)
    hangul_pattern = re.compile('[가-힣ㄱ-ㅎㅏ-ㅣ]')
    result = []
    for c in s:
        if hangul_pattern.match(c):
            result.append(c)
        else:
            for c_ in unicodedata.normalize('NFD', c):
                if unicodedata.category(c_) != 'Mn':
                    result.append(c_)
    return ''.join(result)

def read_language(l1, l2, reverse=False, verbose=False):
    print("Reading languages data...")
    pairs = []
    encode_lang = []
    decode_lang = []
    try:
        with open(f'{l1}2{l2}.txt', encoding='utf-8') as file:
            pf = file.read().strip().split('\n')
        for ll in pf:
            parts = ll.split('\t')
            if len(parts) >= 2:
                l1_lang = norm_string(parts[0])
                l2_lang = norm_string(parts[1])
                if reverse:
                    pairs.append([l2_lang, l1_lang])
                    encode_lang.append(l2_lang)
                    decode_lang.append(l1_lang)
                else:
                    pairs.append([l1_lang, l2_lang])
                    encode_lang.append(l1_lang)
                    decode_lang.append(l2_lang)
        if verbose:
            print(pairs)
        return encode_lang, decode_lang, pairs
    except FileNotFoundError:
        raise FileNotFoundError(f"File '{l1}2{l2}.txt' not found.")

# 데이터 읽기
lang_input, lang_output, pairs = read_language('ENG', 'KOR', reverse=False, verbose=False)

# 토크나이저 로드 (올바른 모델 이름 사용; 필요 시 en-ko로 변경)
tokenizer = AutoTokenizer.from_pretrained("Helsinki-NLP/opus-mt-ko-en")

# 토큰화 (패딩과 truncation 명시적으로 설정)
encoded_input = tokenizer(
    lang_input,
    padding="longest",  # 배치 내 가장 긴 시퀀스에 맞춤
    truncation=True,
    max_length=512,     # 모델의 최대 길이 (필요 시 조정)
    return_tensors="pt"
)
decoded_input = tokenizer(
    lang_output,
    padding="longest",
    truncation=True,
    max_length=512,
    return_tensors="pt"
)

input_ids = encoded_input["input_ids"].to(device)
target_ids = decoded_input["input_ids"].to(device)

# 텐서 모양 확인 (디버깅용)
print(f"Input IDs shape: {input_ids.shape}")
print(f"Target IDs shape: {target_ids.shape}")

# 데이터셋과 로더 생성
dataset = TensorDataset(input_ids, target_ids)
loader = DataLoader(dataset, batch_size=32, shuffle=True)

class Encoder(nn.Module):
    def __init__(self, # moduleSelect = int,
                  vocab_size : int, embed_size : int, hidden_size, dropout = 0.1):
        super().__init__()

        self.hidden_size = hidden_size
        self.embedding = nn.Embedding(vocab_size, embed_size, padding_idx=tokenizer.pad_token_id)
        self.GRU = nn.GRU(embed_size, hidden_size, batch_first=True)

    def forward(self, input):
        embedded = self.embedding(input)
        output, hidden = self.GRU(embedded)
        return output, hidden
    
class Decoder(nn.Module):
    def __init__(self, vocab_size: int, embed_size: int, hidden_size: int, max_length=20, device='cuda'):
        super().__init__()
        self.hidden_size = hidden_size
        self.embedding = nn.Embedding(vocab_size, embed_size, padding_idx=tokenizer.pad_token_id)
        self.GRU = nn.GRU(embed_size, hidden_size, batch_first=True)
        self.out = nn.Linear(hidden_size, vocab_size)
        self.max_len = max_length
        self.device = device
        self.to(device)


    def forward(self, encoder_outputs, encoder_hidden, target_tensor=None,
    teacher_forcing_ratio=0.5):
        """
        encoder_outputs: (batch, src_len, Hidden)
        encoder_hidden: (1, batch, Hidden)
        target_tensor:
        (batch, tgt_len)
        """ 
        top1 = None
        batch_size = encoder_outputs.size(0)
        if target_tensor is not None:
            tgt_len = target_tensor.size(1) # sentance_length
        else:
            tgt_len = self.max_len
        vocab_size = self.out.out_features
        # <SOS>
        decoder_input = torch.full((batch_size,1), SOS_token, dtype=torch.long).to(self.device)
        decoder_hidden = encoder_hidden.to(self.device)
        # output : (batch, sentance_len, Hidden)
        outputs = torch.zeros(batch_size, tgt_len, vocab_size, device=self.device)
        # sentance 길이만큼 반복해야 함.
        for sent_idx in range(tgt_len):
            sel_tok, decoder_hidden = self.forward_1_step(decoder_input, decoder_hidden, encoder_outputs)
            # 저장.
            outputs[:, sent_idx, :] = sel_tok.squeeze(1)
            # 다음 입력 처리
            # teacher forcing을 통해 정답을 넣을지 예측을 넣을지 정함.
            if (target_tensor is not None and random.random() < teacher_forcing_ratio):
            # 정답 입력
                decoder_input = target_tensor[:, sent_idx].unsqueeze(1)
            else:
            #예측 입력
                top1 = sel_tok.argmax(dim=2)
                decoder_input = top1
            
        return outputs
    
    def forward_1_step(self, input_word, hidden, hidden_from_encoder):
        embedded_input_word = self.embedding(input_word)
        output, hidden = self.GRU(embedded_input_word, hidden)  # hidden 업데이트됨
        logits = self.out(output)
        return logits, hidden  # hidden state도 반환
    
def save_checkpoint(encoder, decoder, optimizer, epoch, path = "check_point.pth"):
    torch.save({
    'epoch': epoch,
    'encoder_state_dict': encoder.state_dict(),
    'decoder_state_dict': decoder.state_dict(),
    'optimizer_state_dict': optimizer.state_dict()
    }, path)
    print(f"Checkpoint saved to {path}")


# Layer의 크기 선언.
embed_size = 4
hidden_size = 4
src_vocab = tokenizer.vocab_size
tgt_vocab = tokenizer.vocab_size
encoder = Encoder(src_vocab, embed_size, hidden_size).to(device)
decoder = Decoder(tgt_vocab, embed_size, hidden_size,
max_length=target_ids.size(1), device=device).to(device)
optimizer = torch.optim.Adam(list(encoder.parameters()) + list(decoder.parameters()), lr=1e-3)
criterion = nn.CrossEntropyLoss(ignore_index=-100)


num_epochs = 50
for epoch in range(1, num_epochs+1):
    encoder.train(); decoder.train()
    total_loss = 0
    loop = tqdm(loader, desc=f"Epoch {epoch}/{num_epochs}", unit="batch")
    for src_ids, tgt_ids in loop:
        src_ids, tgt_ids = src_ids.to(device), tgt_ids.to(device)
        optimizer.zero_grad()
        
        # Forward pass
        enc_outs, enc_hidden = encoder(src_ids)
        dec_outputs = decoder(enc_outs, enc_hidden, target_tensor=tgt_ids)
        
        # 벡터화된 loss 계산 (훨씬 빠름)
        # dec_outputs: (batch, seq_len, vocab_size)
        # tgt_ids: (batch, seq_len)
        dec_outputs_flat = dec_outputs.view(-1, dec_outputs.size(-1))
        tgt_ids_flat = tgt_ids.view(-1)
        batch_loss = criterion(dec_outputs_flat, tgt_ids_flat)
        
        # Backward pass
        batch_loss.backward()
        optimizer.step()
        
        total_loss += batch_loss.item()
        loop.set_postfix(loss=batch_loss.item())

    avg_loss = total_loss / len(loader)
    print(f"Epoch {epoch:2d} Loss: {total_loss:.4f}")


