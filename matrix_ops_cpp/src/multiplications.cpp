#include <iostream>
#include <memory>
#include <stdexcept>
#include "matrix.h"
#include "multiplications.h"

void add_directly(Matrix& res, const Matrix& mat1, int left, int right, int upper, int lower){
    for(int i = left; i < right; i++){
        for(int j = upper; j < lower; j++){
            res(i, j) += mat1(i - left, j - upper);
        }
    } 
}

Matrix binet(const Matrix& mat1, const Matrix& mat2){
    int n = mat1.getHeight();
    if (n == 1){
        return Matrix(1, 1, mat1(0, 0) * mat2(0, 0));
    }
    
    int m = n / 2;

    Matrix A11 = mat1.slice(0, m, 0, m);
    Matrix A12 = mat1.slice(0, m, m, n);
    Matrix A21 = mat1.slice(m, n, 0, m);
    Matrix A22 = mat1.slice(m, n, m, n);

    Matrix B11 = mat2.slice(0, m, 0, m);
    Matrix B12 = mat2.slice(0, m, m, n);
    Matrix B21 = mat2.slice(m, n, 0, m);
    Matrix B22 = mat2.slice(m, n, m, n);

    Matrix res(n, n, 0.0);

    add_directly(res, binet(A11, B11), 0, m, 0, m);
    add_directly(res, binet(A12, B21), 0, m, 0, m);

    add_directly(res, binet(A11, B12), 0, m, m, n);
    add_directly(res, binet(A12, B22), 0, m, m, n);

    add_directly(res, binet(A21, B11), m, n, 0, m);
    add_directly(res, binet(A22, B21), m, n, 0, m);

    add_directly(res, binet(A21, B12), m, n, m, n);
    add_directly(res, binet(A22, B22), m, n, m, n);

    return res;
}

Matrix strassen(const Matrix& mat1, const Matrix& mat2){
    int n = mat1.getHeight();
    if (n == 1){
        return Matrix(1, 1, mat1(0, 0) * mat2(0, 0));
    }
    
    int m = n / 2;
    
    Matrix A11 = mat1.slice(0, m, 0, m);
    Matrix A12 = mat1.slice(0, m, m, n);
    Matrix A21 = mat1.slice(m, n, 0, m);
    Matrix A22 = mat1.slice(m, n, m, n);

    Matrix B11 = mat2.slice(0, m, 0, m);
    Matrix B12 = mat2.slice(0, m, m, n);
    Matrix B21 = mat2.slice(m, n, 0, m);
    Matrix B22 = mat2.slice(m, n, m, n);


    Matrix P1 = strassen(A11 + A22, B11 + B22);
    Matrix P2 = strassen(A21 + A22, B11);
    Matrix P3 = strassen(A11, B12 - B22);
    Matrix P4 = strassen(A22, B21 - B11);
    Matrix P5 = strassen(A11 + A12, B22);
    Matrix P6 = strassen(A21 - A11, B11 + B12);
    Matrix P7 = strassen(A12 - A22, B21 + B22);

    Matrix C11 = P1 + P4 - P5 + P7;
    Matrix C12 = P3 + P5;
    Matrix C21 = P2 + P4;
    Matrix C22 = P1 - P2 + P3 + P6;

    Matrix res(n, n, 0.0);

    add_directly(res, C11, 0, m, 0, m);
    add_directly(res, C12, 0, m, m, n);
    add_directly(res, C21, m, n, 0, m);
    add_directly(res, C22, m, n, m, n);

    return res;
}


Matrix hybrid(const Matrix& mat1, const Matrix& mat2, int l){
    int n = mat1.getHeight();
    if (n == 1){
        return Matrix(1, 1, mat1(0, 0) * mat2(0, 0));
    }
    
    if (n <= l){
        return strassen(mat1, mat2);
    }
    
    int m = n / 2;

    Matrix A11 = mat1.slice(0, m, 0, m);
    Matrix A12 = mat1.slice(0, m, m, n);
    Matrix A21 = mat1.slice(m, n, 0, m);
    Matrix A22 = mat1.slice(m, n, m, n);

    Matrix B11 = mat2.slice(0, m, 0, m);
    Matrix B12 = mat2.slice(0, m, m, n);
    Matrix B21 = mat2.slice(m, n, 0, m);
    Matrix B22 = mat2.slice(m, n, m, n);

    Matrix res(n, n, 0.0);

    add_directly(res, hybrid(A11, B11, l), 0, m, 0, m);
    add_directly(res, hybrid(A12, B21, l), 0, m, 0, m);

    add_directly(res, hybrid(A11, B12, l), 0, m, m, n);
    add_directly(res, hybrid(A12, B22, l), 0, m, m, n);

    add_directly(res, hybrid(A21, B11, l), m, n, 0, m);
    add_directly(res, hybrid(A22, B21, l), m, n, 0, m);

    add_directly(res, hybrid(A21, B12, l), m, n, m, n);
    add_directly(res, hybrid(A22, B22, l), m, n, m, n);

    return res;
}