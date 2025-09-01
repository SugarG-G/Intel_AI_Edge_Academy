# 필요한 라이브러리 불러오기
import FinanceDataReader as fdr
import numpy as np
# import pandas as pd
import matplotlib.pyplot as plt
import pickle
import torch, torch.nn as nn
from torch.utils.data import TensorDataset, DataLoader

# 범위를 0 ~ 1 로 normalized
def MinMaxScaler(data):
    """최솟값과 최댓값을 이용하여 0 ~ 1 값으로 변환"""
    numerator = data - np.min(data, 0)
    denominator = np.max(data, 0) - np.min(data, 0)
    # 0으로 나누기 에러가 발생하지 않도록 매우 작은 값(1e-7)을 더해서 나눔
    return numerator / (denominator + 1e-7)

# 삼성전자 주식 데이터
df = fdr.DataReader('005930', '2018-05-04', '2020-01-22')
dfx = df[['Open', 'High', 'Low', 'Volume', 'Close']]
dfx = MinMaxScaler(dfx)
dfy = dfx[['Close']]
dfx = dfx[['Open', 'High', 'Low', 'Volume']]


# 두 데이터를 리스트 형태로 저장
x = dfx.values.tolist()  # open, high, low, volume 데이터
y = dfy.values.tolist()  # close 데이터

# 예시:
# 1월 1일 ~ 1월 10일까지의 OHLCV 데이터로 1월 11일 종가(Close) 예측
# 1월 2일 ~ 1월 11일까지의 OHLCV 데이터로 1월 12일 종가(Close) 예측

window_size = 10
data_x = []
data_y = []

for i in range(len(y) - window_size):
    _x = x[i : i + window_size]      # 다음 날 종가(i + window_size)는 포함되지 않음
    _y = y[i + window_size]          # 다음 날 종가
    data_x.append(_x)
    data_y.append(_y)

# 데이터셋 비율 설정
train_size = int(len(data_y) * 0.7)
val_size = int(len(data_y) * 0.2)

# 학습 데이터
train_x = np.array(data_x[0 : train_size])
train_y = np.array(data_y[0 : train_size])

# 검증 데이터
val_x = np.array(data_x[train_size : train_size + val_size])
val_y = np.array(data_y[train_size : train_size + val_size])

# 테스트 데이터
test_size = len(data_y) - train_size - val_size
test_x = np.array(data_x[train_size + val_size : len(data_x)])
test_y = np.array(data_y[train_size + val_size : len(data_y)])

# 출력 확인
print('훈련 데이터의 크기 :', train_x.shape, train_y.shape)
print('검증 데이터의 크기 :', val_x.shape, val_y.shape)
print('테스트 데이터의 크기 :', test_x.shape, test_y.shape)


# numpy → torch
X_tr = torch.tensor(train_x, dtype=torch.float32)   # (N,10,4)
y_tr = torch.tensor(train_y, dtype=torch.float32).view(-1,1)  # (N,1)
X_va = torch.tensor(val_x,   dtype=torch.float32)
y_va = torch.tensor(val_y,   dtype=torch.float32).view(-1,1)
X_te = torch.tensor(test_x,  dtype=torch.float32)
y_te = torch.tensor(test_y,  dtype=torch.float32).view(-1,1)

tr_loader = DataLoader(TensorDataset(X_tr, y_tr), batch_size=30, shuffle=True)
va_loader = DataLoader(TensorDataset(X_va, y_va), batch_size=30)
te_loader = DataLoader(TensorDataset(X_te, y_te), batch_size=30)

device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')

class RNNReg(nn.Module):
    def __init__(self, in_dim=4, hid=20):
        super().__init__()
        self.rnn1 = nn.RNN(in_dim, hid, nonlinearity='tanh', batch_first=True)      # return_sequences=True
        self.do1  = nn.Dropout(0.1)
        self.rnn2 = nn.RNN(hid, hid, nonlinearity='tanh', batch_first=True)         # 마지막 스텝 사용
        self.do2  = nn.Dropout(0.1)
        self.fc   = nn.Linear(hid, 1)

    def forward(self, x):
        x, _ = self.rnn1(x)          # (B,10,20)
        x = self.do1(x)
        x, _ = self.rnn2(x)          # (B,10,20)
        x = x[:, -1, :]              # 마지막 타임스텝
        x = self.do2(x)
        return self.fc(x)            # (B,1)

model = RNNReg().to(device)
crit  = nn.MSELoss()
opt   = torch.optim.Adam(model.parameters(), lr=1e-3)

train_losses, val_losses = [], []

EPOCHS = 70
for ep in range(1, EPOCHS+1):
    # train
    model.train()
    tr_loss = 0.0
    for xb, yb in tr_loader:
        xb, yb = xb.to(device), yb.to(device)
        opt.zero_grad()
        pred = model(xb)
        loss = crit(pred, yb)
        loss.backward()
        nn.utils.clip_grad_norm_(model.parameters(), 1.0)
        opt.step()
        tr_loss += loss.item() * xb.size(0)
    tr_loss /= len(tr_loader.dataset)

    # valid
    model.eval()
    va_loss = 0.0
    with torch.no_grad():
        for xb, yb in va_loader:
            xb, yb = xb.to(device), yb.to(device)
            pred = model(xb)
            va_loss += crit(pred, yb).item() * xb.size(0)
    va_loss /= len(va_loader.dataset)

    train_losses.append(tr_loss)
    val_losses.append(va_loss)

# 손실 곡선 시각화
plt.figure(figsize=(8,4))
plt.plot(train_losses, label='Train Loss')
plt.plot(val_losses, label='Val Loss')
plt.xlabel('Epoch')
plt.ylabel('MSE Loss')
plt.legend()
plt.title('Training vs Validation Loss')
plt.show()


# -----------------------------
# 2. 예측 vs 실제 (테스트셋)
# -----------------------------
model.eval()
with torch.no_grad():
    pred_test = model(X_te.to(device)).cpu().numpy()

plt.figure(figsize=(10,4))
plt.plot(y_te.numpy(), label='Actual')
plt.plot(pred_test, label='Predicted')
plt.xlabel('Time step')
plt.ylabel('Close (normalized)')
plt.legend()
plt.title('Test Prediction vs Actual')
plt.show()