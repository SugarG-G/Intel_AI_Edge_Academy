"""
Logistic_regression 구현
"""
import mglearn.datasets
import matplotlib.pyplot as plt
import numpy as np
import scipy as sp
from matplotlib.lines import Line2D
from numpy.random import rand

X, Y = mglearn.datasets.make_forge()
mglearn.discrete_scatter(X[:, 0], X[:, 1], Y)
plt.legend(["Class  0", "Class 1"], loc=4)
plt.show()


def Model_fnc(X, weight, bias):
    Z = np.matmul(X, weight) + bias
    return sp.special.expit(Z)


class Logistic_regression():
    def __init__(self, Y, X, lr=0.1, n_iter=10000):
        self.Y = Y
        self.X = X
        self.lr = lr
        self.iter = n_iter
        self.weight = rand(2)
        self.bias = rand(1)
        self.history = []

        self.prev_weight = self.weight + 1e-3
        self.prev_bias = self.bias + 1e-3
        self.db = 1e9
        self.dw = 1e9 * np.ones((2, 1))
        self.loss_prev = 1e9

        self.model = Model_fnc

    def binary_cross_entropy(self, Ytgt, Ypred):
        Ypred = np.clip(Ypred, 0, 1)
        return -np.mean(Ytgt*np.log(Ypred)+(1-Ytgt)*np.log(1-Ypred))

    def grad_f(self, loss_prev, loss_curr, h):
        return (loss_curr - loss_prev) / -h

    def forward(self, weight, bias):
        y_pred = self.model(self.X, weight, bias)
        loss = self.binary_cross_entropy(self.Y, y_pred)
        return y_pred, loss

    def backward(self, loss_curr):
        h = 1e-4

        _, loss_dw0 = self.forward(self.weight + np.array([h, 0]), self.bias)
        _, loss_dw1 = self.forward(self.weight + np.array([0, h]), self.bias)
        grad_w0 = self.grad_f(loss_dw0, loss_curr, h)
        grad_w1 = self.grad_f(loss_dw1, loss_curr, h)

        grad_w = np.array([np.mean(grad_w0), np.mean(grad_w1)])

        _, loss_db = self.forward(self.weight, self.bias+h)
        grad_d = np.mean(self.grad_f(loss_db, loss_curr, h))

        self.loss_prev = loss_curr
        self.prev_weight = self.weight
        self.prev_bias = self.bias

        self.weight = self.weight - self.lr * grad_w
        self.bias = self.bias - self.lr * grad_d

    def fit(self, verbose=True):
        for i in range(1, self.iter):
            _, loss = self.forward(self.weight, self.bias)
            self.history.append([loss, self.weight, self.bias])
            self.backward(loss)
            # if abs(self.dw) < 1e-9 and abs(self.db) < 1e-9:
            #     break
        return self.history


# linear dataset
# X, Y = make_wave(n_samples=40)
# clr = Linear_regression(Y, X)
# history = clr.fit()

# loss = [h[0] for h in history]
# weight = np.array([h[1] for h in history])
# bias = np.array([h[2] for h in history])
# # Ypred = np.matmul(X, weight[0]) + bias[0]
# Ypred = clr.Model_fnc(X, weight[0], bias[0])
# # Ypred_10000 = np.matmul(X, weight[9998]) + bias[9998]
# Ypred_10000 = clr.Model_fnc(X, weight[9998], bias[9998])

# # print(type(loss[0]))
# plt.figure()
# plt.plot(X, Y, 'o')
# plt.plot(X, Ypred)
# plt.plot(X, Ypred_10000)
# plt.levels([
#         "Target",
#         "loss : " + "{:.3f}".format(loss[0]),
#         "loss : " + "{:.3f}".format(loss[9998])
#     ])
# plt.show()
clr = Logistic_regression(Y, X)
history = clr.fit()

loss = [h[0] for h in history]
# print(loss)
weight = np.array([h[1] for h in history])
bias = np.array([h[2] for h in history])

loss_ini = loss[3]
loss_mid = loss[500]
loss_ter = loss[-1]

# 좌표 평면 생성 (시작점, 끝점)
x_min, x_max = X[:, 0].min() - 0.5, X[:, 0].max() + 0.5
y_min, y_max = X[:, 1].min() - 0.5, X[:, 1].max() + 0.5
xx = np.linspace(x_min, x_max, 200)
yy = np.linspace(y_min, y_max, 200)
XX, YY = np.meshgrid(xx, yy)
grid = np.c_[XX.ravel(), YY.ravel()]

Z_init = Model_fnc(grid, weight[3], bias[3]).reshape(XX.shape)
Z_mid = Model_fnc(grid, weight[500], bias[500]).reshape(XX.shape)
Z_ter = Model_fnc(grid, weight[-1], bias[-1]).reshape(XX.shape)

plt.figure()
mglearn.discrete_scatter(X[:, 0], X[:, 1], Y)

c1 = plt.contour(XX, YY, Z_init, levels=[0.5], colors='green', linestyles='--')
c2 = plt.contour(XX, YY, Z_mid, levels=[0.5], colors='blue', linestyles='--')
c2 = plt.contour(XX, YY, Z_ter, levels=[0.5], colors='red', linestyles='-')

proxy_init = Line2D([0], [0], color='green', linestyle='--', linewidth=2)
proxy_mid = Line2D([0], [0], color='blue',  linestyle='--', linewidth=2)
proxy_final = Line2D([0], [0], color='red', linestyle='-', linewidth=2)
plt.legend(
    ['class 0', 'class 1', 'dd', 'dd', 'dd'],
    loc='lower right'
)

plt.show()
