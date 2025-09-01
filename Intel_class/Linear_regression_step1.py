"""
Linear regression(선형 회귀) 구현
"""
from mglearn.datasets import make_wave
import matplotlib.pyplot as plt
import numpy as np
from numpy.random import rand


# 손실함수 정의
def MSE(Ytgt, Ypred):
    """
    Ytgt : 정답 (주어진 결과)
    Ypred : 예측값 (모델함수 결과)
    """
    return np.mean((Ytgt-Ypred)**2)


# 모델함수 정의
def Model_fnc(x, weight, bias):
    return np.matmul(x, weight) + bias


# Linear regression을 위한 함수 정의
def Linear_regression_without_learning(x, Ytgt, n_iter=1000):
    """
    x : 입력 데이터
    y : 출력 데이터 (정답)
    """
    score = []
    param = []
    for i in range(n_iter):
        weight = rand(1)
        bias = rand(1)
        # 모델함수로 부터 결과를 가져오기
        Ypred = Model_fnc(x, weight, bias)
        # 모델함수로 부터 가져온 결과와 y(정답)간 loss계산
        score.append(MSE(Ytgt, Ypred) * 100)
        param.append([weight, bias])
    return score, param


X, Y = make_wave(n_samples=40)

score, param = Linear_regression_without_learning(X, Y)
index = np.argmin(score)
weight, bias = param[index]

Ypred = Model_fnc(X, weight, bias)

plt.figure()
plt.plot(X, Y, 'o')
plt.plot(X, Ypred)
plt.show()
