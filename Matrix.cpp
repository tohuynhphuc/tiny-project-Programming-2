#include "Matrix.h"

#include <cassert>
#include <iostream>
#include <stdexcept>

using namespace std;

// Allocate memory before copying the entries
// of the original matrix into the new matrix
void Matrix::allocateMemory(int rows, int cols) {
    mData = new double*[rows];
    for (int i = 0; i < rows; i++) {
        mData[i] = new double[cols];
    }
}

// Default: rows = 1, cols = 1
Matrix::Matrix(int rows = 1, int cols = 1) {
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument(
            "Matrix dimensions must be positive integers.");
    }
    mNumRows = rows;
    mNumCols = cols;

    allocateMemory(mNumRows, mNumCols);

    // Initialize the matrix with 0
    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            mData[i][j] = 0.0;
        }
    }
}

Matrix::Matrix(const Matrix& other) {
    mNumRows = other.mNumRows;
    mNumCols = other.mNumCols;
    allocateMemory(mNumRows, mNumCols);

    // Copy to new matrix
    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            mData[i][j] = other.mData[i][j];
        }
    }
}

// Destructor to free the allocated memory
Matrix::~Matrix() {
    for (int i = 0; i < mNumRows; i++) {
        delete[] mData[i];
    }
    delete[] mData;
}

// Access to the number of rows and columns
int Matrix::getNumRows() const { return mNumRows; }

int Matrix::getNumCols() const { return mNumCols; }

// const operator(): only allow to reand
double Matrix::operator()(int i, int j) const {
    if (i < 1 || i > mNumRows || j < 1 || j > mNumCols) {
        throw std::invalid_argument("Index is out of range");
    }
    return mData[i - 1][j - 1];
}

// non-const operator(): can modify and assign to a matrix
double& Matrix::operator()(int i, int j) {
    if (i < 1 || i > mNumRows || j < 1 || j > mNumCols) {
        throw std::invalid_argument("Index is out of range");
    }
    return mData[i - 1][j - 1];
}

// Assignment operator
// DOES change original matrix
Matrix& Matrix::operator=(const Matrix& other) {
    // check for self-assignment
    if (this == &other) {
        return *this;
    }

    for (int i = 0; i < this->mNumRows; i++) delete[] mData[i];
    this->allocateMemory(other.getNumRows(), other.getNumCols());

    // copy data over
    this->mNumRows = other.getNumRows();
    this->mNumCols = other.getNumCols();
    for (int i = 0; i < this->mNumRows; i++) {
        for (int j = 0; j < this->mNumCols; j++) {
            this->mData[i][j] = other.mData[i][j];
        }
    }

    return *this;
}

// Unary Operator
// DOES NOT change original vector
Matrix Matrix::operator-() const {
    Matrix result(mNumRows, mNumCols);  // Create a copy of matrix

    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            result.mData[i][j] = -mData[i][j];
        }
    }
    return result;
}

// DOES change original vector
Matrix& Matrix::operator++() {
    for (int i = 0; i < this->mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            this->mData[i][j]++;
        }
    }

    return *this;
}

// DOES change original vector, but return old copy
Matrix Matrix::operator++(int) {
    Matrix old = *this;  // Copy current state

    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            mData[i][j] += 1;
        }
    }
    return old;
}

// DOES change original vector
Matrix& Matrix::operator--() {
    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            mData[i][j] -= 1;
        }
    }
    return *this;
}

// DOES change original vector, but return old copy
Matrix Matrix::operator--(int) {
    Matrix old = *this;
    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            mData[i][j] -= 1;
        }
    }
    return old;
}

// Binary Operator
Matrix Matrix::operator+(const Matrix& other) const {
    Matrix result;
    result.allocateMemory(other.mNumRows, other.mNumCols);
    for (int i = 0; i < other.mNumRows; i++) {
        for (int j = 0; j < other.mNumCols; j++) {
            result.mData[i][j] = this->mData[i][j] + other.mData[i][j];
        }
    }
    return result;
}

// DOES NOT change original matrix
Matrix Matrix::operator-(const Matrix& other) const {
    Matrix result;
    // Check if dimensions match
    if (mNumRows != other.mNumRows || mNumCols != other.mNumCols) {
        throw std::invalid_argument(
            "Matrix dimensions must match for subtraction.");
    }
    result.allocateMemory(other.mNumRows, other.mNumCols);
    for (int i = 0; i < other.mNumRows; i++) {
        for (int j = 0; j < other.mNumCols; j++) {
            result.mData[i][j] = this->mData[i][j] - other.mData[i][j];
        }
    }
    return result;
}

Matrix Matrix::convertToTriangleMatrix() const { assert(mNumRows == mNumCols); }

double Matrix::determinant() const {
    assert(mNumRows == mNumCols);
    if (mNumRows == 1) {
        return mData[0][0];
    }
    if (mNumRows == 2) {
        return mData[0][0] * mData[1][1] - mData[0][1] * mData[1][0];
    }
    double det = 0;
    convertToTriangleMatrix();
}