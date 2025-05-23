#include "Matrix.h"

#include <iostream>
#include <stdexcept>

using namespace std;

// Allocate memory before copying the entries of the original matrix into the new matrix
void Matrix::allocateMemory(int rows, int cols){
    mData = new double*[rows];
    for (int i = 0; i < rows; i++){
        mData[i] = new double[cols];
    }
}

Matrix:: Matrix(const Matrix& other){
    mNumRows = other.mNumRows;
    mNumCols = other.mNumCols;
    allocateMemory(mNumRows, mNumCols);

    // Copy to new matrix
    for (int i = 0; i < mNumRows; i++){
        for (int j = 0; j < mNumCols; j++){
            mData[i][j] = other.mData[i][j];
        }
    }
}

Matrix::Matrix(int rows, int cols){
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Matrix dimensions must be positive integers.");
    }
    mNumRows = rows;
    mNumCols = cols;

    allocateMemory(mNumRows, mNumCols);

    // Initialize the matrix with 0
    for (int i = 0; i < mNumRows; i++){
        for (int j = 0; j < mNumCols; j++){
            mData[i][j] = 0.0;
        }
    }

}

// Destructor to free the allocated memory
Matrix::~Matrix(){
    for (int i = 0; i < mNumRows; i++){
        delete[] mData[i];
    }
    delete[] mData;
}

// Access to the number of rows and columns
int Matrix::getNumRows() const{
    return mNumRows;
}

int Matrix::getNumCols() const{
    return mNumCols;
}

// const operator(): only allow to reand 
double Matrix::operator()(int i, int j){
    if (i < 1 || i > rows || j < 1 || j > cols){
        throw std::invalid_argument("Index is out of range");
    }
    return mData[i-1][j-1];
}

// non-const operator(): can modify and assign to a matrix
double& Matrix::operator()(int i, int j){
    if (i < 1 || i > rows || j < 1 || j > cols){
        throw std::invalid_argument("Index is out of range");
    }
    return mData[i-1][j-1];
}
