cmake_minimum_required(VERSION 3.12)

project(Matrix_algorithms)

find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

set(pybind11_DIR $ENV{VIRTUAL_ENV}/lib/python3.12/site-packages/pybind11/share/cmake/pybind11)
find_package(pybind11 CONFIG)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(
    SOURCES
    src/bindings.cpp 
    src/matrix.cpp
    src/multiplications.cpp
)

pybind11_add_module(matrix_module ${SOURCES})