#ifndef MATRIX_HEADER
#define MATRIX_HEADER
#include "Vector.h"
class Matrix{
    private:
    int mNumRows;
    int mNumCols;
    double** mData;
    void allocateMemory(int rows, int cols);   // To allocate 2D array

    public:
    // Constructor
    Matrix(int rows, int cols);  // Zero initial matrix
    Matrix(const Matrix& other);  // Copy constructor
    // Destructor
    ~Matrix();

    // public methods for accessing the number of rows and columns
    int getNumRows() const;
    int getNumCols() const;
};

#endif