#include "Matrix.h"

#include <cassert>
#include <iostream>
#include <stdexcept>

using namespace std;

// Allocate memory before copying the entries
// of the original matrix into the new matrix
void Matrix::allocateMemory(int rows, int cols)
{
    mData = new double *[rows];
    for (int i = 0; i < rows; i++)
    {
        mData[i] = new double[cols];
    }
}

// Default: rows = 1, cols = 1
Matrix::Matrix(int rows, int cols)
{
    if (rows <= 0 || cols <= 0)
    {
        throw std::invalid_argument(
            "Matrix dimensions must be positive integers.");
    }
    mNumRows = rows;
    mNumCols = cols;

    allocateMemory(mNumRows, mNumCols);

    // Initialize the matrix with 0
    for (int i = 0; i < mNumRows; i++)
    {
        for (int j = 0; j < mNumCols; j++)
        {
            mData[i][j] = 0.0;
        }
    }
}

Matrix::Matrix(const Matrix &other)
{
    mNumRows = other.mNumRows;
    mNumCols = other.mNumCols;
    allocateMemory(mNumRows, mNumCols);

    // Copy to new matrix
    for (int i = 0; i < mNumRows; i++)
    {
        for (int j = 0; j < mNumCols; j++)
        {
            mData[i][j] = other.mData[i][j];
        }
    }
}

// Destructor to free the allocated memory
Matrix::~Matrix()
{
    for (int i = 0; i < mNumRows; i++)
    {
        delete[] mData[i];
    }
    delete[] mData;
}

// Access to the number of rows and columns
int Matrix::getNumRows() const { return mNumRows; }

int Matrix::getNumCols() const { return mNumCols; }

// const operator(): only allow to reand
double Matrix::operator()(int i, int j) const
{
    if (i < 1 || i > mNumRows || j < 1 || j > mNumCols)
    {
        throw std::invalid_argument("Index is out of range");
    }
    return mData[i - 1][j - 1];
}

// non-const operator(): can modify and assign to a matrix
double &Matrix::operator()(int i, int j)
{
    if (i < 1 || i > mNumRows || j < 1 || j > mNumCols)
    {
        throw std::invalid_argument("Index is out of range");
    }
    return mData[i - 1][j - 1];
}

// Assignment operator
// DOES change original matrix
Matrix &Matrix::operator=(const Matrix &other)
{
    // check for self-assignment
    if (this == &other)
    {
        return *this;
    }

    for (int i = 0; i < this->mNumRows; i++)
        delete[] mData[i];
    this->allocateMemory(other.getNumRows(), other.getNumCols());

    // copy data over
    this->mNumRows = other.getNumRows();
    this->mNumCols = other.getNumCols();
    for (int i = 0; i < this->mNumRows; i++)
    {
        for (int j = 0; j < this->mNumCols; j++)
        {
            this->mData[i][j] = other.mData[i][j];
        }
    }

    return *this;
}

// Unary Operator
// DOES NOT change original vector
Matrix Matrix::operator-() const
{
    Matrix result(mNumRows, mNumCols);

    for (int i = 0; i < mNumRows; i++)
    {
        for (int j = 0; j < mNumCols; j++)
        {
            result.mData[i][j] = -mData[i][j];
        }
    }
    return result;
}

// DOES change original vector
Matrix &Matrix::operator++()
{
    for (int i = 0; i < this->mNumRows; i++)
    {
        for (int j = 0; j < mNumCols; j++)
        {
            this->mData[i][j]++;
        }
    }

    return *this;
}

// DOES change original vector, but return old copy
Matrix Matrix::operator++(int)
{
    Matrix old = *this; // Copy current state

    for (int i = 0; i < mNumRows; i++)
    {
        for (int j = 0; j < mNumCols; j++)
        {
            mData[i][j] += 1;
        }
    }
    return old;
}

// DOES change original vector
Matrix &Matrix::operator--()
{
    for (int i = 0; i < mNumRows; i++)
    {
        for (int j = 0; j < mNumCols; j++)
        {
            mData[i][j] -= 1;
        }
    }
    return *this;
}

// DOES change original vector, but return old copy
Matrix Matrix::operator--(int)
{
    Matrix old = *this;
    for (int i = 0; i < mNumRows; i++)
    {
        for (int j = 0; j < mNumCols; j++)
        {
            mData[i][j] -= 1;
        }
    }
    return old;
}

// Binary Operator
Matrix Matrix::operator+(const Matrix &other) const
{
    assert(mNumRows == other.mNumRows && mNumCols == other.mNumCols);
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; i++)
    {
        for (int j = 0; j < mNumCols; j++)
        {
            result.mData[i][j] = this->mData[i][j] + other.mData[i][j];
        }
    }
    return result;
}

Matrix &Matrix::operator+=(const Matrix &other)
{
    assert(mNumRows == other.mNumRows && mNumCols == other.mNumCols);
    for (int i = 0; i < mNumRows; i++)
    {
        for (int j = 0; j < mNumCols; j++)
        {
            this->mData[i][j] += other.mData[i][j];
        }
    }
    return *this;
}

// DOES NOT change original matrix
Matrix Matrix::operator-(const Matrix &other) const
{
    // Check if dimensions match
    if (mNumRows != other.mNumRows || mNumCols != other.mNumCols)
    {
        throw std::invalid_argument(
            "Matrix dimensions must match for subtraction.");
    }
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; i++)
    {
        for (int j = 0; j < mNumCols; j++)
        {
            result.mData[i][j] = this->mData[i][j] - other.mData[i][j];
        }
    }
    return result;
}

Matrix &Matrix::operator-=(const Matrix &other)
{
    assert(mNumRows == other.mNumRows && mNumCols == other.mNumCols);
    for (int i = 0; i < mNumRows; i++)
    {
        for (int j = 0; j < mNumCols; j++)
        {
            this->mData[i][j] -= other.mData[i][j];
        }
    }
    return *this;
}

// MATRIX MULTIPLICATION
Matrix Matrix::operator*(const Matrix &matrix) const
{
    // CODE HERE
    if (mNumCols != matrix.mNumRows)
    {
        throw std::invalid_argument(
            "Matrix dimensions do not match for multiplication.");
    }

    Matrix result(mNumRows, matrix.mNumCols);

    for (int i = 0; i < mNumRows; i++)
    {
        for (int j = 0; j < matrix.mNumCols; j++)
        {
            result(i + 1, j + 1) = 0;

            for (int k = 0; k < mNumCols; k++)
            {
                result(i + 1, j + 1) +=
                    (*this)(i + 1, k + 1) * matrix(k + 1, j + 1);
            }
        }
    }
    return result;
    // CODE END HERE
}

Matrix &Matrix::operator*=(const Matrix &matrix)
{
    // CODE HERE
    if (mNumCols != matrix.mNumRows)
    {
        throw std::invalid_argument(
            "Matrix dimensions do not match for multiplication.");
    }

    // Create a temp matrix to hold the result
    Matrix result(mNumRows, matrix.mNumCols);

    for (int i = 0; i < mNumRows; i++)
    {
        for (int j = 0; j < matrix.mNumCols; j++)
        {
            result(i + 1, j + 1) = 0;
            for (int k = 0; k < mNumCols; k++)
            {
                result(i + 1, j + 1) +=
                    (*this)(i + 1, k + 1) * matrix(k + 1, j + 1);
            }
        }
    }

    // Assign the result back to this
    *this = result;
    return *this;
    // CODE END HERE
}

// VECTOR MULTIPLICATION
Vector Matrix::operator*(const Vector &vector) const
{
    // CODE HERE mxn x nX1 = mX1
    assert(mNumCols == vector.getSize());
    Vector result(mNumRows);
    for (int m = 0; m < mNumRows; m++)
    {
        double sum = 0.0;
        for (int n = 0; n < mNumCols; n++)
        {
            sum += mData[m][n] * vector[n];
        }
        result[m] = sum;
    }
    return result;
    // CODE END HERE
}

Matrix &Matrix::operator*=(const Vector &vector)
{
    // CODE HERE
    assert(mNumCols == vector.getSize());
    Matrix result(mNumRows, 1);
    for (int m = 0; m < mNumRows; m++)
    {
        double sum = 0.0;
        for (int n = 0; n < mNumCols; n++)
        {
            sum += mData[m][n] * vector[n];
        }
        result.mData[m][0] = sum;
    }
    // modify this matrix
    *this = result;
    return *this;
    // CODE END HERE
}

// SCALAR MULTIPLICATION
Matrix Matrix::operator*(double scalar) const
{
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; i++)
    {
        for (int j = 0; j < mNumCols; j++)
        {
            result.mData[i][j] = this->mData[i][j] * scalar;
        }
    }
    return result;
}

Matrix &Matrix::operator*=(double scalar)
{
    for (int i = 0; i < mNumRows; i++)
    {
        for (int j = 0; j < mNumCols; j++)
        {
            this->mData[i][j] = this->mData[i][j] * scalar;
        }
    }
    return *this;
}

double Matrix::determinant() const
{
    assert(mNumRows == mNumCols); // Ensure it's a square matrix
    if (mNumRows == 1)
    {
        return mData[0][0];
    }
    else if (mNumRows == 2)
    {
        return mData[0][0] * mData[1][1] - mData[0][1] * mData[1][0];
    }
    double det = 1.0;
    Matrix result(*this); // Make a copy
    int swap_sign = 1;

    for (int i = 0; i < mNumRows; i++)
    {
        // Find the pivot
        double pivot = result.mData[i][i];
        int swap_row = i;
        if (pivot == 0)
        {
            // Find a non-zero pivot
            for (int j = i + 1; j < mNumRows; j++)
            {
                if (result.mData[j][i] != 0)
                {
                    swap_row = j;
                    break;
                }
            }
            if (swap_row != i)
            {
                // Swap rows
                for (int k = 0; k < mNumCols; k++)
                {
                    std::swap(result.mData[i][k], result.mData[swap_row][k]);
                }
                swap_sign *= -1; // Change sign of determinant
                pivot = result.mData[i][i];
            }
        }

        if (pivot == 0)
        {
            return 0.0; // Singular matrix
        }

        // Eliminate below
        for (int j = i + 1; j < mNumRows; j++)
        {
            double factor = result.mData[j][i] / pivot;
            for (int k = i; k < mNumCols; k++)
            {
                result.mData[j][k] -= factor * result.mData[i][k];
            }
        }
    }
    for (int i = 0; i < mNumRows; i++)
    {
        det *= result.mData[i][i];
    }
    det *= swap_sign; // Adjust sign
    return det;
}