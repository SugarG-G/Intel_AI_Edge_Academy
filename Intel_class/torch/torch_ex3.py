from ast import mod
import torch
import torch.nn as nn
import torch.nn.functional as F
from torchviz import make_dot

torch.manual_seed(42)

model = nn.Linear(5, 3)

x = torch.ones(5)
y = torch.tensor([0., 0., 1.])

output = model(x)
loss = F.binary_cross_entropy_with_logits(output, y)

loss.backward()

weight_grad = model.weight.grad
bias_grad = model.bias.grad

dot = make_dot(loss, params=dict(model.named_parameters()))
dot.render('computational_graph', format='png')
dot.view()
