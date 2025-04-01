#pragma once
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

class Matrix {
private:
    std::unique_ptr<double[]> data;  // Pointer to the data buffer
    int height;                      // Number of rows
    int width;                       // Number of columns                       // Total number of elements (height * width)

public:
    // Constructor to initialize matrix with a specific fill value
    Matrix(int height, int width, double fill_value);

    // Constructor to initialize matrix from a specific memory 
    Matrix(int height, int width, double* memory_buffer);

    // Constructor to initialize special matrix e.g. identity
    Matrix(int height, int width, const std::string matrix_type);

    // Move Constructor
    Matrix(Matrix&& other) noexcept;
    
    // Get the height of the matrix (number of rows)
    int getHeight() const;

    // Get the width of the matrix (number of columns)
    int getWidth() const;

    // Overload operator() for non-const access (allow modification)
    double& operator()(int i, int j);

    // Overload operator() for const access (read-only)
    double& operator()(int i, int j) const;

    Matrix slice(int r1, int r2, int c1, int c2) const;

    // Print the matrix (output to console)
    void print() const;

    std::string repr() const;

    Matrix operator+(const Matrix& other) const;

    Matrix operator+(double offset) const;

    Matrix operator-(const Matrix& other) const;

    Matrix operator-(double offset) const;

    Matrix operator*(const Matrix& other) const;

    Matrix operator*(double scale) const;

    Matrix operator^(const Matrix& other) const;

    Matrix copy() const;

    Matrix transpose() const;

};


Matrix createRandomMatrix(int height, int width);


