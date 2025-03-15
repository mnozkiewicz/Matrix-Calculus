#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <vector>

namespace py = pybind11;

ssize_t get_array_size(py::array_t<double> array){

    py::buffer_info buf = array.request();
    ssize_t size = 1;

    for(ssize_t s: buf.shape){
        size *= s;
    }
    return size;
}

void add_one(py::array_t<double> array) {
    py::buffer_info buf = array.request();

    double* ptr = static_cast<double*>(buf.ptr);

    ssize_t size = get_array_size(array);

    for (ssize_t i = 0; i < size; i++) {
        ptr[i] += 1.0;
    }
}

py::array_t<double> create_array(ssize_t size, double value) {
    // Allocate a new NumPy array of the given size
    py::array_t<double> arr(size);

    // Request buffer information to access raw memory
    py::buffer_info buf = arr.request();

    // Get a pointer to the raw data
    double* ptr = static_cast<double*>(buf.ptr);

    // Fill the array with the specified value
    for (ssize_t i = 0; i < size; i++) {
        ptr[i] = value;
    }

    // Return the newly created NumPy array
    return arr;
}


py::array_t<double> create_2d_array(ssize_t rows, ssize_t cols, double value) {
    py::array_t<double> arr({rows, cols});  // Define shape (rows, cols)
    py::buffer_info buf = arr.request();
    double* ptr = static_cast<double*>(buf.ptr);

    for (ssize_t i = 0; i < rows; i++) {
        for (ssize_t j = 0; j < cols; j++) {
            ptr[i * cols + j] = value;  // Row-major order
        }
    }

    return arr;
}


py::array_t<double> add_two_matrices(py::array_t<double> mat1, py::array_t<double> mat2) {
    py::buffer_info buf1 = mat1.request();
    py::buffer_info buf2 = mat2.request();

    if (buf1.ndim != 2 || buf2.ndim != 2) {
        throw std::runtime_error("Both inputs must be 2D matrices.");
    }
    if (buf1.shape[0] != buf2.shape[0] || buf1.shape[1] != buf2.shape[1]) {
        throw std::runtime_error("Matrix dimensions must match.");
    }

    py::array_t<double> result({buf1.shape[0], buf1.shape[1]});
    py::buffer_info buf_result = result.request();

    double* ptr1 = static_cast<double*>(buf1.ptr);
    double* ptr2 = static_cast<double*>(buf2.ptr);
    double* ptr_result = static_cast<double*>(buf_result.ptr);


    for(ssize_t i = 0; i < get_array_size(mat1); i++){
        ptr_result[i] = ptr1[i] + ptr2[i];
    }

    return result;
}

int add(int a, int b) {
    return a + b;
}


PYBIND11_MODULE(my_module, m) {
    m.def("add", &add, "A function that adds two numbers");
    m.def("add_one", &add_one, "Increase numpy array values by one");
    m.def("create_array", &create_array, "Creates a NumPy array of given size filled with a specific value");
    m.def("create_2d_array", &create_2d_array, "Creates a NumPy matrix of (rows, cols) filled with a specific value");
    m.def("add_two_matrices", &add_two_matrices, "Adds two matrices");
    m.def("add_two_matrices", &add_two_matrices, "Adds two matrices");
}