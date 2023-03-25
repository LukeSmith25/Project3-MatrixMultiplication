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
#include <vector>
#include <chrono>
#include <iomanip>
#include "ThreadedMatrixMult.h"
using namespace std;
using namespace chrono;

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
    cout << endl << "TESTING: BruteForce" << endl;
    SquareMatrix* resultant1;
    {
        vector<decltype(high_resolution_clock::now() - high_resolution_clock::now())> data;
        for (int m = 0; m < 20; m++) {
            auto start = high_resolution_clock::now();

            resultant1 = BruteForce(*matrixA, *matrixB);

            auto stop = high_resolution_clock::now();
            // Change micro to milli after changing size
            data.emplace_back(duration_cast<microseconds>(stop - start));
        }
        double average = 0;

        for (auto i: data) {
            average += i.count();
        }
        average /= data.size();

        cout << setprecision(20) << average << endl;
    }
    displayMatrix(resultant1);


    // Test ThreadedDivideAndConquer
    cout << endl << "TESTING: ThreadedDivideAndConquer" << endl;
    SquareMatrix* resultant2;
    {
        vector<decltype(high_resolution_clock::now() - high_resolution_clock::now())> data;
        for (int m = 0; m < 20; m++) {
            auto start = high_resolution_clock::now();

            resultant2 = ThreadedDivideAndConquer(*matrixA, *matrixB);

            auto stop = high_resolution_clock::now();
            // Change micro to milli after changing size
            data.emplace_back(duration_cast<microseconds>(stop - start));
        }
        double average = 0;

        for (auto i: data) {
            average += i.count();
        }
        average /= data.size();

        cout << setprecision(20) << average << endl;
    }
    //SquareMatrix* resultant2 = ThreadedDivideAndConquer(*matrixA, *matrixB);
    displayMatrix(resultant2);

    // Test Strassen
    cout << endl << "TESTING: Strassen" << endl;
    SquareMatrix* resultant3;
    {
        vector<decltype(high_resolution_clock::now() - high_resolution_clock::now())> data;
        for (int m = 0; m < 20; m++) {
            auto start = high_resolution_clock::now();

            resultant3 = Strassen(*matrixA, *matrixB);

            auto stop = high_resolution_clock::now();
            // Change micro to milli after changing size
            data.emplace_back(duration_cast<microseconds>(stop - start));
        }
        double average = 0;

        for (auto i: data) {
            average += i.count();
        }
        average /= data.size();

        cout << setprecision(20) << average << endl;
    }
    displayMatrix(resultant3);

    // Test Threaded Strassen

    cout << endl << "TESTING: Threaded Strassen" << endl;
    SquareMatrix* resultant4;
    {
        vector<decltype(high_resolution_clock::now() - high_resolution_clock::now())> data;
        for (int m = 0; m < 20; m++) {
            auto start = high_resolution_clock::now();

            resultant4 = ThreadedStrassen(*matrixA, *matrixB);

            auto stop = high_resolution_clock::now();
            // Change micro to milli after changing size
            data.emplace_back(duration_cast<microseconds>(stop - start));
        }
        double average = 0;

        for (auto i: data) {
            average += i.count();
        }
        average /= data.size();

        cout << setprecision(20) << average << endl;
    }
    displayMatrix(resultant4);


    return 0;
}
