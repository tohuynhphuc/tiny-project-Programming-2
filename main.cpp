#include <math.h>

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

#include "LinearSystem.cpp"
#include "Matrix.cpp"
#include "PosSymLinSystem.cpp"
#include "Vector.cpp"

using namespace std;

int main() {
    // testing Vector
    Vector v1 = Vector(3);
    double arr[] = {1, 2, 3, 4, 5, 6};
    Vector v2 = Vector(arr, 6);
    double *arr2 = (double *)calloc(6, sizeof(double));
    for (int i = 0; i < 6; i++) {
        arr2[i] = 6 - i;  // [6, 5, 4, 3, 2, 1]
    }
    Vector v3 = Vector(arr2, 6);
    cout << "v1: " << v1.toString() << endl;
    cout << "v2: " << v2.toString() << endl;
    cout << "v3: " << v3.toString() << endl;

    // determinant
    Matrix m2(2, 2);
    m2(1, 1) = 4;
    m2(1, 2) = 6;
    m2(2, 1) = 3;
    m2(2, 2) = 8;
    cout << "Determinant of 2x2 matrix: " << m2.determinant()
         << " (Expected: 14)" << endl;

    // 3x3 matrix test
    Matrix m3(3, 3);
    m3(1, 1) = 6;
    m3(1, 2) = 1;
    m3(1, 3) = 1;
    m3(2, 1) = 4;
    m3(2, 2) = -2;
    m3(2, 3) = 5;
    m3(3, 1) = 2;
    m3(3, 2) = 8;
    m3(3, 3) = 7;
    cout << "Determinant of 3x3 matrix: " << m3.determinant()
         << " (Expected: -306)" << endl;

    // Singular matrix test (should be 0)
    Matrix m4(2, 2);
    m4(1, 1) = 1;
    m4(1, 2) = 2;
    m4(2, 1) = 2;
    m4(2, 2) = 4;
    cout << "Determinant of singular 2x2 matrix: " << m4.determinant()
         << " (Expected: 0)" << endl;
    // 4x4 matrix with mixed values
    Matrix m5(4, 4);
    m5(1, 1) = 1;
    m5(1, 2) = 2;
    m5(1, 3) = 3;
    m5(1, 4) = 4;
    m5(2, 1) = 5;
    m5(2, 2) = 6;
    m5(2, 3) = 7;
    m5(2, 4) = 8;
    m5(3, 1) = 2;
    m5(3, 2) = 6;
    m5(3, 3) = 4;
    m5(3, 4) = 8;
    m5(4, 1) = 3;
    m5(4, 2) = 1;
    m5(4, 3) = 1;
    m5(4, 4) = 2;
    cout << "Determinant of 4x4 matrix: " << m5.determinant()
         << " (Expected: 72)" << endl;

    // 5x5 matrix with zeros and negatives
    Matrix m6(5, 5);
    m6(1, 1) = 0;
    m6(1, 2) = -2;
    m6(1, 3) = 3;
    m6(1, 4) = 0;
    m6(1, 5) = 1;
    m6(2, 1) = 4;
    m6(2, 2) = 0;
    m6(2, 3) = 0;
    m6(2, 4) = -1;
    m6(2, 5) = 2;
    m6(3, 1) = 0;
    m6(3, 2) = 0;
    m6(3, 3) = 0;
    m6(3, 4) = 0;
    m6(3, 5) = 1;
    m6(4, 1) = 1;
    m6(4, 2) = 2;
    m6(4, 3) = 3;
    m6(4, 4) = 4;
    m6(4, 5) = 5;
    m6(5, 1) = -1;
    m6(5, 2) = 1;
    m6(5, 3) = -1;
    m6(5, 4) = 1;
    m6(5, 5) = -1;
    cout << "Determinant of 5x5 matrix: " << m6.determinant()
         << " (Expected: 19)" << endl;

    // 4x4 singular matrix (determinant should be 0)
    Matrix m7(4, 4);
    m7(1, 1) = 2;
    m7(1, 2) = 4;
    m7(1, 3) = 6;
    m7(1, 4) = 8;
    m7(2, 1) = 1;
    m7(2, 2) = 2;
    m7(2, 3) = 3;
    m7(2, 4) = 4;
    m7(3, 1) = 2;
    m7(3, 2) = 4;
    m7(3, 3) = 6;
    m7(3, 4) = 8;
    m7(4, 1) = 3;
    m7(4, 2) = 6;
    m7(4, 3) = 9;
    m7(4, 4) = 12;
    cout << "Determinant of singular 4x4 matrix: " << m7.determinant()
         << " (Expected: 0)" << endl;

    // 4x4 Vandermonde matrix (det = (b-a)*(c-a)*(d-a)*(c-b)*(d-b)*(d-c))
    double a = 1, b = 2, c = 3, d = 4;
    Matrix m8(4, 4);
    m8(1, 1) = 1;
    m8(1, 2) = a;
    m8(1, 3) = a * a;
    m8(1, 4) = a * a * a;
    m8(2, 1) = 1;
    m8(2, 2) = b;
    m8(2, 3) = b * b;
    m8(2, 4) = b * b * b;
    m8(3, 1) = 1;
    m8(3, 2) = c;
    m8(3, 3) = c * c;
    m8(3, 4) = c * c * c;
    m8(4, 1) = 1;
    m8(4, 2) = d;
    m8(4, 3) = d * d;
    m8(4, 4) = d * d * d;
    cout << "Determinant of 4x4 Vandermonde matrix: " << m8.determinant()
         << " (Expected: 12)" << endl;

    // 6x6 diagonal matrix (det = product of diagonal)
    Matrix m9(6, 6);
    for (int i = 1; i <= 6; i++)
        for (int j = 1; j <= 6; j++) m9(i, j) = (i == j) ? i : 0;
    cout << "Determinant of 6x6 diagonal matrix: " << m9.determinant()
         << " (Expected: 720)" << endl;

    // 5x5 identity matrix (det = 1)
    Matrix m10(5, 5);
    for (int i = 1; i <= 5; i++)
        for (int j = 1; j <= 5; j++) m10(i, j) = (i == j) ? 1 : 0;
    cout << "Determinant of 5x5 identity matrix: " << m10.determinant()
         << " (Expected: 1)" << endl;

    Matrix m11(3, 3);
    m11(1, 1) = 4;
    m11(1, 2) = 7;
    m11(1, 3) = 2;
    m11(2, 1) = 3;
    m11(2, 2) = 6;
    m11(2, 3) = 1;
    m11(3, 1) = 2;
    m11(3, 2) = 5;
    m11(3, 3) = 1;
    Matrix m12 = m11.inverse();
    cout << "Determinant of matrix: " << m11.determinant()
         << " and of inverse matrix: " << m12.determinant()
         << " (Expected: 3, 1/3)" << endl;
    cout << "Inverse: " << m12.toString() << endl;

    // Test LinearSystem (Gaussian elimination)
    Matrix A1(3, 3);
    A1(1, 1) = 2;
    A1(1, 2) = 1;
    A1(1, 3) = -1;
    A1(2, 1) = -3;
    A1(2, 2) = -1;
    A1(2, 3) = 2;
    A1(3, 1) = -2;
    A1(3, 2) = 1;
    A1(3, 3) = 2;

    double b1_arr[] = {8, -11, -3};
    Vector b1(b1_arr, 3);

    LinearSystem sys1(&A1, &b1);
    Vector x1 = sys1.Solve();
    cout << "LinearSystem::Solve() solution: " << x1.toString()
         << " (Expected: [2, 3, -1])" << endl;

    // Test PosSymLinSystem (Conjugate Gradient)
    // Test PosSymLinSystem (Conjugate Gradient)
    // Matrix A2(2, 2);
    // A2(1, 1) = 4;
    // A2(1, 2) = 1;
    // A2(2, 1) = 1;
    // A2(2, 2) = 3;

    // double b2_arr[] = {1, 2};
    // Vector b2(b2_arr, 2);

    // PosSymLinSystem sys2(&A2, &b2);
    // Vector x2 = sys2.Solve();
    // cout << "PosSymLinSystem::Solve() solution: " << x2.toString() << "
    // (Expected: [0.090909, 0.636364])" << endl;
    return 0;
}