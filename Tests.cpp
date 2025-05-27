#include "Tests.h"

#include <cmath>
#include <iostream>

#include "LinearSystem.h"
#include "Matrix.h"
#include "PosSymLinSystem.h"
#include "Vector.h"

#define DELTA 0.01

using namespace std;

bool compare(double a, double b) { return abs(a - b) <= DELTA; }

bool test1()
{
    cout << YELLOW << "TEST 1" << RESET << "\n";

    Vector v(3);
    v(1) = 3;
    v(2) = 1;
    v(3) = 4;

    cout << v.toString() << endl;
    cout << "Expected: [3, 1, 4]\n";

    return v(1) == 3 && v(2) == 1 && v(3) == 4;
}

bool test2()
{
    cout << YELLOW << "TEST 2" << RESET << "\n";

    double data[] = {1, 5, 9};
    Vector v(data, 3);

    cout << v.toString() << endl;
    cout << "Expected: [1, 5, 9]\n";

    return v(1) == 1 && v(2) == 5 && v(3) == 9;
}

bool test3()
{
    cout << YELLOW << "TEST 3" << RESET << "\n";

    double data[] = {2, 6, 5};
    Vector v1(data, 3);
    Vector v2(v1);

    cout << "v1 = " << v1.toString() << endl;
    cout << "v2 = " << v2.toString() << endl;
    cout << "Expected: v1 == v2\n";

    return v2(1) == 2 && v2(2) == 6 && v2(3) == 5;
}

bool test4()
{
    cout << YELLOW << "TEST 4" << RESET << "\n";

    double data[] = {3, 5, 8, 9};
    Vector v(data, 4);
    Vector v1 = -v;

    cout << "v1 = " << v1.toString() << endl;
    cout << "v = " << v.toString() << endl;
    cout << "Expected: v1 = [-3, -5, -8, -9]\n";

    return v1(1) == -3 && v1(2) == -5 && v1(3) == -8 && v1(4) == -9;
}

bool test5()
{
    cout << YELLOW << "TEST 5" << RESET << "\n";

    double data[] = {7, 9, 3, 2, 3};
    Vector v(data, 5);
    Vector v1 = ++v;
    Vector v2 = v++;

    cout << "v1 = " << v1.toString() << endl;
    cout << "v2 = " << v2.toString() << endl;
    cout << "v = " << v.toString() << endl;
    cout << "Expected: v1 = v2 = [8, 10, 4, 3, 4]; v = [9, 11, 5, 4, 5]\n";

    return v1(1) == 8 && v2(1) == 8 && v(1) == 9;
}

bool test6()
{
    cout << YELLOW << "TEST 6" << RESET << "\n";

    double data[] = {8, 4, 6};
    Vector v(data, 3);
    Vector v1 = --v;
    Vector v2 = v--;

    cout << "v1 = " << v1.toString() << endl;
    cout << "v2 = " << v2.toString() << endl;
    cout << "v = " << v.toString() << endl;
    cout << "Expected: v1 = v2 = [7, 4, 5]; v = [6, 3, 4]\n";

    return v1(1) == 7 && v2(1) == 7 && v(1) == 6;
}

bool test7()
{
    cout << YELLOW << "TEST 7" << RESET << "\n";

    double data1[] = {2, 6, 4, 3};
    Vector v1(data1, 4);
    double data2[] = {3, 8, 3, 2};
    Vector v2(data2, 4);
    Vector v = v1 + v2;
    Vector vv = v;
    vv += v2;

    cout << "v1 = " << v1.toString() << endl;
    cout << "v2 = " << v2.toString() << endl;
    cout << "v = v1 + v2\nv = " << v.toString() << endl;
    cout << "Expected: v = [5, 14, 7, 5]\n";
    cout << "v += v2\nv= " << v.toString() << endl;
    cout << "Expected: v = [8, 22, 10, 7]\n";

    return v(1) == 5 && v(2) == 14 && v(3) == 7 && v(4) == 5 && vv(1) == 8 &&
           vv(2) == 22 && vv(3) == 10 && vv(4) == 7;
}

bool test8()
{
    cout << YELLOW << "TEST 8" << RESET << "\n";

    double data1[] = {2, 6, 4, 3};
    Vector v1(data1, 4);
    double data2[] = {3, 8, 3, 2};
    Vector v2(data2, 4);
    Vector v = v1 - v2;
    Vector vv = v;
    vv -= v2;

    cout << "v1 = " << v1.toString() << endl;
    cout << "v2 = " << v2.toString() << endl;
    cout << "v = v1 + v2\nv = " << v.toString() << endl;
    cout << "Expected: v = [-1, -2, 1, 1]\n";
    cout << "v -= v2\nv =  " << vv.toString() << endl;
    cout << "Expected: v = [-4, -10, -2, -1]\n";

    return v(1) == -1 && v(2) == -2 && v(3) == 1 && v(4) == 1 && vv(1) == -4 &&
           vv(2) == -10 && vv(3) == -2 && vv(4) == -1;
}

bool test9()
{
    cout << YELLOW << "TEST 9" << RESET << "\n";

    double data1[] = {2, 6, 4, 3};
    Vector v1(data1, 4);
    double data2[] = {3, 8, 3, 2};
    Vector v2(data2, 4);
    double v = v1 * v2;
    v1 *= 5;
    cout << "5 * v1 = " << v1.toString() << endl;
    cout << "v2 = " << v2.toString() << endl;
    cout << "v = v1 * v2 = " << v << endl;
    cout << "Expected: v1 = [10, 30, 20, 15]; v = 72\n";

    return v1(1) == 10 && v1(2) == 30 && v1(3) == 20 && v1(4) == 15 && v == 72;
}

bool test10()
{
    cout << YELLOW << "TEST 10" << RESET << "\n";

    Matrix m(2, 2);
    m(1, 1) = 7;
    m(1, 2) = 9;
    m(2, 1) = 5;
    m(2, 2) = 0;

    cout << m.toString() << endl;
    cout << "Expected: [[7, 9], [5, 0]]\n";

    return m(1, 1) == 7 && m(1, 2) == 9 && m(2, 1) == 5 && m(2, 2) == 0;
}

bool test11()
{
    cout << YELLOW << "TEST 11" << RESET << "\n";

    double **data = new double *[2];
    data[0] = new double[2]{2, 8};
    data[1] = new double[2]{8, 4};
    Matrix m(data, 2, 2);

    cout << m.toString() << endl;
    cout << "Expected: [[2, 8], [8, 4]]\n";

    return m(1, 1) == 2 && m(1, 2) == 8 && m(2, 1) == 8 && m(2, 2) == 4;
}
/*

cout << YELLOW << "TEST 9" << RESET << "\n";

    // 2x3 pseudo-inverse matrix test
    Matrix m3(2, 3);
    m3(1, 1) = 5;
    m3(1, 2) = -8;
    m3(1, 3) = 2;
    m3(2, 1) = 0;
    m3(2, 2) = 7;
    m3(2, 3) = -2;
    cout << "Pseudo-inverse of m3: " << m3.pseudoInverse().toString() << endl;
    cout << "Expected: [[0.199398043641836, 0.225733634311512]," << endl;
    cout << "	[−0.00300978179082, 0.128668171557562]," << endl;
    cout << "	[−0.010534236267871, −0.049661399548533]]" << endl;

    // 5x3 pseudo-inverse matrix test
    Matrix m4(5, 3);
    m4(1, 1) = 5;
    m4(1, 2) = -8;
    m4(1, 3) = 2;
    m4(2, 1) = 0;
    m4(2, 2) = 7;
    m4(2, 3) = -2;
    m4(3, 1) = 2;
    m4(3, 2) = 9;
    m4(3, 3) = -3;
    m4(4, 1) = -4;
    m4(4, 2) = -1;
    m4(4, 3) = 8;
    m4(5, 1) = 0;
    m4(5, 2) = 0;
    m4(5, 3) = -3;
    cout << "Pseudo-inverse of m4: " << m4.pseudoInverse().toString() << endl;
    cout << "Expected: [[0.148736738954454, 0.030732961242952,
0.107139306662122, -0.010509422975871, -0.056495249456776]," << endl; cout << "
[−0.005879596097312, 0.045457514947524, 0.073813074290259, 0.02955704202349,
-0.029219036257509]," << endl; cout << "	[0.064249499382216,
0.020169570959908, 0.053308337948958, 0.10696604320225, -0.07201227046142]]" <<
endl;

    return true;
*/

bool test12()
{
    cout << YELLOW << "TEST 12" << RESET << "\n";

    double **data = new double *[2];
    data[0] = new double[2]{1, 9};
    data[1] = new double[2]{7, 1};
    Matrix m1(data, 2, 2);
    Matrix m(m1);

    cout << m.toString() << endl;
    cout << "Expected: [[1, 9], [7, 1]]\n";

    return m(1, 1) == 1 && m(1, 2) == 9 && m(2, 1) == 7 && m(2, 2) == 1;
}

bool test13()
{
    cout << YELLOW << "TEST 13" << RESET << "\n";

    double **data = new double *[2];
    data[0] = new double[2]{3, 5};
    data[1] = new double[2]{8, 9};
    Matrix m(data, 2, 2);
    Matrix m1 = -m;

    cout << "m1 = \n"
         << m1.toString() << endl;
    cout << "m = \n"
         << m.toString() << endl;
    cout << "Expected: m1 = [[-3, -5], [-8, -9]]\n";

    return m1(1, 1) == -3 && m1(1, 2) == -5 && m1(2, 1) == -8 && m1(2, 2) == -9;
}

bool test14()
{
    cout << YELLOW << "TEST 14" << RESET << "\n";

    double **data = new double *[2];
    data[0] = new double[2]{7, 9};
    data[1] = new double[2]{3, 2};
    Matrix m(data, 2, 2);
    Matrix m1 = ++m;
    Matrix m2 = m++;

    cout << "m1 = \n"
         << m1.toString() << endl;
    cout << "m2 = \n"
         << m2.toString() << endl;
    cout << "m = \n"
         << m.toString() << endl;
    cout << "Expected: m1 = m2 = [[8, 10], [4, 3]]; m = [[9, 11], [5, 4]]\n";

    return m1(1, 1) == 8 && m2(1, 1) == 8 && m(1, 1) == 9;
}

bool test15()
{
    cout << YELLOW << "TEST 15" << RESET << "\n";

    double **data = new double *[2];
    data[0] = new double[2]{7, 9};
    data[1] = new double[2]{3, 2};
    Matrix m(data, 2, 2);
    Matrix m1 = --m;
    Matrix m2 = m--;

    cout << "m1 = \n"
         << m1.toString() << endl;
    cout << "m2 = \n"
         << m2.toString() << endl;
    cout << "m = \n"
         << m.toString() << endl;
    cout << "Expected: m1 = m2 = [[6, 8], [2, 1]]; m = [[5, 7], [1, 0]]\n";

    return m1(1, 1) == 6 && m2(1, 1) == 6 && m(1, 1) == 5;
}

bool test16()
{
    cout << YELLOW << "TEST 16" << RESET << "\n";

    double **data1 = new double *[2];
    data1[0] = new double[2]{10, 10};
    data1[1] = new double[2]{10, 10};
    Matrix m1(data1, 2, 2);

    double **data2 = new double *[2];
    data2[0] = new double[2]{1, 2};
    data2[1] = new double[2]{3, 5};
    Matrix m2(data2, 2, 2);
    Matrix m3 = m1 + m2;
    Matrix m4 = m1;
    m4 += m2;

    cout << "m3 = \n"
         << m3.toString() << endl;
    cout << "m4 = \n"
         << m4.toString() << endl;
    cout << "Expected: m3 = m4 = [[11, 12], [13, 15]]\n";

    return m3(1, 1) == 11 && m3(1, 2) == 12 && m3(2, 1) == 13 &&
           m3(2, 2) == 15 && m4(1, 1) == 11 && m4(1, 2) == 12 &&
           m4(2, 1) == 13 && m4(2, 2) == 15;
}

bool test17()
{
    cout << YELLOW << "TEST 17" << RESET << "\n";

    double **data1 = new double *[2];
    data1[0] = new double[2]{10, 10};
    data1[1] = new double[2]{10, 10};
    Matrix m1(data1, 2, 2);

    double **data2 = new double *[2];
    data2[0] = new double[2]{1, 2};
    data2[1] = new double[2]{3, 5};
    Matrix m2(data2, 2, 2);
    Matrix m3 = m1 - m2;
    Matrix m4 = m1;
    m4 -= m2;

    cout << "m3 = \n"
         << m3.toString() << endl;
    cout << "m4 = \n"
         << m4.toString() << endl;
    cout << "Expected: m3 = m4 = [[9, 8], [7, 5]]\n";

    return m3(1, 1) == 9 && m3(1, 2) == 8 && m3(2, 1) == 7 && m3(2, 2) == 5 &&
           m4(1, 1) == 9 && m4(1, 2) == 8 && m4(2, 1) == 7 && m4(2, 2) == 5;
}

bool test18()
{
    cout << YELLOW << "TEST 18" << RESET << "\n";

    double **data1 = new double *[2];
    data1[0] = new double[2]{2, 4};
    data1[1] = new double[2]{6, 8};
    Matrix m1(data1, 2, 2);

    double **data2 = new double *[2];
    data2[0] = new double[2]{1, 2};
    data2[1] = new double[2]{3, 5};
    Matrix m2(data2, 2, 2);
    Matrix m3 = m1 * m2;
    Matrix m4 = m1;
    m4 *= m2;

    cout << "m3 = \n"
         << m3.toString() << endl;
    cout << "m4 = \n"
         << m4.toString() << endl;
    cout << "Expected: m3 = m4 = [[14, 24], [30, 52]]\n";

    return m3(1, 1) == 14 && m3(1, 2) == 24 && m3(2, 1) == 30 &&
           m3(2, 2) == 52 && m4(1, 1) == 14 && m4(1, 2) == 24 &&
           m4(2, 1) == 30 && m4(2, 2) == 52;
}

bool test19()
{
    cout << YELLOW << "TEST 19" << RESET << "\n";

    double **data1 = new double *[2];
    data1[0] = new double[2]{2, 4};
    data1[1] = new double[2]{6, 8};
    Matrix m1(data1, 2, 2);

    double data2[] = {5, 10};
    Vector v(data2, 2);
    Vector v3 = m1 * v;
    Matrix m4 = m1;
    m4 *= v;

    cout << "v3 = \n"
         << v3.toString() << endl;
    cout << "m4 = \n"
         << m4.toString() << endl;
    cout << "Expected: v3 = m4 = [50, 110]\n";

    return v3(1) == 50 && v3(2) == 110 && m4(1, 1) == 50 && m4(2, 1) == 110 &&
           m4.getNumCols() == 1 && m4.getNumRows() == 2;
}

bool test20()
{
    cout << YELLOW << "TEST 20" << RESET << "\n";

    double **data1 = new double *[2];
    data1[0] = new double[2]{1, 2};
    data1[1] = new double[2]{3, 5};
    Matrix m1(data1, 2, 2);
    double k = 1.5;
    Matrix m2 = m1 * k;
    Matrix m3 = m1;
    m3 *= k;

    cout << "m2 = \n"
         << m2.toString() << endl;
    cout << "m3 = \n"
         << m3.toString() << endl;
    cout << "Expected: m2 = m3 = [[1.5, 3], [4.5, 7.5]]\n";

    return m2(1, 1) == 1.5 && m2(1, 2) == 3 && m2(2, 1) == 4.5 &&
           m2(2, 2) == 7.5 && m3(1, 1) == 1.5 && m3(1, 2) == 3 &&
           m3(2, 1) == 4.5 && m3(2, 2) == 7.5;
}

bool test21()
{
    cout << YELLOW << "TEST 21" << RESET << "\n";

    double **data1 = new double *[4];
    data1[0] = new double[4]{3, 1, 4, 1};
    data1[1] = new double[4]{5, 9, 2, 6};
    data1[2] = new double[4]{5, 3, 5, 8};
    data1[3] = new double[4]{9, 7, 9, 3};
    Matrix m1(data1, 4, 4);

    float d = m1.determinant();
    Matrix m4(2, 2);
    m4(1, 1) = 1;
    m4(1, 2) = 2;
    m4(2, 1) = 2;
    m4(2, 2) = 4;
    float d4 = m4.determinant();

    cout << "det (\n"
         << m1.toString() << "\n) = " << d << "\n";
    cout << "Expected: 98\n";
    cout << "det (\n"
         << m4.toString() << "\n) = " << d4 << "\n";
    cout << "Expected: 0\n";
    return d == 98 && d4 == 0;
}

bool test22()
{
    cout << YELLOW << "TEST 22" << RESET << "\n";

    double **data1 = new double *[4];
    data1[0] = new double[4]{3, 1, 4, 1};
    data1[1] = new double[4]{5, 9, 2, 6};
    data1[2] = new double[4]{5, 3, 5, 8};
    data1[3] = new double[4]{9, 7, 9, 3};
    Matrix m1(data1, 4, 4);
    Matrix inverse = m1.inverse();

    cout << "Inverse = \n"
         << inverse.toString() << "\n";
    cout << "Expected: \n[[-4.77, -1.26, 0.81, 1.95],\n [1.74, 0.58, -0.40, "
            "-0.68],\n [3.33, 0.78, -0.53, -1.24],\n [0.24, 0.08, 0.10, "
            "-0.18]]\n";

    return compare(inverse(1, 1), -4.77) && compare(inverse(1, 2), -1.26) &&
           compare(inverse(1, 3), 0.81) && compare(inverse(1, 4), 1.95) &&
           compare(inverse(2, 1), 1.74) && compare(inverse(2, 2), 0.58) &&
           compare(inverse(2, 3), -0.40) && compare(inverse(2, 4), -0.68) &&
           compare(inverse(3, 1), 3.33) && compare(inverse(3, 2), 0.78) &&
           compare(inverse(3, 3), -0.53) && compare(inverse(3, 4), -1.24) &&
           compare(inverse(4, 1), 0.24) && compare(inverse(4, 2), 0.08) &&
           compare(inverse(4, 3), 0.10) && compare(inverse(4, 4), -0.18);
}

bool test23()
{
    cout << YELLOW << "TEST 23" << RESET << "\n";

    double **data1 = new double *[4];
    data1[0] = new double[4]{3, 1, 4, 1};
    data1[1] = new double[4]{5, 9, 2, 6};
    data1[2] = new double[4]{5, 3, 5, 8};
    data1[3] = new double[4]{9, 7, 9, 3};
    Matrix m1(data1, 4, 4);
    m1 = m1.transpose();

    double **data2 = new double *[4];
    data2[0] = new double[4]{3, 5, 5, 9};
    data2[1] = new double[4]{1, 9, 3, 7};
    data2[2] = new double[4]{4, 2, 5, 9};
    data2[3] = new double[4]{1, 6, 8, 3};
    Matrix m2(data2, 4, 4);

    cout << m1.toString();
    cout
        << "\nExpected: \n[[3, 5, 5, 9],\n [1, 9, 3, 7],\n [4, 2, 5, 9],\n [1, "
           "6, 8, 3]]\n";

    return m1(1, 1) == m2(1, 1) && m1(1, 2) == m2(1, 2) &&
           m1(1, 3) == m2(1, 3) && m1(1, 4) == m2(1, 4) &&
           m1(2, 1) == m2(2, 1) && m1(2, 2) == m2(2, 2) &&
           m1(2, 3) == m2(2, 3) && m1(2, 4) == m2(2, 4) &&
           m1(3, 1) == m2(3, 1) && m1(3, 2) == m2(3, 2) &&
           m1(3, 3) == m2(3, 3) && m1(3, 4) == m2(3, 4) &&
           m1(4, 1) == m2(4, 1) && m1(4, 2) == m2(4, 2) &&
           m1(4, 3) == m2(4, 3) && m1(4, 4) == m2(4, 4);
}

bool test24()
{
    cout << YELLOW << "TEST 24" << RESET << "\n";

    double **data1 = new double *[2];
    data1[0] = new double[3]{3, 1, 4};
    data1[1] = new double[3]{1, 5, 9};
    Matrix m1(data1, 2, 3);
    Matrix inverse = m1.pseudoInverse();

    double **dataOutput = new double *[3];
    dataOutput[0] = new double[2]{0.33, -0.13};
    dataOutput[1] = new double[2]{-0.13, 0.10};
    dataOutput[2] = new double[2]{0.04, 0.07};
    Matrix expectedOutput(dataOutput, 3, 2);

    cout << "Pseudo-Inverse = \n"
         << inverse.toString() << "\n";
    cout << "Expected: \n"
         << expectedOutput.toString() << "\n";

    return compare(inverse(1, 1), expectedOutput(1, 1)) &&
           compare(inverse(1, 2), expectedOutput(1, 2)) &&
           compare(inverse(2, 1), expectedOutput(2, 1)) &&
           compare(inverse(2, 2), expectedOutput(2, 2)) &&
           compare(inverse(3, 1), expectedOutput(3, 1)) &&
           compare(inverse(3, 2), expectedOutput(3, 2));
}

bool test25()
{
    cout << YELLOW << "TEST 25" << RESET << "\n";

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
    LinearSystem sys2(sys1);
    Vector x1 = sys2.Solve();

    cout << "Solution: " << x1.toString() << "\nExpected: [2, 3, -1]" << endl;
    return compare(x1(1), 2) && compare(x1(2), 3) && compare(x1(3), -1);
}

bool test26()
{
    cout << YELLOW << "TEST 26" << RESET << "\n";

    double **data1 = new double *[3];
    data1[0] = new double[2]{7, 8};
    data1[1] = new double[3]{4, 6};
    data1[2] = new double[3]{5, 0};
    Matrix A(data1, 3, 2);

    double dataB[] = {1, -2, 4};
    Vector b(dataB, 3);

    LinearSystem sys(&A, &b);
    Vector x = sys.Solve();  // redirects to SolveLeastSquare()

    cout << "Solution: " << x.toString() << "\nExpected: [0.85, -0.72]" << endl;
    return compare(x(1), 0.85) && compare(x(2), -0.72);
}

bool test27()
{
    cout << YELLOW << "TEST 27" << RESET << "\n";

    double **data1 = new double *[1];
    data1[0] = new double[3]{1, 2, 3};
    Matrix A(data1, 1, 3);

    double dataB[] = {1};
    Vector b(dataB, 1);

    LinearSystem sys(&A, &b);
    Vector x = sys.Solve();  // redirects to SolveMinimumNorm()

    cout << "Solution: " << x.toString() << "\nExpected: [0.07, 0.14, 0.21]"
         << endl;
    return compare(x(1), 0.07) && compare(x(2), 0.14) && compare(x(3), 0.21);
}

bool test28()
{
    cout << YELLOW << "TEST 28" << RESET << "\n";
    Matrix A_spd(2, 2);
    A_spd(1, 1) = 4;
    A_spd(1, 2) = 1;
    A_spd(2, 1) = 1;
    A_spd(2, 2) = 3;

    double b_spd_arr[] = {1, 2};
    Vector b_spd(b_spd_arr, 2);

    PosSymLinSystem sys_spd(&A_spd, &b_spd);

    cout << sys_spd.isSymmetric() << endl;

    Vector x_spd = sys_spd.Solve();

    cout << "x = " << x_spd.toString() << "\nExpected: [0.09, 0.64]\n";
    return compare(x_spd(1), 0.09) && compare(x_spd(2), 0.63);
}

bool test29() {
    cout << YELLOW << "TEST 29" << RESET << "\n";

    double** data = new double*[3];
    data[0] = new double[3]{25, 15, -5};
    data[1] = new double[3]{15, 18, 0};
    data[2] = new double[3]{-5, 0, 11};
    Matrix A(data, 3, 3);

    double b_arr[] = {5, 10, 15};
    Vector b(b_arr, 3);

    PosSymLinSystem sys(&A, &b);
    Vector x = sys.Solve();
    cout << "x = " << x.toString() << "\nExpected: [0.34, 0.27, 1.52]\n";

    return true;
}

bool test30()
{
    cout << YELLOW << "TEST 30 " << RESET << "\n";
    return true;
}