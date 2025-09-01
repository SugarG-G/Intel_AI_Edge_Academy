"""
Linear regression(선형 회귀) + gradient 구현
"""
from mglearn.datasets import make_wave
import matplotlib.pyplot as plt
import numpy as np
from numpy.random import rand


class Linear_regression():
    def __init__(self, Y, X, lr=0.01, n_iter=10000):
        self.Y = Y
        self.X = X
        self.lr = lr
        self.iter = n_iter
        self.weight = rand(1)
        self.bias = rand(1)
        self.history = []

        self.model = self.Model_fnc

    def Model_fnc(self, x, weight, bias):
        return np.matmul(x, weight) + bias

    def mse(self, Ytgt, Ypred):
        return np.mean((Ytgt - Ypred)**2)

    def grad_f(self, loss_prev, loss_curr, h):
        return (loss_curr - loss_prev) / h

    def forward(self, weight, bias):
        y_pred = self.model(self.X, weight, bias)
        loss = self.mse(self.Y, y_pred)
        return y_pred, loss

    def backward(self, loss_curr):
        h = 1e-9

        _, loss_dw = self.forward(self.weight+h, self.bias)
        grad_weight = self.grad_f(loss_curr, loss_dw, h)

        _, loss_db = self.forward(self.weight, self.bias+h)
        grad_bias = self.grad_f(loss_curr, loss_db, h)

        self.weight = self.weight - self.lr * grad_weight
        self.bias = self.bias - self.lr * grad_bias

    def fit(self, verbose=True):
        for i in range(1, self.iter):
            _, loss = self.forward(self.weight, self.bias)
            self.history.append([loss, self.weight, self.bias])
            self.backward(loss)
            # if abs(self.dw) < 1e-9 and abs(self.db) < 1e-9:
            #     break
        return self.history


X, Y = make_wave(n_samples=40)

clr = Linear_regression(Y, X)
history = clr.fit()

loss = [h[0] for h in history]
weight = np.array([h[1] for h in history])
bias = np.array([h[2] for h in history])
# Ypred = np.matmul(X, weight[0]) + bias[0]
Ypred = clr.Model_fnc(X, weight[0], bias[0])
# Ypred_10000 = np.matmul(X, weight[9998]) + bias[9998]
Ypred_10000 = clr.Model_fnc(X, weight[9998], bias[9998])

# print(type(loss[0]))
plt.figure()
plt.plot(X, Y, 'o')
plt.plot(X, Ypred)
plt.plot(X, Ypred_10000)
plt.legend([
        "Target",
        "loss : " + "{:.3f}".format(loss[0]),
        "loss : " + "{:.3f}".format(loss[9998])
    ])
plt.show()
