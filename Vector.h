#ifndef VECTOR_HEADER
#define VECTOR_HEADER

#include <string>
#include <sstream>

class Vector {
   private:
    int mSize;
    double* mData;

   public:
    // Constructor
    Vector(int size); // default
		Vector(double array[], int size); // array input
    Vector(const Vector& other); // Vector input

    // Destructor
    ~Vector();

    // Assignment Operator
    Vector& operator=(const Vector& other); // DOES change original vector

    // Unary Operator
    Vector operator-() const; // DOES NOT change original vector

    // Binary Operator
    // Vector ... const -> return new object
    // Vector& ...      -> assign back to current object
    Vector operator+(const Vector& other) const; // DOES NOT change original vector
    Vector& operator+=(const Vector& other); //	 DOES change original vector

    Vector operator-(const Vector& other) const; // DOES NOT change original vector
    Vector& operator-=(const Vector& other); // DOES change original vector

    Vector operator*(double scalar) const; // DOES NOT change original vector
    Vector& operator*=(double scalar); // DOES change original vector

    // Dot Product (maybe?)
    double operator*(const Vector& other) const; // DOES NOT change original vector

    // [] ()
    double& operator[](int index);
    double& operator()(int index_1);

    // If vector is const -> use this
    const double& operator[](int index) const;
    const double& operator()(int index_1) const;

		// toString
		std::string toString();
};
    
#endif