#ifndef LINEAR_SYSTEM_HEADER
#define LINEAR_SYSTEM_HEADER

#include "Matrix.h"
#include "Vector.h"

class LinearSystem {
   protected:
    int mSize;
    Matrix* mpA;
    Vector* mpb;

   public:
    // Do not allow mSize. Assert size and then
    // auto assign mSize
    LinearSystem(Matrix* _mpA, Vector* _mpb);

    // Copy Constructor
    LinearSystem(const LinearSystem& ls);

    // Solve using Gauss Elimination with pivoting
    Vector Solve();
};

#endif