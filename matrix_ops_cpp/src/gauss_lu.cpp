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
        throw std::out_of_range("Matrix should be square");
    }

    if (vector_org.getHeight() != n || vector_org.getWidth() > 1) {
        throw std::out_of_range("Vector should have the same number of rows as matrix and one column");
    }

    Matrix matrix = matrix_org.copy();
    Matrix vector = vector_org.copy();

    for(int i = 0; i < n - 1; i++){
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