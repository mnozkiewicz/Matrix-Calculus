#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>
#include <numeric>
#include <cmath>
#include "gauss_lu.h"


Matrix gauss(Matrix& matrix_org, Matrix& vector_org){

    int n = matrix_org.getHeight();
    if (matrix_org.getHeight() != matrix_org.getWidth()) {
        throw std::out_of_range("Matrix should be squared");
    }

    if (vector_org.getHeight() != n || vector_org.getWidth() > 1) {
        throw std::out_of_range("Vector should have the same number of rows as matrix and one column");
    }

    Matrix matrix = matrix_org.copy();
    Matrix vector = vector_org.copy();

    for(int i = 0; i < n - 1; i++){
        if(std::abs(matrix(i, i)) < 1e-15){
            throw std::invalid_argument("Matrix is not Gauss-able. Consider using pivoting.");
        }
        for(int j = i + 1; j < n; j++){
            double ratio = matrix(j, i) / matrix(i, i);
            for(int k = i; k < n; k++){
                matrix(j, k) -= ratio * matrix(i,k);
            }
            vector(j, 0) -= ratio * vector(i, 0);
        }
    }

    Matrix sol(n, 1, 0.0);
    
    for(int i = n - 1; i >= 0; i--){
        sol(i, 0) = vector(i, 0);
        for(int j = i + 1; j < n; j++){
            sol(i, 0) -= sol(j, 0) * matrix(i, j);
        }
        sol(i, 0) /= matrix(i, i);
    }

    return sol;
}

Matrix gauss_pivoting(Matrix& matrix_org, Matrix& vector_org){

    int n = matrix_org.getHeight();
    if (matrix_org.getHeight() != matrix_org.getWidth()) {
        throw std::out_of_range("Matrix should be square");
    }

    if (vector_org.getHeight() != n || vector_org.getWidth() > 1) {
        throw std::out_of_range("Vector should have the same number of rows as matrix and one column");
    }

    Matrix matrix = matrix_org.copy();
    Matrix vector = vector_org.copy();

    std::vector<int> perm(n);
    std::iota(perm.begin(), perm.end(), 0);

    for(int i = 0; i < n - 1; i++){
        int max_ind = i;
        for(int j = i + 1; j < n; j++){
            if(std::abs(matrix(perm[j], i)) > std::abs(matrix(perm[max_ind], i))){
                max_ind = j;
            }
        }

        std::swap(perm[i], perm[max_ind]);

        for(int j = i + 1; j < n; j++){
            double ratio = matrix(perm[j], i) / matrix(perm[i], i);
            for(int k = i; k < n; k++){
                matrix(perm[j], k) -= ratio * matrix(perm[i],k);
            }
            vector(perm[j], 0) -= ratio * vector(perm[i], 0);
        }
    }

    Matrix sol(n, 1, 0.0);
    
    for(int i = n - 1; i >= 0; i--){
        sol(i, 0) = vector(perm[i], 0);
        for(int j = i + 1; j < n; j++){
            sol(i, 0) -= sol(j, 0) * matrix(perm[i], j);
        }
        sol(i, 0) /= matrix(perm[i], i);
    }

    return sol;
}


std::tuple<Matrix, Matrix> LU(const Matrix& matrix_org){
    if (matrix_org.getHeight() != matrix_org.getWidth()) {
        throw std::out_of_range("Matrix should be square");
    }

    int n = matrix_org.getHeight();
    Matrix L(n, n, "identity");
    Matrix U = matrix_org.copy();

    for(int i = 0; i < n; i++){
        if(std::abs(U(i, i)) < 1e-15){
            throw std::invalid_argument("Matrix is non LU-able!. Consider using pivoting");
        }
        for(int j = i + 1; j < n; j++){
            double ratio = U(j, i) / U(i, i);
            for(int k = 0; k < n; k++){
                U(j, k) -= U(i, k) * ratio;
            }
            L(j, i) = ratio;
        }
    }
    
    return {std::move(L), std::move(U)};
}

void swap_rows(Matrix& mat, int row1, int row2){
    for(int i = 0; i < mat.getWidth(); i++){
        std::swap(mat(row1, i), mat(row2, i));
    }
}

std::tuple<Matrix, Matrix, Matrix> LU_pivoting(const Matrix& matrix_org){
    if (matrix_org.getHeight() != matrix_org.getWidth()) {
        throw std::out_of_range("Matrix should be squared");
    }

    int n = matrix_org.getHeight();

    Matrix P(n, n, 0.0);
    Matrix L(n, n, 0.0);
    Matrix U = matrix_org.copy();

    std::vector<int> perm(n);
    for(int i = 0; i < n; i++) {
        perm[i] = i;
    }

    for(int i = 0; i < n; i++){
        int max_index = i;
        for(int j = i + 1; j < n; j++){
            if(std::abs(U(j, i)) > std::abs(U(max_index, i))){
                max_index = j;
            }
        }

        if(max_index != i){
            swap_rows(U, i, max_index);
            swap_rows(L, i, max_index);
            std::swap(perm[i], perm[max_index]);
        }
        
        L(i, i) = 1.0;
        for(int j = i + 1; j < n; j++){
            double ratio = U(j, i) / U(i, i);
            for(int k = 0; k < n; k++){
                U(j, k) -= U(i, k) * ratio;
            }
            L(j, i) = ratio;
        }
    }

    for(int i = 0; i < n; i++) {
        P(perm[i], i) = 1.0;
    }

    return {std::move(P), std::move(L), std::move(U)};
}