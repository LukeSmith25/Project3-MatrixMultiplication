/*
* Author:                 Luke Smith
* Assignment Title:       Matrix Multiplication
* Assignment Description: This program computes the product of two matrices using four methods: Brute Force, Divide
*                         and Conquer, Strassen's Algorithm, and Threaded Strassen's Algorithm
* Due Date:               3/26/2023
* Date Created:           3/3/2023
* Date Last Modified:     3/26/2023
 */

#ifndef PROJECT3_MATRIXMULTIPLICATION_THREADEDMATRIXMULT_H
#define PROJECT3_MATRIXMULTIPLICATION_THREADEDMATRIXMULT_H

#include <iostream>
#include <unordered_map>
#include <thread>
using namespace std;

// Struct Declarations
struct SquareMatrix;
struct ThreadedMatrix;

// Core Functions
void* BruteForceMultiplication(void* tMatrix);
SquareMatrix* BruteForce(const SquareMatrix& A, const SquareMatrix& B);
SquareMatrix* ThreadedDivideAndConquer(const SquareMatrix& A, const SquareMatrix& B);
SquareMatrix* Strassen(const SquareMatrix& A, const SquareMatrix& B);

// Helper Functions
void multiply(const SquareMatrix& A, const SquareMatrix& B, SquareMatrix& C, int mid);
void add(const SquareMatrix& A, const SquareMatrix& B, SquareMatrix& C, int mid);
void sub(const SquareMatrix& A, const SquareMatrix& B, SquareMatrix& C, int mid);
void displayMatrix(const SquareMatrix* m);

// SquareMatrix Definition
struct SquareMatrix{
    int dim;
    int** data;
    SquareMatrix(){}

    /*
     * Function Name: SquareMatrix Constructor
     * Description:   Default constructor for SquareMatrix
     * Return:        Void
     * Pre:           Integer representing the matrix's dimension is passed
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


// ThreadedMatrix Definition
struct ThreadedMatrix {
    SquareMatrix *A;
    SquareMatrix *B;
    SquareMatrix *C;
    int dim, rowStart, colStart;

    ThreadedMatrix(SquareMatrix *a, SquareMatrix *b, SquareMatrix *c, int dim, int rowStart, int colStart) {
        this->A = a;
        this->B = b;
        this->C = c;
        this->dim = dim;
        this->rowStart = rowStart;
        this->colStart = colStart;
    }
};

/*
 * Function Name: BruteForceMultiplication
 * Description:   Function uses brute force to multiply two matrices passed in
 * Return:        void *
 * Pre:           ThreadedMatrix struct pointer passed to function and is cast to void *
 * Post:          void ThreadedMatrix pointer is returned to thread
 */
void* BruteForceMultiplication(void* tMatrix) {
    auto* threadedMatrix = (ThreadedMatrix*) tMatrix;
    const auto* A = threadedMatrix->A;
    const auto* B = threadedMatrix->B;
    int mid = threadedMatrix->A->dim;

    for (int i = 0; i < mid; i++) {
        for (int j = 0; j < mid; j++) {
            int sum = 0;
            for (int k = 0; k < threadedMatrix->C->dim; k++) {
                sum += A->data[i][k] * B->data[k][j];
            }
            threadedMatrix->C->data[i][j] = sum;
        }
    }
    return nullptr;
}

/*
 * Function Name: BruteForce
 * Description:   Multiplies two matrices using brute force method
 * Return:        SquareMatrix Pointer
 * Pre:           Two SquareMatrix structs are passed by reference
 * Post:          Resultant matrix C is returned as a pointer
 */
SquareMatrix* BruteForce(const SquareMatrix& A, const SquareMatrix& B) {
    auto* C = new SquareMatrix(A.dim);
    int mid = A.dim/2;

    auto* A11 = new SquareMatrix(mid);
    auto* A12 = new SquareMatrix(mid);
    auto* A21 = new SquareMatrix(mid);
    auto* A22 = new SquareMatrix(mid);

    auto* B11 = new SquareMatrix(mid);
    auto* B12 = new SquareMatrix(mid);
    auto* B21 = new SquareMatrix(mid);
    auto* B22 = new SquareMatrix(mid);

    for (int i = 0; i < A.dim; i++) {
        for (int j = 0; j < B.dim; j++) {
            for (int k = 0; k < A.dim; k++) {
                C->data[i][j] += A.data[i][k] * B.data[k][j];
            }
        }
    }

    return C;
}

/*
 * Function Name: ThreadedDivideAndConquer
 * Description:   Multiplies two matrices using brute force method and passes multiplications to individual threads
 * Return:        SquareMatrix Pointer
 * Pre:           Two SquareMatrix structs are passed by reference
 * Post:          Resultant matrix C is returned as a pointer
 */
SquareMatrix* ThreadedDivideAndConquer(const SquareMatrix& A, const SquareMatrix& B) {
    // Store dimension and Create Resultant
    int dim = A.dim;
    auto* C = new SquareMatrix(A.dim);

    // Base Case: 1
    if (dim == 1) {
        C->data[0][0] = A.data[0][0] * B.data[0][0];
        return C;
    }

    // Split Matrices by Dim/2 so 4x4 -> 4, 2x2 Matrices
    int mid = dim/2;

    auto* A11 = new SquareMatrix(mid);
    auto* A12 = new SquareMatrix(mid);
    auto* A21 = new SquareMatrix(mid);
    auto* A22 = new SquareMatrix(mid);

    auto* B11 = new SquareMatrix(mid);
    auto* B12 = new SquareMatrix(mid);
    auto* B21 = new SquareMatrix(mid);
    auto* B22 = new SquareMatrix(mid);

    // Transfer Data from A & B to Sub-Matrices
    for (int i = 0; i < mid; i++) {
        for (int j = 0; j < mid; j++) {
            A11->data[i][j] = A.data[i][j];
            A12->data[i][j] = A.data[i][j + mid];
            A21->data[i][j] = A.data[i + mid][j];
            A22->data[i][j] = A.data[i + mid][j + mid];

            B11->data[i][j] = B.data[i][j];
            B12->data[i][j] = B.data[i][j + mid];
            B21->data[i][j] = B.data[i + mid][j];
            B22->data[i][j] = B.data[i + mid][j + mid];
        }
    }

    // Create Threaded Matrices
    auto* tM1 = new ThreadedMatrix(A11, B11, new SquareMatrix(mid), dim, 0, 0);
    auto* tM2 = new ThreadedMatrix(A12, B21, new SquareMatrix(mid), dim, 0, 0);
    auto* tM3 = new ThreadedMatrix(A11, B12, new SquareMatrix(mid), dim, 0, 0);
    auto* tM4 = new ThreadedMatrix(A12, B22, new SquareMatrix(mid), dim, 0, 0);
    auto* tM5 = new ThreadedMatrix(A21, B11, new SquareMatrix(mid), dim, 0, 0);
    auto* tM6 = new ThreadedMatrix(A22, B21, new SquareMatrix(mid), dim, 0, 0);
    auto* tM7 = new ThreadedMatrix(A21, B12, new SquareMatrix(mid), dim, 0, 0);
    auto* tM8 = new ThreadedMatrix(A22, B22, new SquareMatrix(mid), dim, 0, 0);

    // Pass Matrices To Threads
    thread t1(BruteForceMultiplication, (void *)tM1);
    thread t2(BruteForceMultiplication, (void *)tM2);
    thread t3(BruteForceMultiplication, (void *)tM3);
    thread t4(BruteForceMultiplication, (void *)tM4);
    thread t5(BruteForceMultiplication, (void *)tM5);
    thread t6(BruteForceMultiplication, (void *)tM6);
    thread t7(BruteForceMultiplication, (void *)tM7);
    thread t8(BruteForceMultiplication, (void *)tM8);

    // Join the Threads Results
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();

    auto* C11 = new SquareMatrix(mid);
    auto* C12 = new SquareMatrix(mid);
    auto* C21 = new SquareMatrix(mid);
    auto* C22 = new SquareMatrix(mid);

    add(*tM1->C, *tM2->C, *C11, mid);
    add(*tM3->C, *tM4->C, *C12, mid);
    add(*tM5->C, *tM6->C, *C21, mid);
    add(*tM7->C, *tM8->C, *C22, mid);

    // Combine the submatrices to form the final output matrix
    for (int i = 0; i < mid; i++) {
        for (int j = 0; j < mid; j++) {
            C->data[i][j] += C11->data[i][j];
            C->data[i][j + mid] += C12->data[i][j];
            C->data[i + mid][j] += C21->data[i][j];
            C->data[i + mid][j + mid] += C22->data[i][j];
        }
    }

    return C;
}

/*
 * Function Name: Strassen
 * Description:   Multiplies two matrices using Strassen's method
 * Return:        SquareMatrix Pointer
 * Pre:           Two SquareMatrix structs are passed by reference
 * Post:          Resultant matrix C is returned as a pointer
 */
SquareMatrix* Strassen(const SquareMatrix& A, const SquareMatrix& B) {
    auto* C = new SquareMatrix(A.dim);
    int mid = A.dim/2;

    auto* A11 = new SquareMatrix(mid);
    auto* A12 = new SquareMatrix(mid);
    auto* A21 = new SquareMatrix(mid);
    auto* A22 = new SquareMatrix(mid);
    auto* B11 = new SquareMatrix(mid);
    auto* B12 = new SquareMatrix(mid);
    auto* B21 = new SquareMatrix(mid);
    auto* B22 = new SquareMatrix(mid);
    auto* C11 = new SquareMatrix(mid);
    auto* C12 = new SquareMatrix(mid);
    auto* C21 = new SquareMatrix(mid);
    auto* C22 = new SquareMatrix(mid);

    for (int i = 0; i < mid; i++) {
        for (int j = 0; j < mid; j++) {
            A11->data[i][j] = A.data[i][j];
            A12->data[i][j] = A.data[i][j + mid];
            A21->data[i][j] = A.data[i + mid][j];
            A22->data[i][j] = A.data[i + mid][j + mid];

            B11->data[i][j] = B.data[i][j];
            B12->data[i][j] = B.data[i][j + mid];
            B21->data[i][j] = B.data[i + mid][j];
            B22->data[i][j] = B.data[i + mid][j + mid];
        }
    }

    // Sub-Strassen's Add/Sub
    auto* s1 = new SquareMatrix(mid);
    auto* s2 = new SquareMatrix(mid);
    auto* s3 = new SquareMatrix(mid);
    auto* s4 = new SquareMatrix(mid);
    auto* s5 = new SquareMatrix(mid);
    auto* s6 = new SquareMatrix(mid);
    auto* s7 = new SquareMatrix(mid);
    auto* s8 = new SquareMatrix(mid);
    auto* s9 = new SquareMatrix(mid);
    auto* s10 = new SquareMatrix(mid);

    sub(*B12, *B22, *s1, mid);
    add(*A11, *A12, *s2, mid);
    add(*A21, *A22, *s3, mid);
    sub(*B21, *B11, *s4, mid);
    add(*A11, *A22, *s5, mid);
    add(*B11, *B22, *s6, mid);
    sub(*A12, *A22, *s7, mid);
    add(*B21, *B22, *s8, mid);
    sub(*A11, *A21, *s9, mid);
    add(*B11, *B12, *s10, mid);

    /*
     * Strassen Multiplication
     *
     * S1 = A11(B12-B22)
     * S2 = (A11+A12)B22
     * S3 = (A21+A22)B11
     * S4 = A22(B21-B11)
     * S5 = (A11+A22)(B11+B22)
     * S6 = (A12-A22)(B21+B22)
     * S7 = (A11-A21)(B11+B12)
     */
    auto* M1 = new SquareMatrix(mid);
    auto* M2 = new SquareMatrix(mid);
    auto* M3 = new SquareMatrix(mid);
    auto* M4 = new SquareMatrix(mid);
    auto* M5 = new SquareMatrix(mid);
    auto* M6 = new SquareMatrix(mid);
    auto* M7 = new SquareMatrix(mid);

    M1 = BruteForce(*A11, *s1);
    M2 = BruteForce(*s2, *B22);
    M3 = BruteForce(*s3, *B11);
    M4 = BruteForce(*A22, *s4);
    M5 = BruteForce(*s5, *s6);
    M6 = BruteForce(*s7, *s8);
    M7 = BruteForce(*s9, *s10);

    auto* tempA = new SquareMatrix(mid);
    auto* tempB = new SquareMatrix(mid);

    // Calculate: C11
    add(*M5, *M4,*tempA, mid);
    add(*tempA, *M6, *tempB, mid);
    sub(*tempB, *M2, *C11, mid);

    // Calculate: C12
    add(*M1, *M2, *C12, mid);
    // Calculate: C21
    add(*M3, *M4, *C21, mid);
    // Calculate: C22
    add(*M5, *M1, *tempA, mid);
    sub(*tempA, *M3, *tempB, mid);
    sub(*tempB, *M7, *C22, mid);

    for (int i = 0; i < mid; i++) {
        for (int j = 0; j < mid; j++) {
            C->data[i][j] = C11->data[i][j];
            C->data[i][j + mid] = C12->data[i][j];
            C->data[i + mid][j] = C21->data[i][j];
            C->data[i + mid][j+ mid] = C22->data[i][j];
        }
    }

    return C;
}

/*
 * Function Name: ThreadedStrassen
 * Description:   Multiplies two matrices using Strassen's method and passes each multiplication to a separate thread
 * Return:        SquareMatrix Pointer
 * Pre:           Two SquareMatrix structs are passed by reference
 * Post:          Resultant matrix C is returned as a pointer
 */
SquareMatrix* ThreadedStrassen(const SquareMatrix& A, const SquareMatrix& B) {
    auto* C = new SquareMatrix(A.dim);
    int mid = A.dim/2;

    // Initialize sub-matrices
    auto* A11 = new SquareMatrix(mid);
    auto* A12 = new SquareMatrix(mid);
    auto* A21 = new SquareMatrix(mid);
    auto* A22 = new SquareMatrix(mid);
    auto* B11 = new SquareMatrix(mid);
    auto* B12 = new SquareMatrix(mid);
    auto* B21 = new SquareMatrix(mid);
    auto* B22 = new SquareMatrix(mid);
    auto* C11 = new SquareMatrix(mid);
    auto* C12 = new SquareMatrix(mid);
    auto* C21 = new SquareMatrix(mid);
    auto* C22 = new SquareMatrix(mid);

    // Split A and B data into sub-matrices
    for (int i = 0; i < mid; i++) {
        for (int j = 0; j < mid; j++) {
            A11->data[i][j] = A.data[i][j];
            A12->data[i][j] = A.data[i][j + mid];
            A21->data[i][j] = A.data[i + mid][j];
            A22->data[i][j] = A.data[i + mid][j + mid];

            B11->data[i][j] = B.data[i][j];
            B12->data[i][j] = B.data[i][j + mid];
            B21->data[i][j] = B.data[i + mid][j];
            B22->data[i][j] = B.data[i + mid][j + mid];
        }
    }

    // Sub-Strassen's Add/Sub
    // Initialize sub-sub-strassen's matrices
    auto* s1 = new SquareMatrix(mid);
    auto* s2 = new SquareMatrix(mid);
    auto* s3 = new SquareMatrix(mid);
    auto* s4 = new SquareMatrix(mid);
    auto* s5 = new SquareMatrix(mid);
    auto* s6 = new SquareMatrix(mid);
    auto* s7 = new SquareMatrix(mid);
    auto* s8 = new SquareMatrix(mid);
    auto* s9 = new SquareMatrix(mid);
    auto* s10 = new SquareMatrix(mid);

    // Compute each sub-portion
    sub(*B12, *B22, *s1, mid);
    add(*A11, *A12, *s2, mid);
    add(*A21, *A22, *s3, mid);
    sub(*B21, *B11, *s4, mid);
    add(*A11, *A22, *s5, mid);
    add(*B11, *B22, *s6, mid);
    sub(*A12, *A22, *s7, mid);
    add(*B21, *B22, *s8, mid);
    sub(*A11, *A21, *s9, mid);
    add(*B11, *B12, *s10, mid);

    // Initialize Strassen's 7 Matrices
    auto* M1 = new SquareMatrix(mid);
    auto* M2 = new SquareMatrix(mid);
    auto* M3 = new SquareMatrix(mid);
    auto* M4 = new SquareMatrix(mid);
    auto* M5 = new SquareMatrix(mid);
    auto* M6 = new SquareMatrix(mid);
    auto* M7 = new SquareMatrix(mid);

    // Multiply and store result in matrices
    M1 = BruteForce(*A11, *s1);
    M2 = BruteForce(*s2, *B22);
    M3 = BruteForce(*s3, *B11);
    M4 = BruteForce(*A22, *s4);
    M5 = BruteForce(*s5, *s6);
    M6 = BruteForce(*s7, *s8);
    M7 = BruteForce(*s9, *s10);

    // Possibly make function to create threads
    auto* tM1 = new ThreadedMatrix(A11, s1, new SquareMatrix(mid), mid, 0, 0);
    auto* tM2 = new ThreadedMatrix(s2, B22, new SquareMatrix(mid), mid, 0, 0);
    auto* tM3 = new ThreadedMatrix(s3, B11, new SquareMatrix(mid), mid, 0, 0);
    auto* tM4 = new ThreadedMatrix(A22, s4, new SquareMatrix(mid), mid, 0, 0);
    auto* tM5 = new ThreadedMatrix(s5, s6, new SquareMatrix(mid), mid, 0, 0);
    auto* tM6 = new ThreadedMatrix(s7, s8, new SquareMatrix(mid), mid, 0, 0);
    auto* tM7 = new ThreadedMatrix(s9, s10, new SquareMatrix(mid), mid, 0, 0);

    // Threads to handle multiplication
    thread t1(BruteForceMultiplication, (void *)tM1);
    thread t2(BruteForceMultiplication, (void *)tM2);
    thread t3(BruteForceMultiplication, (void *)tM3);
    thread t4(BruteForceMultiplication, (void *)tM4);
    thread t5(BruteForceMultiplication, (void *)tM5);
    thread t6(BruteForceMultiplication, (void *)tM6);
    thread t7(BruteForceMultiplication, (void *)tM7);
    // Join all threads
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();

    auto* tempA = new SquareMatrix(mid);
    auto* tempB = new SquareMatrix(mid);

    // Calculate: C11
    add(*M5, *M4,*tempA, mid);
    add(*tempA, *M6, *tempB, mid);
    sub(*tempB, *M2, *C11, mid);

    // Calculate: C12
    add(*M1, *M2, *C12, mid);
    // Calculate: C21
    add(*M3, *M4, *C21, mid);
    // Calculate: C22
    add(*M5, *M1, *tempA, mid);
    sub(*tempA, *M3, *tempB, mid);
    sub(*tempB, *M7, *C22, mid);

    // Add sub-matrices data to resultant
    for (int i = 0; i < mid; i++) {
        for (int j = 0; j < mid; j++) {
            C->data[i][j]            = C11->data[i][j];
            C->data[i][j + mid]      = C12->data[i][j];
            C->data[i + mid][j]      = C21->data[i][j];
            C->data[i + mid][j+ mid] = C22->data[i][j];
        }
    }

    return C;
}

void multiply(const SquareMatrix& A, const SquareMatrix& B, SquareMatrix& C, int mid) {
    for (int i = 0; i < mid; i++) {
        for (int j = 0; j < mid; j++) {
            int sum = 0;
            for (int k = 0; k < C.dim; k++) {
                sum += A.data[i][k] * B.data[k][j];
            }
            C.data[i][j] = sum;
        }
    }
}

/*
 * Function Name: add
 * Description:   Adds two matrices' data
 * Return:        void
 * Pre:           Three SquareMatrix structs are passed by reference and an integer is passed by value
 * Post:          Resultant is stored in matrix C
 */
void add(const SquareMatrix& A, const SquareMatrix& B, SquareMatrix& C, int mid) {
    for (int i = 0; i < mid; i++) {
        for (int j = 0; j < mid; j++) {
            C.data[i][j] = A.data[i][j] + B.data[i][j];
        }
    }
}

/*
 * Function Name: sub
 * Description:   Subtracts two matrices' data
 * Return:        void
 * Pre:           Three SquareMatrix structs are passed by reference and an integer is passed by value
 * Post:          Resultant is stored in matrix C
 */
void sub(const SquareMatrix& A, const SquareMatrix& B, SquareMatrix& C, int mid) {
    for (int i = 0; i < mid; i++) {
        for (int j = 0; j < mid; j++) {
            C.data[i][j] = A.data[i][j] - B.data[i][j];
        }
    }
}

/*
 * Function Name: displayMatrix
 * Description:   Function displays the dimension and the matrix's data
 * Return:        void
 * Pre:           SquareMatrix struct passed as pointer
 * Post:          SquareMatrix dimension and data are displayed
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

#endif //PROJECT3_MATRIXMULTIPLICATION_THREADEDMATRIXMULT_H
