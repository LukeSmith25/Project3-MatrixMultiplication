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
    // Read In Dimensions of Matrices
    int dim1, dim2;
    cin >> dim1 >> dim2;

    // Declare Two Matrices
    SquareMatrix matrixA = SquareMatrix(dim1);
    matrixA.displayMatrix();
    SquareMatrix matrixB = SquareMatrix(dim2);
    matrixB.displayMatrix();

    // Read in Matrices
    int input;
    for (int i = 0; i < dim1; i++) {
        for (int j = 0; j < dim1; j++) {
            cin >> input;
            matrixA.data[i][j] = input;
        }
    }

    //displayMatrix(matrixA);
    //displayMatrix(matrixB);

    return 0;
}
