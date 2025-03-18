#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <iostream>
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
            ptr[i * cols + j] = value;
        }
    }

    return arr;
}


py::array_t<double> add_two_arrays(py::array_t<double> mat1, py::array_t<double> mat2) {
    py::buffer_info buf1 = mat1.request();
    py::buffer_info buf2 = mat2.request();

    if (buf1.ndim != buf2.ndim) {
        throw std::runtime_error("Both inputs must have the same number of dimensions.");
    }

    for(int i = 0; i < buf1.ndim; i++){
        if(buf1.shape[i] != buf2.shape[i]){
            throw std::runtime_error("Array dimensions must match.");
        }
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


py::array_t<double> scale_array(py::array_t<double> mat, double x) {
    py::buffer_info buf = mat.request();

    if (buf.ndim != 2) {
        throw std::runtime_error("Matrix should have two dim");
    }


    py::array_t<double> result({buf.shape[0], buf.shape[1]});
    py::buffer_info buf_result = result.request();

    double* ptr = static_cast<double*>(buf.ptr);
    double* ptr_result = static_cast<double*>(buf_result.ptr);


    for(ssize_t i = 0; i < get_array_size(mat); i++){
        ptr_result[i] = ptr[i] * x;
    }

    return result;
}

py::array_t<double> mat_mul(py::array_t<double> mat1, py::array_t<double> mat2) {
    py::buffer_info buf1 = mat1.request();
    py::buffer_info buf2 = mat2.request();

    if (buf1.ndim != 2 || buf1.ndim != 2) {
        throw std::runtime_error("Both inputs must be 2d matrices");
    }

    if (buf1.shape[1] != buf2.shape[0]){
        throw std::runtime_error("Matrix dimension do not match");
    }

    ssize_t m = buf1.shape[0]; 
    ssize_t n = buf2.shape[1]; 
    ssize_t p = buf1.shape[1];

    py::array_t<double> result = create_2d_array(m, n, 0.0);
    py::buffer_info buf_result = result.request();

    double* ptr1 = static_cast<double*>(buf1.ptr);
    double* ptr2 = static_cast<double*>(buf2.ptr);
    double* ptr_result = static_cast<double*>(buf_result.ptr);

    
    for(ssize_t i = 0; i < m; i++){
        for(ssize_t j = 0; j < p; j++){
            for(ssize_t k = 0; k < n; k++){
                *ptr_result += (*ptr1)*(*ptr2);
                ++ptr_result;
                ++ptr2;
            }
            ptr_result -= n;
            ++ptr1;
        }
        ptr_result += n;
        ptr2 -= p*n;

    }

    return result;
}


py::array_t<double> matrix_slice(
    py::array_t<double> mat1, 
    ssize_t r1, ssize_t r2,
    ssize_t c1, ssize_t c2
) 
{
    ssize_t m = r2 - r1, n = c2 - c1;
    py::array_t<double> arr({r2 - r1, c2 - c1});
    py::buffer_info buf = arr.request();

    py::buffer_info buf_mat = mat1.request();

    double* ptr_mat = static_cast<double*>(buf_mat.ptr);
    double* ptr = static_cast<double*>(buf.ptr);

    ptr_mat += r1*(buf_mat.shape[0]) + c1;
    for(ssize_t i = r1; i < r2; i++){
        for(ssize_t j = c1; j < c2; j++){
            *ptr = *ptr_mat; 
            ptr++;
            ptr_mat++;
        }
        ptr_mat += buf_mat.shape[0] - n;
    }

    return arr;
}

void assign_values(
    py::array_t<double> target,
    py::array_t<double> source, 
    ssize_t r1, ssize_t r2,
    ssize_t c1, ssize_t c2
){

    py::buffer_info buf_t = target.request();
    py::buffer_info buf_s = source.request();

    double* ptr_t = static_cast<double*>(buf_t.ptr);
    double* ptr_s = static_cast<double*>(buf_s.ptr);

    ssize_t n = buf_t.shape[0];
    for(int i = r1; i < r2; i++){
        for(int j = c1; j < c2; j++){
            ptr_t[i*n + j] = *ptr_s;
            ++ptr_s;
        }
    }  
}

void add_directly(
    py::array_t<double> target,
    py::array_t<double> source1,
    py::array_t<double> source2,
    ssize_t r1, ssize_t r2,
    ssize_t c1, ssize_t c2
){

    py::buffer_info buf_t = target.request();
    py::buffer_info buf_s1 = source1.request();
    py::buffer_info buf_s2 = source2.request();

    double* ptr_t = static_cast<double*>(buf_t.ptr);
    double* ptr_s1 = static_cast<double*>(buf_s1.ptr);
    double* ptr_s2 = static_cast<double*>(buf_s2.ptr);

    ssize_t n = buf_t.shape[0];
    for(int i = r1; i < r2; i++){
        for(int j = c1; j < c2; j++){
            ptr_t[i*n + j] = *ptr_s1 + *ptr_s2;
            ++ptr_s1;
            ++ptr_s2;
        }
    }  
}


py::array_t<double> binet(py::array_t<double> mat1, py::array_t<double> mat2) {
    py::buffer_info buf1 = mat1.request();
    py::buffer_info buf2 = mat2.request();

    ssize_t n = buf1.shape[0];
    if (n == 1){
        double* ptr1 = static_cast<double*>(buf1.ptr);
        double* ptr2 = static_cast<double*>(buf2.ptr);
        return create_2d_array(1, 1, (*ptr1)*(*ptr2));
    }
    else{
        auto A_1_1 = matrix_slice(mat1, 0, n / 2, 0, n / 2);
        auto A_1_2 = matrix_slice(mat1, 0, n / 2, n / 2, n);
        auto A_2_1 = matrix_slice(mat1, n / 2, n, 0, n / 2);
        auto A_2_2 = matrix_slice(mat1, n / 2, n, n / 2, n);

        auto B_1_1 = matrix_slice(mat2, 0, n / 2, 0, n / 2);
        auto B_1_2 = matrix_slice(mat2, 0, n / 2, n / 2, n);
        auto B_2_1 = matrix_slice(mat2, n / 2, n, 0, n / 2);
        auto B_2_2 = matrix_slice(mat2, n / 2, n, n / 2, n);

        py::array_t<double> res = create_2d_array(n, n, 0); 

        add_directly(res, binet(A_1_1, B_1_1), binet(A_1_2, B_2_1), 0, n / 2, 0, n / 2);
        add_directly(res, binet(A_1_1, B_1_2), binet(A_1_2, B_2_2), 0, n / 2, n / 2, n);
        add_directly(res, binet(A_2_1, B_1_1), binet(A_2_2, B_2_1), n / 2, n, 0, n / 2);
        add_directly(res, binet(A_2_1, B_1_2), binet(A_2_2, B_2_2), n / 2, n, n / 2, n);
        
        return res;
    }
}

py::array_t<double> strassen(py::array_t<double> mat1, py::array_t<double> mat2) {
    py::buffer_info buf1 = mat1.request();
    py::buffer_info buf2 = mat2.request();

    ssize_t n = buf1.shape[0];
    if (n == 1){
        double* ptr1 = static_cast<double*>(buf1.ptr);
        double* ptr2 = static_cast<double*>(buf2.ptr);
        return create_2d_array(1, 1, (*ptr1)*(*ptr2));
    }
    else{
        auto A11 = matrix_slice(mat1, 0, n / 2, 0, n / 2);
        auto A12 = matrix_slice(mat1, 0, n / 2, n / 2, n);
        auto A21 = matrix_slice(mat1, n / 2, n, 0, n / 2);
        auto A22 = matrix_slice(mat1, n / 2, n, n / 2, n);

        auto B11 = matrix_slice(mat2, 0, n / 2, 0, n / 2);
        auto B12 = matrix_slice(mat2, 0, n / 2, n / 2, n);
        auto B21 = matrix_slice(mat2, n / 2, n, 0, n / 2);
        auto B22 = matrix_slice(mat2, n / 2, n, n / 2, n);


        auto P1 = strassen(A11 + A22, B11 + B22);
        auto P2 = strassen(A21 + A22, B11);
        auto P3 = strassen(A11, B12 - B22);
        auto P4 = strassen(A22, B21 - B11);
        auto P5 = strassen(A11 + A12, B22);
        auto P6 = strassen(A21 - A11, B11 + B12);
        auto P7 = strassen(A12 - A22, B21 + B22);

        auto C11 = P1 + P4 - P5 + P7;
        auto C12 = P3 + P5;
        auto C21 = P2 + P4;
        auto C22 = P1 - P2 + P3 + P6;


        py::array_t<double> res = create_2d_array(n, n, 0);

        assign_values(res, C11, 0, n / 2, 0, n / 2);
        assign_values(res, C12, 0, n / 2, n / 2, n);
        assign_values(res, C21, n / 2, n, 0, n / 2);
        assign_values(res, C22, n / 2, n, n / 2, n);

        return res;
    }
}

int add(int a, int b) {
    return a + b;
}


PYBIND11_MODULE(my_module, m) {
    m.def("add", &add, "A function that adds two numbers");
    m.def("add_one", &add_one, "Increase numpy array values by one");
    m.def("create_array", &create_array, "Creates a NumPy array of given size filled with a specific value");
    m.def("create_2d_array", &create_2d_array, "Creates a NumPy matrix of (rows, cols) filled with a specific value");
    m.def("add_two_arrays", &add_two_arrays, "Adds two matrices");
    m.def("mat_mul", &mat_mul, "Multiplies matrices");
    m.def("_binet_mul", &binet, "Binet matrix multiplication");
    m.def("_strassen_mul", &strassen, "Strassen matrix multiplication");
}
