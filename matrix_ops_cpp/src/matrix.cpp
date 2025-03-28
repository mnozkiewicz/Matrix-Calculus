#include <random>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include "matrix.h"
#include "multiplications.h"


Matrix::Matrix(int height, int width, double fill_value): data(std::make_unique<double[]>(height * width)), height(height), width(width) {
    size = height * width;
    for(int i = 0; i < size; ++i) data[i] = fill_value;
}

Matrix::Matrix(int height, int width, double* memory_buffer): data(std::make_unique<double[]>(height * width)), height(height), width(width){
    size = height * width;
    for(int i = 0; i < size; ++i) data[i] = memory_buffer[i];
}

int Matrix::getHeight() const {
    return height;
}

int Matrix::getWidth() const {
    return width;
}

double& Matrix::operator()(int i, int j) {
    if (i < 0 || i >= height || j < 0 || j >= width) {
        throw std::out_of_range("Matrix indices out of bounds");
    }
    return data[i * width + j];
}

double& Matrix::operator()(int i, int j) const {
    if (i < 0 || i >= height || j < 0 || j >= width) {
        throw std::out_of_range("Matrix indices out of bounds");
    }
    return data[i * width + j];
}


Matrix Matrix::slice(int r1, int r2, int c1, int c2) const {
    if (r1 < 0 || r2 > this->height) {
        throw std::out_of_range("Row indices out of bounds");
    }

    if (c1 < 0 || c2 > this->width) {
        throw std::out_of_range("Col indices out of bounds");
    }

    if(r1 >= r2 || c1 >= c2){
        throw std::out_of_range("Fist argument of the slice should be smaller than second");
    }

    Matrix result(r2 - r1, c2 - c1, 0.0);

    for(int i = r1; i < r2; ++i){
        for(int j = c1; j < c2; ++j){
            result(i - r1, j - c1) = (*this)(i, j);  
        }
    }
    return result;

}

void Matrix::print() const {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            printf("%7.4f   ", (*this)(i, j));
        }
        std::cout << std::endl;
    }
}

std::string Matrix::repr() const {

    std::string mat_repr;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            mat_repr += std::to_string((*this)(i, j)) + " ";
        }
        mat_repr += "\n";
    }
    return mat_repr;
}

Matrix Matrix::operator+(const Matrix& other) const{
    if (this->height != other.height || this->width != other.width) {
        throw std::invalid_argument("Matrices must have the same dimensions for addition");
    }

    Matrix result(this->height, this->width, 0.0);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            result(i, j) = (*this)(i, j) + other(i, j);
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix& other) const{
    if (this->height != other.height || this->width != other.width) {
        throw std::invalid_argument("Matrices must have the same dimensions for addition");
    }
    Matrix result(this->height, this->width, 0.0);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            result(i, j) = (*this)(i, j) - other(i, j);
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const{
    if (this->height != other.height || this->width != other.width) {
        throw std::invalid_argument("Matrices must have the same dimensions for addition");
    }
    Matrix result(this->height, this->width, 0.0);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            result(i, j) = (*this)(i, j) * other(i, j);
        }
    }
    return result;
}

Matrix Matrix::operator+(double offset) const{
    Matrix result(this->height, this->width, 0.0);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            result(i, j) = (*this)(i, j) + offset;
        }
    }
    return result;
}

Matrix Matrix::operator-(double offset) const{
    Matrix result(this->height, this->width, 0.0);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            result(i, j) = (*this)(i, j) - offset;
        }
    }
    return result;
}


Matrix Matrix::operator*(double scale) const{
    Matrix result(this->height, this->width, 0.0);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            result(i, j) = (*this)(i, j) * scale;
        }
    }
    return result;
}


Matrix Matrix::operator^(const Matrix& other) const{
    if (this->width != other.height) {
        throw std::invalid_argument("Matrices dimension do not match for matrix multiplication");
    }

    Matrix result(this->height, other.width, 0.0);

    for (int i = 0; i < this->height; ++i) {
        for (int j = 0; j < other.width; ++j) {
            for(int k = 0; k < this->width; ++k){
                result(i, j) += (*this)(i, k) * other(k, j);
            }
        }
    }
    return result;
}


Matrix Matrix::copy() const{
    int m = (*this).getHeight(), n = (*this).getWidth();
    Matrix copied = Matrix(m, n, 0.0);
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            copied(i, j) = (*this)(i, j);
        }
    }
    return copied;
}

Matrix Matrix::transpose() const{
    int m = (*this).getHeight(), n = (*this).getWidth();
    Matrix copied = Matrix(n, m, 0.0);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            copied(i, j) = (*this)(j, i);
        }
    }
    return copied;
}


Matrix createRandomMatrix(int height, int width){
    Matrix matrix = Matrix(height, width, 0.0);
    std::random_device rd;
    std::mt19937 gen(rd());  
    std::uniform_real_distribution<double> dist(0, 1);

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            matrix(i, j) = dist(gen);
        }
    }
    return matrix;
}
