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
#include <thread>
using namespace std;


struct SquareMatrix{
    int dim;
    int** data;    // points to a [dim x dim] square matrix

    /*
     * Function Name: SquareMatrix Constructor
     * Description:   Default constructor for SquareMatrix
     * Return:        Void
     * Pre:           User enters Dimension for matrix
     * Post:          SquareMatrix object is created and data is initialized to 0
     */
    SquareMatrix(int dim) {
        this->dim = dim;
        this->data = new int *[dim];
        for (int i = 0; i < dim; i++) {
            data[i] = new int[dim];
            for (int j = 0; j < dim; j++) {
                data[i][j] = 0;
            }
        }
    }
};


/*
 * Function Name: displayMatrix
 * Description:   Function displays the dimension and the matrix's data
 * Return:        void
 * Pre:           SquareMatrix struct exists
 * Post:          Attributes of SquareMatrix are displayed
 */
void displayMatrix(const SquareMatrix* m) {
    cout << "Dimension: " << m->dim << endl;
    for (int i = 0; i < m->dim; i++) {
        for (int j = 0; j < m->dim; j++) {
            cout << m->data[i][j] << " ";
        }
        cout << endl;
    }
}

/*
 * Function Name: BruteForce
 * Description:   Multiplies two matrices using brute force method
 * Return:        SquareMatrix Pointer
 * Pre:           Two SquareMatrix structs exists
 * Post:          Resultant Matrix is returned
 */
SquareMatrix* BruteForce(const SquareMatrix& A, const SquareMatrix& B) {
    auto* resultant = new SquareMatrix(A.dim);
    resultant->dim = A.dim;
    // For Size of Row A
    for (int i = 0; i < A.dim; i++) {
        // For Size of Col B
        for (int j = 0; j < B.dim; j++) {
            // For Size of Col A (To Get Actual Values From A)
            for (int k = 0; k < A.dim; k++) {
                resultant->data[i][j] += A.data[i][k] * B.data[k][j];
            }
        }
    }
    return resultant;
}

/*
 * Function Name: ThreadedDivideAndConquer
 * Description:   Function displays the dimension and the matrix's data
 * Return:        void
 * Pre:           SquareMatrix struct exists
 * Post:          Attributes of SquareMatrix are displayed
 */
SquareMatrix* ThreadedDivideAndConquer(const SquareMatrix& A, const SquareMatrix& B) {
    auto* result = new SquareMatrix(A.dim);
}

SquareMatrix* Strassen(const SquareMatrix& A, const SquareMatrix& B) {
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
            element += to_string(i+1);
            element += to_string(j+1);
            matrixMap.emplace(element, A.data[i][j]);
            cout << "STORING: " << element << " " << A.data << endl;
        }
    }

    // Store Matrix B
    for (int i = 0; i < A.dim; i++) {
        for (int j = 0; j < B.dim; j++) {
            string element = "B";
            element += to_string(i+1);
            element += to_string(j+1);
            matrixMap.emplace(element, B.data[i][j]);
            cout << "STORING: " << element << " " << B.data << endl;
        }
    }

    int S1, S2, S3, S4, S5, S6, S7;
}

void * BruteForceSquareMatrixMultiplication(void *);

// Threads share the matrices
struct ThreadedMatrix {
    SquareMatrix *A;
    SquareMatrix *B;
    SquareMatrix *R;
    int resDim, rowStart, rowEnd, colStart, colEnd;

    ThreadedMatrix(SquareMatrix *a, SquareMatrix *b, SquareMatrix *r) {
        this->A = a;
        this->B = b;
        this->R = r;
        // Pass All Dimensions and Figure Out How to Divide in Functions
        this->resDim = a->dim;
        this->rowStart = a->dim;
        this->rowEnd = a->dim;
        this->colStart = a->dim;
        this->colEnd = a->dim;
    }
};

#endif //PROJECT3_MATRIXMULTIPLICATION_THREADEDMATRIXMULT_H
