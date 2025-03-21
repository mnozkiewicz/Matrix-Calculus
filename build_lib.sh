cmake -S . -B build_cpp -DPython3_EXECUTABLE=$(which python)
cmake --build build_cpp

mkdir -p matrix_ops
cp build_cpp/matrix_module.cpython*.so matrix_ops/