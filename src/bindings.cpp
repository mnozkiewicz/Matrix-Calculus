#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <iostream>
#include <vector>
#include "matrix.h"
#include "multiplications.h"

namespace py = pybind11;

py::array_t<double> matrixToNumpy(const Matrix& matrix){

    int height = matrix.getHeight();
    int width = matrix.getWidth();

    py::array_t<double> arr({height, width});
    py::buffer_info buf = arr.request();

    double* ptr = static_cast<double*>(buf.ptr);

    for (int i = 0; i < height; ++i) {
        for(int j = 0; j < width; ++j){
            ptr[i*width + j] = matrix(i, j);
        }
    }
    return arr;
}

Matrix numpyToMatrix(py::array_t<double>& numpyArr){

    py::buffer_info buf = numpyArr.request();
    double* ptr = static_cast<double*>(buf.ptr);

    if (buf.ndim != 2) {
        throw std::runtime_error("Input numpy array should be two dimensional");
    }

    int height = buf.shape[0];
    int width = buf.shape[1];

    return Matrix(height, width, ptr);
}

PYBIND11_MODULE(matrix_module, m) {
    m.def("createRandomMatrix", &createRandomMatrix, "A function that adds two numbers");
    m.def("matrixToNumpy", &matrixToNumpy, "Convert Matrix object to numpy");
    m.def("numpyToMatrix", &numpyToMatrix, "Convert Numpy object to Matrix");

    m.def("_binet", &binet, "Binet matrix multiplication");
    m.def("_strassen", &strassen, "Strassen matrix multiplication");
    m.def("_hybrid", &hybrid, "Hybrid matrix multiplication");

    py::class_<Matrix>(m, "Matrix")
        .def(py::init<int, int, double>())  // Bind constructor
        .def("getHeight", &Matrix::getHeight)  // Bind method
        .def("getWidth", &Matrix::getWidth)
        .def("__repr__", &Matrix::repr)
        .def("at", py::overload_cast<int, int>(&Matrix::operator(), py::const_))
        .def("slice", &Matrix::slice)
        .def("__add__", py::overload_cast<const Matrix&>(&Matrix::operator+, py::const_))
        .def("__add__", py::overload_cast<double>(&Matrix::operator+, py::const_))
        .def("__sub__", py::overload_cast<const Matrix&>(&Matrix::operator-, py::const_))
        .def("__sub__", py::overload_cast<double>(&Matrix::operator-, py::const_))
        .def("__mul__", py::overload_cast<const Matrix&>(&Matrix::operator*, py::const_))
        .def("__mul__", py::overload_cast<double>(&Matrix::operator*, py::const_))
        .def("__matmul__", &Matrix::operator^);
}