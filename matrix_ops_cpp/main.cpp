#include <iostream>
#include "matrix.h"
#include "multiplications.h"
#include "gauss_lu.h"

int main(){

    Matrix matrix = createRandomMatrix(8, 8);
    Matrix vector = createRandomMatrix(8, 1);
    Matrix sol1 = gauss_pivoting(matrix, vector);
    Matrix sol2 = gauss(matrix, vector);
    
    matrix.print();
    printf("\n");
    vector.transpose().print();
    printf("\n");
    sol1.transpose().print();
    printf("\n");
    sol2.transpose().print();
    return 0;
}