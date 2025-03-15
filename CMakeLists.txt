cmake_minimum_required(VERSION 3.12)

project(Matrix_algorithms)

find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

set(pybind11_DIR $ENV{VIRTUAL_ENV}/lib/python3.12/site-packages/pybind11/share/cmake/pybind11)
find_package(pybind11 CONFIG)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

pybind11_add_module(my_module src/example.cpp)