import numpy as np
from numpy.random import rand
import scipy as sp


class Perceptron():
    # def __init__(self, X, Y, lr = 0.1, iteration = 1000):
    def __init__(self, X, Y, lr = 0.1, iteration = 5000, epoch = 300):
        self.X = X
        self.Y = Y
        self.lr = lr
        # signal layer
        self.weight = rand(2)
        self.bias = rand(1)
        
        # double layer
        self.weight_layer_1 = np.random.uniform(-1, 1, (2, 2))
        self.weight_layer_2 = np.random.uniform(-1, 1, (2))
        self.bias_layer_1 = np.zeros((2))
        self.bias_layer_2 = np.zeros((1))
        
        self.iteration = iteration
    
    def Model(self):
        return np.matmul(self.X, self.weight) + self.bias
    
    def forward(self):
        output = self.Model()
        return self.activation(output)

    def activation(self, X): #sigmod
        return sp.special.expit(X)

    def loss(self, Ytgt, Ypred): #categorical
        return -np.mean(Ytgt * np.log(Ypred) + (1 - np.array(Ytgt)) * np.log(1 - Ypred))
    
    def Linear(self, xdata, weight, bias):
        return np.matmul(xdata, weight) + bias

    def run(self):
        # signal layer
        loss_score = []
        for i in range(self.iteration):
            self.cache = []
            Ypred = self.forward()
            loss = self.loss(self.Y, Ypred)
            loss_score.append(loss)
            print("loss : ", loss)
            dZ = Ypred - self.Y
            X = np.array(self.X)
            dw = np.matmul(X.T, dZ)
            db = np.sum(dZ) / len(dZ)
        
            self.weight = self.weight - self.lr * dw
            self.bias = self.bias - self.lr * db
            
            return self.weight, self.bias
        """
        # double layer
        Global_loss_score = []
        for i in range(self.iteration):
            # forward layer1
            input = np.array(self.X)
            output = self.Model(input, self.weight_layer_1, self.bias_layer_1)
            output = self.activation(output)
            cache = output
            input = output.copy()
            # forward layer2
            output = self.Model(input, self.weight_layer_2, self.bias_layer_2)
            input = output.copy()
            Ypred = self.activation(input)
            # loss
            loss = self.loss(self.Y, Ypred)
            
            # backpropagation sigmoid + binary corssentropy
            dZ = Ypred - self.Y
            
            # backpropagation layer2
            d_weight_layer_2 = np.matmul(cache.T, dZ)
            d_bias_layer_2 = np.mean(dZ, axis=0)
            
            # dZ update            
            dZ = dZ[:, np.newaxis] * self.weight_layer_2
            back_act = cache * (1 - cache)
            dZ = dZ * back_act

            # backpropagation layer1
            d_weight_layer_1 = np.matmul(d_weight_layer_2, dZ)
            d_bias_layer_1 = np.sum(dZ) / len(dZ)
            
            print("loss : ", loss)
            self.weight_layer_1 = self.weight_layer_1 - self.lr * d_weight_layer_1
            self.bias_layer_1 = self.bias_layer_1 - self.lr * d_bias_layer_1           

            self.weight_layer_2 = self.weight_layer_2 - self.lr * d_weight_layer_2
            self.bias_layer_2 = self.bias_layer_2 - self.lr * d_bias_layer_2

            Global_loss_score.append([loss, self.weight_layer_1, self.bias_layer_1, self.weight_layer_2, self.bias_layer_2])

        return Global_loss_score
        """
    
xdata = [[0, 0], [0, 1], [1, 0], [1, 1]]
ydata = [0, 1, 1, 1]

ANDgate = Perceptron(xdata, ydata)
weight, bias = ANDgate.run()
output = sp.special.expit(np.matmul(xdata, weight) + bias)
Ypred = (output >= 0.5).astype(int)
print("--------------------------")
print("Target | Predict")
print("--------------------------")
for i in range(4):
    print(ydata[i], "      |", Ypred[i])
