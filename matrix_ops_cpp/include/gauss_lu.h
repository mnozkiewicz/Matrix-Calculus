#pragma once
#include "matrix.h"

Matrix gauss(Matrix& mat1, Matrix& vector);

Matrix gauss_pivoting(Matrix& matrix, Matrix& vector);
