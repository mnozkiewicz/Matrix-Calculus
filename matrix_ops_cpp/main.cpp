#include <iostream>
#include "matrix.h"
#include "multiplications.h"
#include "gauss_lu.h"

int main(){

    Matrix matrix = createRandomMatrix(8, 8);
    auto [L, U] = LU(matrix);
    
    matrix.print();
    printf("\n");
    L.print();
    printf("\n");
    U.print();
    printf("\n");

    return 0;
}