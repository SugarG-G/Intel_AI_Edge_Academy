import numpy as np
import torch

array = np.random.rand(3, 4)

print(f"Shape of array: {array.shape}")
print(f"Number of dimensions: {array.ndim}")
print(f"Total elements: {array.size}")
print(f"Datatype of array: {array.dtype}")
print(f"Memory usage (bytes): {array.nbytes}")
print(f"Item size (bytes): {array.itemsize}")
print(f"Strides: {array.strides}")
print(f"Is C-contiguous: {array.flags.c_contiguous}")
print(f"Is Fortran-contiguous: {array.flags.f_contiguous}")

tensor = torch.from_numpy(array)

print(f"\nShape of tensor: {tensor.shape}")
print(f"Size of tensor: {tensor.size()}")
print(f"Number of dimensions: {tensor.ndim}")
print(f"Total elements: {tensor.numel()}")
print(f"Datatype of tensor: {tensor.dtype}")
print(f"Device tensor is stored on: {tensor.device}")
print(f"Memory layout: {tensor.layout}")
print(f"Strides: {tensor.stride()}")
print(f"Requires gradient: {tensor.requires_grad}")
print(f"Is contiguous: {tensor.is_contiguous()}")

transposed = tensor.t()
print(f"Is contiguous (transposed): {transposed.is_contiguous()}")
