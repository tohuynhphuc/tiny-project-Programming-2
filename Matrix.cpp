#include "Matrix.h"

#include <cassert>
#include <iostream>
#include <stdexcept>

using namespace std;

// Allocate memory before copying the entries
// of the original matrix into the new matrix
void Matrix::allocateMemory(int rows, int cols) {
    mData = new double *[rows];

    for (int i = 0; i < rows; i++) {
        mData[i] = new double[cols];
    }
}

//* ----------Constructors----------
//! Default Constructor
Matrix::Matrix(int rows, int cols) {
    //? Matrix dimensions must be positive
    assert(rows > 0 && cols > 0);

    mNumRows = rows;
    mNumCols = cols;
    allocateMemory(mNumRows, mNumCols);

    // Initialize the matrix with 0s
    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            mData[i][j] = 0.0;
        }
    }
}

//! Copy constructor
Matrix::Matrix(const Matrix &other) {
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

//* ----------Destructor----------
Matrix::~Matrix() {
    for (int i = 0; i < mNumRows; i++) {
        delete[] mData[i];
    }
    delete[] mData;
}

//* ----------Getters----------
int Matrix::getNumRows() const { return mNumRows; }
int Matrix::getNumCols() const { return mNumCols; }
double **Matrix::getData() const { return mData; }

//* ----------Brackets ()----------
const double &Matrix::operator()(int i, int j) const {
    //? Index must be in range
    assert(i >= 1 && i <= mNumRows && j >= 1 && j <= mNumCols);

    return mData[i - 1][j - 1];
}

double &Matrix::operator()(int i, int j) {
    //? Index must be in range
    assert(i >= 1 && i <= mNumRows && j >= 1 && j <= mNumCols);

    return mData[i - 1][j - 1];
}

//* ----------Assignment operator----------
// DOES change original matrix
Matrix &Matrix::operator=(const Matrix &other) {
    // check for self-assignment
    if (this == &other) {
        return *this;
    }

    for (int i = 0; i < this->mNumRows; i++) {
        delete[] mData[i];
    }
    delete[] mData;

    allocateMemory(other.getNumRows(), other.getNumCols());

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

//* ----------Unary Operators----------
//! Negative, DOES NOT change original matrix
Matrix Matrix::operator-() const {
    Matrix result(mNumRows, mNumCols);

    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            result.mData[i][j] = -mData[i][j];
        }
    }
    return result;
}

//! Prefix ++, DOES change original matrix
Matrix &Matrix::operator++() {
    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            mData[i][j]++;
        }
    }

    return *this;
}

//! Postfix ++, DOES change original matrix, but return old copy
Matrix Matrix::operator++(int) {
    Matrix old = *this;  // Copy current state

    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            mData[i][j]++;
        }
    }

    return old;
}

//! Prefix --, DOES change original matrix
Matrix &Matrix::operator--() {
    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            mData[i][j]--;
        }
    }

    return *this;
}

//! Postfix --, DOES change original matrix, but return old copy
Matrix Matrix::operator--(int) {
    Matrix old = *this;

    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            mData[i][j]--;
        }
    }

    return old;
}

//* ----------Binary Operators----------
//! Addition, DOES NOT change original matrix
Matrix Matrix::operator+(const Matrix &other) const {
    //? Dimensions must match for addition
    assert(mNumRows == other.mNumRows && mNumCols == other.mNumCols);

    Matrix result(mNumRows, mNumCols);

    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            result.mData[i][j] = mData[i][j] + other.mData[i][j];
        }
    }

    return result;
}

//! Addition, DOES change original matrix
Matrix &Matrix::operator+=(const Matrix &other) {
    //? Dimensions must match for addition
    assert(mNumRows == other.mNumRows && mNumCols == other.mNumCols);

    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            mData[i][j] += other.mData[i][j];
        }
    }
    return *this;
}

//! Subtraction, DOES NOT change original matrix
Matrix Matrix::operator-(const Matrix &other) const {
    //? Dimensions must match for subtraction
    assert(mNumRows == other.mNumRows && mNumCols == other.mNumCols);

    Matrix result(mNumRows, mNumCols);

    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            result.mData[i][j] = mData[i][j] - other.mData[i][j];
        }
    }

    return result;
}

//! Subtraction, DOES change original matrix
Matrix &Matrix::operator-=(const Matrix &other) {
    //? Dimensions must match for subtraction
    assert(mNumRows == other.mNumRows && mNumCols == other.mNumCols);

    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            mData[i][j] -= other.mData[i][j];
        }
    }

    return *this;
}

//! ----------MATRIX MULTIPLICATION----------
Matrix Matrix::operator*(const Matrix &matrix) const {
    //? Dimensions must match for multiplication
    assert(mNumCols == matrix.mNumRows);

    Matrix result(mNumRows, matrix.mNumCols);

    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < matrix.mNumCols; j++) {
            double sum = 0;

            for (int k = 0; k < mNumCols; k++) {
                sum += (*this)(i + 1, k + 1) * matrix(k + 1, j + 1);
            }

            result(i + 1, j + 1) = sum;
        }
    }

    return result;
}

Matrix &Matrix::operator*=(const Matrix &matrix) {
    *this = (*this) * matrix;
    return *this;
}

//! ----------VECTOR MULTIPLICATION----------
Vector Matrix::operator*(const Vector &vector) const {
    //& [m x n] x [n x 1] = [m x 1]
    //? Dimensions must match for multiplication
    assert(mNumCols == vector.getSize());

    Vector result(mNumRows);
    for (int m = 0; m < mNumRows; m++) {
        double sum = 0;

        for (int n = 0; n < mNumCols; n++) {
            sum += mData[m][n] * vector[n];
        }

        result[m] = sum;
    }

    return result;
}

Matrix &Matrix::operator*=(const Vector &vector) {
    //& [m x n] x [n x 1] = [m x 1]
    //? Dimensions must match for multiplication
    assert(mNumCols == vector.getSize());

    Matrix result(mNumRows, 1);

    for (int m = 0; m < mNumRows; m++) {
        double sum = 0.0;
        for (int n = 0; n < mNumCols; n++) {
            sum += mData[m][n] * vector[n];
        }
        result.mData[m][0] = sum;
    }

    *this = result;
    return *this;
}

//! ----------SCALAR MULTIPLICATION----------
Matrix Matrix::operator*(double scalar) const {
    Matrix result(mNumRows, mNumCols);

    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            result.mData[i][j] = mData[i][j] * scalar;
        }
    }

    return result;
}

Matrix &Matrix::operator*=(double scalar) {
    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            mData[i][j] = mData[i][j] * scalar;
        }
    }
    return *this;
}

//* ----------Determinant in square mtrx----------
double Matrix::determinant() const {
    //? It MUST be a square matrix
    assert(mNumRows == mNumCols);

    if (mNumRows == 1) {
        return mData[0][0];
    } else if (mNumRows == 2) {
        return mData[0][0] * mData[1][1] - mData[0][1] * mData[1][0];
    }

    Matrix result(*this);  // Make a copy
    bool isPositive = true;

    for (int i = 0; i < mNumRows; i++) {
        //& Find the pivot
        double pivot = result.mData[i][i];
        int swapRow = i;

        if (pivot == 0) {
            // Find a non-zero pivot
            for (int j = i + 1; j < mNumRows; j++) {
                if (result.mData[j][i] == 0) continue;
                swapRow = j;
                break;
            }

            if (swapRow == i) return 0;  // Singular matrix

            // Swap rows
            for (int k = 0; k < mNumCols; k++) {
                swap(result.mData[i][k], result.mData[swapRow][k]);
            }

            isPositive = !isPositive;  // Change sign of determinant
            pivot = result.mData[i][i];
        }

        //& Eliminate below
        for (int j = i + 1; j < mNumRows; j++) {
            double factor = result.mData[j][i] / pivot;

            for (int k = i; k < mNumCols; k++) {
                result.mData[j][k] -= factor * result.mData[i][k];
            }
        }
    }

    double det = 1;
    for (int i = 0; i < mNumRows; i++) {
        det *= result.mData[i][i];
    }

    return isPositive ? det : -det;
}

//* ----------Inverse Square Matrix----------
Matrix Matrix::inverse() const {
    //? It MUST be a square matrix
    assert(mNumRows == mNumCols);

    // Check if the matrix is invertible
    double det = this->determinant();
    if (det == 0.0) {
        throw std::runtime_error("Matrix is singular and cannot be inverted.");
    }
    int n = mNumRows;
    Matrix augmented(n, 2 * n);

    // Create an augmented matrix [A|I]
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            augmented(i + 1, j + 1) = (*this)(i + 1, j + 1);
        }
        for (int j = 0; j < n; j++) {
            augmented(i + 1, j + 1 + n) = (i == j) ? 1.0 : 0.0;
        }
    }

    // Gauss-Jordan elimination
    for (int i = 0; i < n; i++) {
        // Find pivot
        double pivot = augmented(i + 1, i + 1);
        if (pivot == 0.0) {
            bool found = false;
            for (int j = i + 1; j < n; j++) {
                if (augmented(j + 1, i + 1) != 0.0) {
                    // Swap rows i and j
                    for (int k = 0; k < 2 * n; k++) {
                        std::swap(augmented(i + 1, k + 1),
                                  augmented(j + 1, k + 1));
                    }

                    pivot = augmented(i + 1, i + 1);
                    found = true;
                    break;
                }
            }
            if (!found) {
                throw std::runtime_error(
                    "Matrix is singular and cannot be inverted!");
            }
        }

        // Normalize pivot row
        for (int k = 0; k < 2 * n; k++) {
            augmented(i + 1, k + 1) /= pivot;
        }

        // Eliminate other rows
        for (int j = 0; j < n; j++) {
            if (j != i) {
                double factor = augmented(j + 1, i + 1);
                for (int k = 0; k < 2 * n; k++) {
                    augmented(j + 1, k + 1) -= factor * augmented(i + 1, k + 1);
                }
            }
        }
    }

    // Extract the right half of the augmented to get the inverse
    Matrix inverse(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inverse(i + 1, j + 1) = augmented(i + 1, j + 1 + n);
        }
    }

    return inverse;
}

//* Transpose
Matrix Matrix::transposed_matrix() const {
    Matrix result(mNumCols, mNumRows);
    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            result.mData[j][i] = mData[i][j];
        }
    }
    return result;
}