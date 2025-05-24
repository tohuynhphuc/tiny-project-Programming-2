#ifndef VECTOR_HEADER
#define VECTOR_HEADER

#include <sstream>
#include <string>

class Vector {
   private:
    int mSize;
    double* mData;

   public:
    //* Constructors
    Vector(int size);                  // Size input
    Vector(double array[], int size);  // Array input
    Vector(const Vector& other);       // Vector input

    //* Destructor
    ~Vector();

    int getSize() const;
    double* getData() const;

    //* Assignment Operator
    Vector& operator=(const Vector& other);  // DOES change original vector

    //* Unary Operators
    Vector operator-() const;  // DOES NOT change original vector
    Vector& operator++();      // DOES change original vector
    Vector operator++(int);  // DOES change original vector, but return old copy
    Vector& operator--();    // DOES change original vector
    Vector operator--(int);  // DOES change original vector, but return old copy

    //* Binary Operators
    // Vector ... const -> return new object
    // Vector& ...      -> assign back to current object
    Vector operator+(const Vector& other) const;
    Vector& operator+=(const Vector& other);

    Vector operator-(const Vector& other) const;
    Vector& operator-=(const Vector& other);

    Vector operator*(double scalar) const;
    Vector& operator*=(double scalar);

    //* Dot Product
    double operator*(const Vector& other) const;

    //* Brackets [] ()
    double& operator[](int index);
    double& operator()(int index_1);

    // If vector is const -> use this
    const double& operator[](int index) const;
    const double& operator()(int index_1) const;

    //* To String
    std::string toString();
};

#endif