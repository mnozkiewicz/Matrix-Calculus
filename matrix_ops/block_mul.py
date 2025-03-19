import numpy as np
from .matrix_module import _binet, _strassen, _hybrid, Matrix

def is_power_of_two(n: int) -> bool:
    return n > 0 and (n & (n - 1)) == 0


def check_matrices(mat1: Matrix, mat2: Matrix):
    m1, n1 = mat1.getHeight(), mat1.getWidth()
    m2, n2 = mat2.getHeight(), mat2.getWidth()

    if m1 != n1 or m2 != n2:
        raise ValueError("Matrices should be squared")
    
    if m1 != m2:
        raise ValueError("Matrices shapes do not match")
    
    if not is_power_of_two(m1):
        raise ValueError("Matrix size should be a power of two")


def binet(mat1: Matrix, mat2: Matrix) -> Matrix:
    check_matrices(mat1, mat2)
    return _binet(mat1, mat2)


def strassen(mat1: Matrix, mat2: Matrix) -> Matrix:
    check_matrices(mat1, mat2)
    return _strassen(mat1, mat2)

def hybrid(mat1: Matrix, mat2: Matrix, l: int) -> Matrix:
    check_matrices(mat1, mat2)
    return _hybrid(mat1, mat2, l)