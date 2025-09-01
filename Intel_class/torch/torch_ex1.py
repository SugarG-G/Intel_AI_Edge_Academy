import torch

scalar = torch.tensor(5)
print("Scalar:", scalar)
print("shape:", scalar.shape)
print("Dimensions:", scalar.dim())

vector = torch.tensor([1, 2, 3, 4])
print("vector:", vector)
print("shape:", vector.shape)
print("Dimensions:", vector.dim())

matrix = torch.tensor([[1, 2], [3, 4], [5, 6]])
print("matrix:", matrix)
print("shape:", matrix.shape)
print("dimensions:", matrix.dim())

tensor_3d = torch.tensor([[[1, 2], [3, 4]], [[5, 6], [7, 8]]])
print("tenser_3d:", tensor_3d)
print("shape:", tensor_3d.shape)
print("dimensions:", tensor_3d.dim())
