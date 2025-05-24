#ifndef MATRIX_HEADER
#define MATRIX_HEADER

#include "Vector.h"

class Matrix {
   private:
    int mNumRows;
    int mNumCols;
    double **mData;

    void allocateMemory(int rows, int cols);  // To allocate 2D array

   public:
    //* Constructors
    Matrix(int rows = 1, int cols = 1);  // Size constructor
    //! NOT IMPLEMENTED
    Matrix(double **data, int rows, int cols);  // Array constructor
    Matrix(const Matrix &other);                // Copy constructor

    //* Destructor
    ~Matrix();

    //* Getters
    int getNumRows() const;
    int getNumCols() const;
    double **getData() const;

    //* Brackets ()
    const double &operator()(int i, int j) const;
    double &operator()(int i, int j);

    //* Assignment operator
    Matrix &operator=(const Matrix &other);  // DOES change original matrix

    //* Unary Operators
    Matrix operator-() const;  // DOES NOT change original matrix
    Matrix &operator++();      // DOES change original matrix
    Matrix operator++(int);  // DOES change original matrix, but return old copy
    Matrix &operator--();    // DOES change original matrix
    Matrix operator--(int);  // DOES change original matrix, but return old copy

    //* Binary Operators
    // Matrix ... const -> return new object
    // Matrix& ...      -> assign back to current object
    Matrix operator+(const Matrix &other) const;
    Matrix &operator+=(const Matrix &other);

    Matrix operator-(const Matrix &other) const;
    Matrix &operator-=(const Matrix &other);

    //! MATRIX MULTIPLICATION
    Matrix operator*(const Matrix &matrix) const;
    Matrix &operator*=(const Matrix &matrix);

    //! VECTOR MULTIPLICATION
    Vector operator*(const Vector &vector) const;
    Matrix &operator*=(const Vector &vector);

    //! SCALAR MULTIPLICATION
    Matrix operator*(double scalar) const;
    Matrix &operator*=(double scalar);

    //* Determinant in a square matrix
    double determinant() const;

    //* Inverse in a square matrix
    Matrix inverse() const;

	//* Pseudo Inverse in a non-square matrix
	Matrix pseudoInverse() const;

    //* Transpose
    Matrix transpose() const;

    //* To String
    std::string toString();
};

#endif