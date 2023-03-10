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
#include <unordered_map>
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


SquareMatrix* ThreadedDivideAndConquer(const SquareMatrix& A, const SquareMatrix& B) {
    /*
     * S1 = (A11 + A22) * (B11 + B22)
     * S2 = (A21 + A22) *  B11
     * S3 = A11 * (B12 – B22)
     * S4 = A22 * (B21 – B11)
     * S5 = (A11 + A12) * B22
     * S6 = (A21 – A11) * (B11 + B12)
     * S7 = (A12 – A22) * (B21 + B22)
     */

    unordered_map<string,int> matrixMap;

    // Store Matrix A
    for (int i = 0; i < A.dim; i++) {
        for (int j = 0; j < B.dim; j++) {
            string element = "A";
            element += (i+1);
            element += (j+1);
            matrixMap.emplace(element, A.data[i][j]);
            cout << "STORING: " << element << " " << A.data << endl;
        }
    }

    // Store Matrix B
    for (int i = 0; i < A.dim; i++) {
        for (int j = 0; j < B.dim; j++) {
            string element = "B";
            element += (i+1);
            element += (j+1);
            matrixMap.emplace(element, B.data[i][j]);
            cout << "STORING: " << element << " " << B.data << endl;
        }
    }

    int S1, S2, S3, S4, S5, S6, S7;
}


#endif //PROJECT3_MATRIXMULTIPLICATION_THREADEDMATRIXMULT_H
