#pragma once
#include "matrix.h"


Matrix binet(const Matrix& mat1, const Matrix& mat2);

Matrix strassen(const Matrix& mat1, const Matrix& mat2);

Matrix hybrid(const Matrix& mat1, const Matrix& mat2, int l);
