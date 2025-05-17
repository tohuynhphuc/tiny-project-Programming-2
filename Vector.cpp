#include "Vector.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;

// Constructor
Vector::Vector(int size) {
    if (size < 0) {
        throw std::invalid_argument("Vector sizes must be non-negative.");
    }

    mSize = size;

    if (mSize == 0) {
        mData = nullptr;
    } else if (mSize > 0) {
        mData = new double[mSize]();
    }
}
Vector::Vector(double array[], int size) {
    if (!array || size <= 0) {
        Vector(0);  // if empty array, create default vector
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

// Destructor
Vector::~Vector() {
    delete[] mData;
    mSize = 0;
}

// Assignment Operator
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

// Unary Operator: negative, increment, decrement
// DOES NOT change original vector
Vector Vector::operator-() const {
    Vector result = Vector(mSize);
    for (int i = 0; i < mSize; i++) {
        result.mData[i] = -this->mData[i];
    }

    return result;
}

// Binary Operator
// Vector ... const -> return new object
// Vector& ...      -> assign back to current object

// DOES NOT change original vector
Vector Vector::operator+(const Vector& other) const {
    if (mSize != other.mSize) {
        throw std::invalid_argument("Vector sizes must match for addition.");
    }

    Vector result = Vector(mSize);

    for (int i = 0; i < mSize; i++) {
        result.mData[i] = mData[i] + other.mData[i];
    }

    return result;
}

// DOES change original vector
Vector& Vector::operator+=(const Vector& other) {
    if (mSize != other.mSize) {
        throw std::invalid_argument("Vector sizes must match for addition.");
    }

    for (int i = 0; i < mSize; i++) {
        mData[i] += other.mData[i];
    }

    return *this;
}

// DOES NOT change original vector
Vector Vector::operator-(const Vector& other) const {
    if (mSize != other.mSize) {
        throw std::invalid_argument("Vector sizes must match for subtraction.");
    }

    Vector result = Vector(mSize);

    for (int i = 0; i < mSize; i++) {
        result.mData[i] = mData[i] - other.mData[i];
    }

    return result;
}

// DOES change original vector
Vector& Vector::operator-=(const Vector& other) {
    if (mSize != other.mSize) {
        throw std::invalid_argument("Vector sizes must match for subtraction.");
    }

    for (int i = 0; i < mSize; i++) {
        mData[i] -= other.mData[i];
    }

    return *this;
}

// DOES NOT change original vector
Vector Vector::operator*(double scalar) const {
    Vector result = Vector(mSize);

    for (int i = 0; i < mSize; i++) {
        result.mData[i] = mData[i] * scalar;
    }

    return result;
}

// DOES change original vector
Vector& Vector::operator*=(double scalar) {
    for (int i = 0; i < mSize; i++) {
        mData[i] *= scalar;
    }

    return *this;
}

// Dot Product (maybe?)
// DOES NOT change original vector
double Vector::operator*(const Vector& other) const {
    if (mSize != other.mSize) {
        throw std::invalid_argument("Vector sizes must match for dot product.");
    }

    double result = 0;

    for (int i = 0; i < mSize; i++) {
        result += mData[i] * other.mData[i];
    }

    return result;
}

// [] ()
double& Vector::operator[](int index) {
    if (index < 0 || index >= mSize) {
        throw std::out_of_range(
            "Index out of range in operator[]: must be between 0 and " +
            std::to_string(mSize - 1));
    }

    return mData[index];
}
double& Vector::operator()(int index_1) {
    if (index_1 < 1 || index_1 > mSize) {
        throw std::out_of_range(
            "Index out of range in operator(): must be between 1 and " +
            std::to_string(mSize));
    }

    return mData[index_1 - 1];
}

// If vector is const -> use this
const double& Vector::operator[](int index) const {
    if (index < 0 || index >= mSize) {
        throw std::out_of_range(
            "Index out of range in operator[]: must be between 0 and " +
            std::to_string(mSize - 1));
    }

    return mData[index];
}
const double& Vector::operator()(int index_1) const {
    if (index_1 < 1 || index_1 > mSize) {
        throw std::out_of_range(
            "Index out of range in operator(): must be between 1 and " +
            std::to_string(mSize));
    }

    return mData[index_1 - 1];
}

// toString
std::string Vector::toString() {
    string result = "[";
    for (int i = 0; i < mSize; i++) {
        result += to_string(mData[i]);

        if (i < mSize - 1) {  // if not the last element, add ,
            result += ", ";
        }
    }
    result += "]";

    return result;
}
