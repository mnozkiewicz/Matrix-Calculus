cmake -S . -B build_cpp -DPython3_EXECUTABLE=$(which python)
cmake --build build_cpp

mkdir -p matrix_package
cp build_cpp/my_module.cpython-312-darwin.so matrix_package/