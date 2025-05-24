#include "Vector.h"

#include <cassert>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;

//* Constructors
Vector::Vector(int size) {
    //? Vector size must be positive
    assert(size >= 0);

    mSize = size;

    if (mSize == 0) {
        mData = nullptr;
    } else if (mSize > 0) {
        mData = new double[mSize]();
    }
}

Vector::Vector(double array[], int size) {
    //? Vector size must be positive
    assert(size >= 0);

    if (!array) {
        mSize = size;

        if (mSize == 0) {
            mData = nullptr;
        } else if (mSize > 0) {
            mData = new double[mSize]();
        }
    } else {
        mSize = size;
        mData = new double[mSize];

        for (int i = 0; i < mSize; i++) {
            mData[i] = array[i];
        }
    }
}

Vector::Vector(const Vector& other) {
    mSize = other.mSize;

    if (mSize == 0) {
        mData = nullptr;
    } else if (mSize > 0) {
        mData = new double[mSize];

        for (int i = 0; i < mSize; i++) {
            mData[i] = other.mData[i];
        }
    }
}

//* Destructor
Vector::~Vector() {
    delete[] mData;
    mSize = 0;
}

//* Getters
int Vector::getSize() const { return mSize; }
double* Vector::getData() const { return mData; }

//* Assignment Operator
// DOES change original vector
Vector& Vector::operator=(const Vector& other) {
    // Check for self-assignment
    if (this == &other) {
        return *this;
    }

    delete[] mData;

    mSize = other.mSize;

    if (mSize == 0) {
        mData = nullptr;
    } else if (mSize > 0) {
        mData = new double[mSize];

        for (int i = 0; i < mSize; i++) {
            mData[i] = other.mData[i];
        }
    }

    return *this;
}

//* Unary Operators: negative, increment, decrement
//! Negative, DOES NOT change original vector
Vector Vector::operator-() const {
    Vector result(mSize);
    for (int i = 0; i < mSize; i++) {
        result.mData[i] = -mData[i];
    }
    return result;
}

//! Prefix++, DOES change original vector
Vector& Vector::operator++() {
    for (int i = 0; i < mSize; i++) {
        mData[i]++;
    }
    return *this;
}

//! Postfix++, DOES change original vector, but return a copy of old version
Vector Vector::operator++(int) {
    Vector temp = *this;  // Copy current state
    for (int i = 0; i < mSize; i++) {
        mData[i]++;
    }
    return temp;
}

//! Prefix--, DOES change the original vector
Vector& Vector::operator--() {
    for (int i = 0; i < mSize; i++) {
        mData[i]--;
    }
    return *this;
}

//! Postfix--, DOES change the original vector, but return the old-version copy
Vector Vector::operator--(int) {
    Vector temp = *this;  // Copy current state
    for (int i = 0; i < mSize; i++) {
        mData[i]--;
    }
    return temp;
}

//* Binary Operators
// Vector ... const -> return new object
// Vector& ...      -> assign back to current object

//! Addition, DOES NOT change original vector
Vector Vector::operator+(const Vector& other) const {
    //? Vector sizes must match for addition
    assert(mSize == other.mSize);

    Vector result(mSize);

    for (int i = 0; i < mSize; i++) {
        result.mData[i] = mData[i] + other.mData[i];
    }

    return result;
}

//! Addition, DOES change original vector
Vector& Vector::operator+=(const Vector& other) {
    //? Vector sizes must match for addition
    assert(mSize == other.mSize);

    for (int i = 0; i < mSize; i++) {
        mData[i] += other.mData[i];
    }

    return *this;
}

//! Subtraction, DOES NOT change original vector
Vector Vector::operator-(const Vector& other) const {
    //? Vector sizes must match for subtraction
    assert(mSize == other.mSize);

    Vector result(mSize);

    for (int i = 0; i < mSize; i++) {
        result.mData[i] = mData[i] - other.mData[i];
    }

    return result;
}

//! Subtraction, DOES change original vector
Vector& Vector::operator-=(const Vector& other) {
    //? Vector sizes must match for subtraction
    assert(mSize == other.mSize);

    for (int i = 0; i < mSize; i++) {
        mData[i] -= other.mData[i];
    }

    return *this;
}

//! Scalar Multiplication, DOES NOT change original vector
Vector Vector::operator*(double scalar) const {
    Vector result(mSize);

    for (int i = 0; i < mSize; i++) {
        result.mData[i] = mData[i] * scalar;
    }

    return result;
}

//! Scalar Multiplication, DOES change original vector
Vector& Vector::operator*=(double scalar) {
    for (int i = 0; i < mSize; i++) {
        mData[i] *= scalar;
    }

    return *this;
}

//! Dot Product, DOES NOT change original vector
double Vector::operator*(const Vector& other) const {
    //? Vector sizes must match for dot product
    assert(mSize == other.mSize);

    double result = 0;

    for (int i = 0; i < mSize; i++) {
        result += mData[i] * other.mData[i];
    }

    return result;
}

//! Brackets [] ()
double& Vector::operator[](int index) {
    //? Index out of range in operator[]: must be between 0 and (mSize - 1)
    assert(index >= 0 && index < mSize);

    return mData[index];
}

double& Vector::operator()(int index_1) {
    //? Index out of range in operator(): must be between 1 and mSize
    assert(index_1 > 0 && index_1 <= mSize);

    return mData[index_1 - 1];
}

//& If vector is const -> use this
const double& Vector::operator[](int index) const {
    //? Index out of range in operator[]: must be between 0 and (mSize - 1)
    assert(index >= 0 && index < mSize);

    return mData[index];
}

const double& Vector::operator()(int index_1) const {
    //? Index out of range in operator(): must be between 1 and mSize
    assert(index_1 > 0 && index_1 <= mSize);

    return mData[index_1 - 1];
}

//! To String
string Vector::toString() {
    string result = "[";
    for (int i = 0; i < mSize; i++) {
        result += to_string(mData[i]);

        if (i < mSize - 1) {  // if not the last element add ,
            result += ", ";
        }
    }
    result += "]";

    return result;
}
