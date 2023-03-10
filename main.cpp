/*
* Author:                 Luke Smith
* Assignment Title:       Matrix Multiplication
* Assignment Description: This program computes the product of two matrices using four methods: Brute Force, Divide
*                         and Conquer, Strassen's Algorithm, and Threaded Strassen's Algorithm
* Due Date:               2/19/2023
* Date Created:           3/3/2023
* Date Last Modified:     3/3/2023 - Initial creation of files
 */

#include <iostream>
#include "ThreadedMatrixMult.h"
using namespace std;

int main() {
    SquareMatrix matrixA = *new SquareMatrix(3);
    SquareMatrix matrixB = *new SquareMatrix(3);
    int matrixA[3][3] = {10, 10, 20, 4, 5, 6, 2, 3, 5};
    int matrixB[3][3] = {3, 2, 4, 3, 3, 9, 4, 4, 2};

    auto* A = new SquareMatrix(3);
    auto* B = new SquareMatrix(3);
    A->data = reinterpret_cast<int **>((matrixA));
    B->data = (int**)(matrixB);

    displayMatrix(A);
    displayMatrix(B);

    return 0;
}
