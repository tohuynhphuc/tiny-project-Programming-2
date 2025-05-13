#ifndef VECTOR_HEADER
#define VECTOR_HEADER

class Vector {
   private:
    int mSize;
    double* mData;

   public:
    // Constructor
    Vector(int size = 0);
    Vector(const Vector& other);

    // Destructor
    ~Vector();

    // Assignment Operator
    Vector& operator=(const Vector& other);

    // Unary Operator
    Vector operator-() const;

    // Binary Operator
    // Vector ... const -> return new object
    // Vector& ...      -> assign back to current object
    Vector operator+(const Vector& other) const;
    Vector& operator+=(const Vector& other);

    Vector operator-(const Vector& other) const;
    Vector& operator-=(const Vector& other);

    Vector operator*(double scalar) const;
    Vector& operator*=(double scalar);

    // Dot Product (maybe?)
    double operator*(const Vector& other) const;

    // [] ()
    double& operator[](int index);
    double& operator()(int index_1);

    // If vector is const -> use this
    const double& operator[](int index) const;
    const double& operator()(int index_1) const;
};

#endif