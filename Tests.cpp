#include "Tests.h"

#include <cmath>
#include <iostream>

#include "LinearSystem.h"
#include "Matrix.h"
#include "PosSymLinSystem.h"
#include "Vector.h"

using namespace std;

bool test1() {
    cout << YELLOW << "TEST 1" << RESET << "\n";

    Vector v(3);
    v(1) = 3;
    v(2) = 1;
    v(3) = 4;
    cout << v.toString() << endl;
    cout << "Expected: [3, 1, 4]\n";

    return v(1) == 3 && v(2) == 1 && v(3) == 4;
}

bool test2() {
    cout << YELLOW << "TEST 2" << RESET << "\n";

    double data[] = {1, 5, 9};
    Vector v(data, 3);
    cout << v.toString() << endl;
    cout << "Expected: [1, 5, 9]\n";

    return v(1) == 1 && v(2) == 5 && v(3) == 9;
}

bool test3() {
    cout << YELLOW << "TEST 3" << RESET << "\n";

    double data[] = {2, 6, 5};
    Vector v1(data, 3);
    Vector v2(v1);
    cout << "v1 = " << v1.toString() << endl;
    cout << "v2 = " << v2.toString() << endl;
    cout << "Expected: v1 == v2\n";

    return v2(1) == 2 && v2(2) == 6 && v2(3) == 5;
}

bool test4() {
    cout << YELLOW << "TEST 4" << RESET << "\n";

    double data[] = {3, 5, 8, 9};
    Vector v(data, 4);
    Vector v1 = -v;
    cout << "v1 = " << v1.toString() << endl;
    cout << "v = " << v.toString() << endl;
    cout << "Expected: v1 = [-3, -5, -8, -9]\n";

    return v1(1) == -3 && v1(2) == -5 && v1(3) == -8 && v1(4) == -9;
}

bool test5() {
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

bool test6() {
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

bool test7() {
    cout << YELLOW << "TEST 7" << RESET << "\n";

    double data1[] = {2, 6, 4, 3};
    Vector v1(data1, 4);
    double data2[] = {3, 8, 3, 2};
    Vector v2(data2, 4);
    Vector v = v1 + v2;
    cout << "v1 = " << v1.toString() << endl;
    cout << "v2 = " << v2.toString() << endl;
    cout << "v = v1 + v2\nv = " << v.toString() << endl;
    cout << "Expected: v = [5, 14, 7, 5]\n";
    Vector vv = v;
    vv += v2;
    cout << "v += v2\nv= " << v.toString() << endl;
    cout << "Expected: v = [8, 22, 10, 7]\n";
    //! TODO: ADD +=

    return v(1) == 5 && v(2) == 14 && v(3) == 7 && v(4) == 5 && vv(1) == 8 &&
           vv(2) == 22 && vv(3) == 10 && vv(4) == 7;
}

bool test8() {
    cout << YELLOW << "TEST 8" << RESET << "\n";

    double data1[] = {2, 6, 4, 3};
    Vector v1(data1, 4);
    double data2[] = {3, 8, 3, 2};
    Vector v2(data2, 4);
    Vector v = v1 - v2;
    cout << "v1 = " << v1.toString() << endl;
    cout << "v2 = " << v2.toString() << endl;
    cout << "v = v1 + v2\nv = " << v.toString() << endl;
    cout << "Expected: v = [-1, -2, 1, 1]\n";
    Vector vv = v;
    vv -= v2;
    cout << "v -= v2\nv =  " << vv.toString() << endl;
    cout << "Expected: v = [-4, -10, -2, -1]\n";

    return v(1) == -1 && v(2) == -2 && v(3) == 1 && v(4) == 1 && vv(1) == -4 &&
           vv(2) == -10 && vv(3) == -2 && vv(4) == -1;
}

bool test9() {
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

bool test10() {
    // NOT IMPLEMENTED
    return true;
}

bool test11() {
    // NOT IMPLEMENTED
    return true;
}

bool test12() {
    // NOT IMPLEMENTED
    return true;
}

bool test13() {
    // NOT IMPLEMENTED
    return true;
}

bool test14() {
    // NOT IMPLEMENTED
    return true;
}

bool test15() {
    // NOT IMPLEMENTED
    return true;
}

bool test16() {
    // NOT IMPLEMENTED
    return true;
}

bool test17() {
    // NOT IMPLEMENTED
    return true;
}

bool test18() {
    // NOT IMPLEMENTED
    return true;
}

bool test19() {
    // NOT IMPLEMENTED
    return true;
}

bool test20() {
    // NOT IMPLEMENTED
    return true;
}

bool test21() {
    // NOT IMPLEMENTED
    return true;
}

bool test22() {
    // NOT IMPLEMENTED
    return true;
}

bool test23() {
    // NOT IMPLEMENTED
    return true;
}

bool test24() {
    // NOT IMPLEMENTED
    return true;
}

bool test25() {
    // NOT IMPLEMENTED
    return true;
}

bool test26() {
    // NOT IMPLEMENTED
    return true;
}

bool test27() {
    // NOT IMPLEMENTED
    return true;
}

bool test28() {
    // NOT IMPLEMENTED
    return true;
}

bool test29() {
    // NOT IMPLEMENTED
    return true;
}

bool test30() {
    // NOT IMPLEMENTED
    return true;
}