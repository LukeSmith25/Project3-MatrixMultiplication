/*
* Author:                 Luke Smith
* Assignment Title:       Matrix Multiplication
* Assignment Description: This program computes the product of two matrices using four methods: Brute Force, Divide
*                         and Conquer, Strassen's Algorithm, and Threaded Strassen's Algorithm
* Due Date:               2/19/2023
* Date Created:           3/3/2023
* Date Last Modified:     3/3/2023 - Initial creation of files
 */

#ifndef PROJECT3_MATRIXMULTIPLICATION_THREADEDMATRIXMULT_H
#define PROJECT3_MATRIXMULTIPLICATION_THREADEDMATRIXMULT_H

#include <iostream>
using namespace std;

struct SquareMatrix{
    int dim;
    int** data;    // points to a [dim x dim] square matrix
    SquareMatrix(int size) {
        this->dim = size;
        this->data = nullptr;
    }
};

void * BruteForceSquareMatrixMultiplication(void *);

void setMatrix(SquareMatrix* A,int* array) {
    for (int i = 0; i < A->dim; i++) {
        for(int j = 0; j < A->dim; j++) {
            // Take Int Array and Populate Matrix Data
        }
    }
}

static void displayMatrix(SquareMatrix* matrix) {
    cout << matrix->dim << endl;
    for (int i = 0; i < matrix->dim; i++) {
        // For Size of Col B
        for (int j = 0; j < matrix->dim; j++) {
            cout << matrix->data[i][j] << " ";
        }
        cout << endl;
    }
}

//************************************************************
// description: read data from specified file                *
// return: string                                            *
// pre: string is valid                                      *
// post: returns string of data                              *
//                                                           *
//************************************************************
SquareMatrix* BruteForce(const SquareMatrix& A, const SquareMatrix& B) {
    auto* result = new SquareMatrix(A.dim);
    result->dim = A.dim;
    // For Size of Row A
    for (int i = 0; i < A.dim; i++) {
        // For Size of Col B
        for (int j = 0; j < B.dim; j++) {
            // For Size of Col A (To Get Actual Values From A)
            for (int k = 0; k < A.dim; k++) {
                result->data[i][j] += A.data[i][k] * B.data[k][j];
                cout << result->data[i][j] << " = " << A.data[i][k] << B.data[k][j];
            }
        }
    }

    return result;
}

#endif //PROJECT3_MATRIXMULTIPLICATION_THREADEDMATRIXMULT_H
