#include <math.h>

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

#include "LinearSystem.h"
#include "Matrix.h"
#include "PosSymLinSystem.h"
#include "Tests.h"
#include "Vector.h"

using namespace std;

void testing() {
    bool (*tests[TESTS_COUNT])() = {
        test1,  test2,  test3,  test4,  test5,  test6,  test7,  test8,
        test9,  test10, test11, test12, test13, test14, test15, test16,
        test17, test18, test19, test20, test21, test22, test23, test24,
        test25, test26, test27, test28, test29, test30};

    int testsPassed = 0;
    for (int i = 0; i < TESTS_COUNT; i++) {
        bool passed = tests[i]();
        if (passed) {
            cout << GREEN << "Test " << (i + 1) << " passed" << RESET;
            testsPassed++;
        } else {
            cout << RED << "Test " << (i + 1) << " failed" << RESET;
        }
        cout << "\n\n";
    }

    if (testsPassed == TESTS_COUNT) {
        cout << GREEN;
    } else if (testsPassed == 0) {
        cout << RED;
    } else {
        cout << YELLOW;
    }

    cout << "Total Passed: " << testsPassed << "/" << TESTS_COUNT << "."
         << RESET << "\n";
}

int main() { testing(); }