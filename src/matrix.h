#pragma once
#include <iostream>
#include <memory>
#include <stdexcept>

class Matrix {
private:
    std::unique_ptr<double[]> data;  // Pointer to the data buffer
    int height;                      // Number of rows
    int width;                       // Number of columns
    int size;                        // Total number of elements (height * width)

public:
    // Constructor to initialize matrix with a specific fill value
    Matrix(int height, int width, double fill_value);

    // Get the height of the matrix (number of rows)
    int getHeight() const;

    // Get the width of the matrix (number of columns)
    int getWidth() const;

    // Overload operator() for non-const access (allow modification)
    double& operator()(int i, int j);

    // Overload operator() for const access (read-only)
    double& operator()(int i, int j) const;

    // Print the matrix (output to console)
    void print() const;

    Matrix operator+(const Matrix& other) const;

    Matrix operator^(const Matrix& other) const;

    Matrix operator+(double offset) const;

    Matrix operator*(double scale) const;
};


