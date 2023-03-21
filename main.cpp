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
    SquareMatrix* matrixA = new SquareMatrix(dim1);
    SquareMatrix* matrixB = new SquareMatrix(dim2);

    // Read in Matrix A
    int input;
    for (int i = 0; i < dim1; i++) {
        for (int j = 0; j < dim1; j++) {
            cin >> input;
            matrixA->data[i][j] = input;
        }
    }
    cout << "MatrixA: " << endl;
    displayMatrix(matrixA);
    cout << endl;

    // Read in Matrix B
    for (int i = 0; i < dim2; i++) {
        for (int j = 0; j < dim2; j++) {
            cin >> input;
            matrixB->data[i][j] = input;
        }
    }
    cout << "MatrixB: " << endl;
    displayMatrix(matrixB);
    cout << endl;

    // Test Brute Force
    cout << "TESTING: BruteForce" << endl;
    SquareMatrix* resultant1 = BruteForce(*matrixA, *matrixB);
    displayMatrix(resultant1);

    // Test ThreadedDivideAndConquer
    cout << "TESTING: ThreadedDivideAndConquer" << endl;
    SquareMatrix* resultant2 = ThreadedDivideAndConquer(*matrixA, *matrixB);
    displayMatrix(resultant2);

    // Test Strassen
    SquareMatrix* resultant3 = Strassen(*matrixA, *matrixB);
    displayMatrix(resultant3);

    return 0;
}
