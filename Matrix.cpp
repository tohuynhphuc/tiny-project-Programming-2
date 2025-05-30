#include "Matrix.h"

#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

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
//! Size Constructor
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

//! Array Constructor
Matrix::Matrix(double **data, int rows, int cols) {
    //? Matrix dimensions must be positive
    assert(rows > 0 && cols > 0);

    mNumRows = rows;
    mNumCols = cols;
    allocateMemory(mNumRows, mNumCols);

    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            mData[i][j] = data[i][j];
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

    for (int i = 0; i < mNumRows; i++) {
        delete[] mData[i];
    }
    delete[] mData;

    allocateMemory(other.getNumRows(), other.getNumCols());

    // copy data over
    mNumRows = other.getNumRows();
    mNumCols = other.getNumCols();

    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            mData[i][j] = other.mData[i][j];
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

    //? Check if the matrix is invertible
    double det = determinant();
    assert(det != 0);

    int n = mNumRows;
    Matrix augmented(n, 2 * n);

    //& Create an augmented matrix [A|I]
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            augmented(i, j) = (*this)(i, j);
            augmented(i, j + n) = (i == j) ? 1 : 0;
        }
    }

    //& Gauss-Jordan elimination
    for (int i = 1; i <= n; i++) {
        // Find pivot
        double pivot = augmented(i, i);
        if (pivot == 0.0) {
            bool found = false;
            for (int j = i + 1; j <= n; j++) {
                if (augmented(j, i) != 0.0) {
                    // Swap rows i and j
                    for (int k = 1; k <= 2 * n; k++) {
                        swap(augmented(i, k), augmented(j, k));
                    }

                    pivot = augmented(i, i);
                    found = true;
                    break;
                }
            }
            if (!found) {
                throw runtime_error(
                    "Matrix is singular and cannot be inverted!");
            }
        }

        // Normalize pivot row
        for (int k = 1; k <= 2 * n; k++) {
            augmented(i, k) /= pivot;
        }

        // Eliminate other rows
        for (int j = 1; j <= n; j++) {
            if (j != i) {
                double factor = augmented(j, i);
                for (int k = 1; k <= 2 * n; k++) {
                    augmented(j, k) -= factor * augmented(i, k);
                }
            }
        }
    }

    // Extract the right half of the augmented to get the inverse
    Matrix inverse(n, n);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            inverse(i, j) = augmented(i, j + n);
        }
    }

    return inverse;
}

//* Pseudo Inverse in a non-square matrix
Matrix Matrix::pseudoInverse() const {
    if (mNumRows == mNumCols) {
        return inverse();
    }

    // check if rank is full
    int rank = min(mNumRows, mNumCols);
    bool found_rank = false;

    for (int start_r = 0; start_r <= mNumRows - rank && !found_rank;
         start_r++) {
        for (int start_c = 0; start_c <= mNumCols - rank && !found_rank;
             start_c++) {
            Matrix submatrix = Matrix(rank, rank);
            // copy data to submatrix
            for (int i = start_r; i < start_r + rank; i++) {
                for (int j = start_c; j < start_c + rank; j++) {
                    submatrix.mData[i - start_r][j - start_c] = mData[i][j];
                }
            }
            if (submatrix.determinant() != 0) {
                found_rank = true;
                continue;
            }
        }
    }

    //? Matrix has neither full row rank nor full column rank, cannot find
    //? pseudo-inverse
    assert(found_rank);

    Matrix result;
    Matrix transpose = this->transpose();
    if (rank == mNumRows) {
        //& full row rank, use right inverse
        result = transpose * ((*this) * transpose).inverse();
    } else {
        //& full column rank, use left inverse
        result = (transpose * (*this)).inverse() * transpose;
    }

    return result;
}

//* Transpose
Matrix Matrix::transpose() const {
    Matrix result(mNumCols, mNumRows);

    for (int i = 0; i < mNumRows; i++) {
        for (int j = 0; j < mNumCols; j++) {
            result.mData[j][i] = mData[i][j];
        }
    }

    return result;
}

string Matrix::toString() {
    ostringstream oss;
    oss << "[";

    for (int i = 0; i < mNumRows; ++i) {
        oss << "[";
        for (int j = 0; j < mNumCols; ++j) {
            double val = mData[i][j];
            if (fabs(val - round(val)) < 1e-9) {
                oss << static_cast<int>(round(val));  // Print as int
            } else {
                oss << fixed << setprecision(2)
                    << val;  // Print as double with 2 decimal places
            }
            if (j < mNumCols - 1) {
                oss << ", ";
            }
        }
        oss << "]";
        if (i < mNumRows - 1) {
            oss << ",\n ";
        }
    }

    oss << "]";
    return oss.str();
}