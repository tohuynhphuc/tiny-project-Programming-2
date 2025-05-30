#ifndef LINEAR_SYSTEM_HEADER
#define LINEAR_SYSTEM_HEADER

#include "Matrix.h"
#include "Vector.h"

class LinearSystem {
   protected:
    int mSize;
    Matrix *mpA;
    Vector *mpb;

   public:
    //* Constructors
    //! Default Constructor
    // Do not allow mSize. Assert size and then
    // auto assign mSize
    LinearSystem(Matrix *_mpA, Vector *_mpb);

    //! Copy Constructor
    LinearSystem(const LinearSystem &ls);

    //* Solve using Gauss Elimination with pivoting
    virtual Vector Solve() const;

    //* Ill-posed problem
    Vector SolveLeastSquares() const;
    Vector SolveMinimumNorm() const;
};

#endif