#include <iostream>
#include "matrix.h"
#include "multiplications.h"
#include "gauss_lu.h"
#include <Eigen/Dense>

int main(){

    Eigen::MatrixXd A = Eigen::MatrixXd::Random(10, 10);

    A(0, 0) = 0;

    Eigen::JacobiSVD<Eigen::MatrixXd> svd(A, Eigen::ComputeFullU | Eigen::ComputeFullV);

    std::cout << "Singular values:\n" << svd.singularValues() << "\n";
    std::cout << "U matrix:\n" << svd.matrixU() << "\n";
    std::cout << "V matrix:\n" << svd.matrixV() << "\n";
    
    return 0;
}