#pragma once
#include "matrix.h"

Matrix gauss(Matrix& matrix, Matrix& vector);

Matrix gauss_pivoting(Matrix& matrix, Matrix& vector);

std::tuple<Matrix, Matrix> LU(const Matrix& matrix);

std::tuple<Matrix, Matrix, Matrix> LU_pivoting(const Matrix& matrix);
