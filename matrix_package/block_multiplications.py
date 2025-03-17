import numpy as np
from .my_module import _binet_mul, _strassen_mul

def is_power_of_two(n: int) -> bool:
    return n > 0 and (n & (n - 1)) == 0

def binet_mul(mat1: np.ndarray, mat2: np.ndarray) -> np.ndarray:
    if len(mat1.shape) != 2 or mat1.shape[0] != mat1.shape[1] or not is_power_of_two(mat1.shape[0]):
        raise ValueError("Matrices should be squared and size should be a power of two")
    if mat1.shape != mat2.shape:
        raise ValueError("Matrices shapes do not match")
    
    return _binet_mul(mat1, mat2)


def strassen_mul(mat1: np.ndarray, mat2: np.ndarray) -> np.ndarray:
    if len(mat1.shape) != 2 or mat1.shape[0] != mat1.shape[1] or not is_power_of_two(mat1.shape[0]):
        raise ValueError("Matrices should be squared and size should be a power of two")
    if mat1.shape != mat2.shape:
        raise ValueError("Matrices shapes do not match")
    
    return _strassen_mul(mat1, mat2)