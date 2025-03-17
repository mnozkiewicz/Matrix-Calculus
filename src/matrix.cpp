#include <random>
#include <iostream>
#include <memory>
#include <stdexcept>
#include "matrix.h"


Matrix::Matrix(int height, int width, double fill_value): data(std::make_unique<double[]>(height * width)), height(height), width(width) {
    size = height * width;
    for(int i = 0; i < size; ++i) data[i] = fill_value;
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

void Matrix::print() const {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            std::cout << (*this)(i, j) << " ";
        }
        std::cout << std::endl;
    }
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

Matrix Matrix::operator+(double offset) const{
    Matrix result(this->height, this->width, 0.0);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            result(i, j) = (*this)(i, j) + offset;
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


int main(){

    Matrix matrix1 = Matrix(4, 4, 0.1);
    Matrix matrix2 = Matrix(4, 4, 0.3);

    // (matrix1 + matrix2).print();
    (matrix1 ^ matrix2).print();

    return 0;
}