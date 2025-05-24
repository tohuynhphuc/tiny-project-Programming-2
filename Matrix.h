#ifndef MATRIX_HEADER
#define MATRIX_HEADER

#include "Vector.h"

class Matrix
{
private:
    int mNumRows;
    int mNumCols;
    double **mData;
    void allocateMemory(int rows, int cols); // To allocate 2D array

public:
    // Constructor
    Matrix(int rows = 1, int cols = 1); // Zero initial matrix
    Matrix(const Matrix &other);        // Copy constructor

    // Destructor
    ~Matrix();

    // public methods for accessing the number of rows and columns
    int getNumRows() const;
    int getNumCols() const;

    // const operator()
    double operator()(int i, int j) const;
    // non-const operator()
    double &operator()(int i, int j);

    // Assignment operator
    Matrix &operator=(const Matrix &other); // DOES change original matrix

    // Unary Operator
    Matrix operator-() const; // DOES NOT change original matrix
    Matrix &operator++();     // DOES change original vector
    Matrix operator++(int);   // DOES change original vector, but return old copy
    Matrix &operator--();     // DOES change original vector
    Matrix operator--(int);   // DOES change original vector, but return old copy

    // Binary Operator
    // Vector ... const -> return new object
    // Vector& ...      -> assign back to current object
    Matrix operator+(const Matrix &other) const;
    Matrix &operator+=(const Matrix &other);

    Matrix operator-(const Matrix &other) const;
    Matrix &operator-=(const Matrix &other);

    Matrix operator*(const Matrix &matrix) const;
    Matrix &operator*=(const Matrix &matrix);

    Vector operator*(const Vector &vector) const;
    Matrix &operator*=(const Vector &vector);

    Matrix operator*(double scalar) const;
    Matrix &operator*=(double scalar);

    // Helper function: Convert a square matrix
    // to an UPPER TRIANGLE matrix
    Matrix convertToTriangleMatrix() const;

    // Determinant in a square matrix
    double determinant() const;
    // Inverse in a square matrix
    Matrix inverse() const;
};

#endif