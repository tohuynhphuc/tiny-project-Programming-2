#include "LinearSystem.h"

#include <cassert>
#include <iostream>
#include <stdexcept>

using namespace std;

//* ----------Constructors----------
//! Default Constructor
LinearSystem::LinearSystem(Matrix *A, Vector *b) {
    //? Vector size must match
    assert(b->getSize() == A->getNumRows());

    mpA = A;
    mpb = b;
    mSize = b->getSize();
}

//! Copy Constructor
LinearSystem::LinearSystem(const LinearSystem &ls) {
    mpA = ls.mpA;
    mpb = ls.mpb;
    mSize = ls.mSize;
}

//* ----------Solve----------
Vector LinearSystem::Solve() const {
    //& Check when not square matrix
    if (mpA->getNumRows() > mpA->getNumCols()) {
        return this->SolveLeastSquares();
    } else if (mpA->getNumRows() < mpA->getNumCols()) {
        return this->SolveMinimumNorm();
    }

    //& 1. Form augmented matrix [A | b]
    Matrix aug(mSize, mSize + 1);  // Augmented matrix
    Vector result(mSize);          // Result vector
    for (int i = 1; i <= mSize; i++) {
        for (int j = 1; j <= mSize; j++) {
            aug(i, j) = (*mpA)(i, j);
        }
        aug(i, mSize + 1) = (*mpb)(i);
    }

    //& 2. Forward elimination
    for (int i = 0; i < mSize; i++) {
        // Partial pivoting: find max row in column i
        int maxRow = i;
        for (int k = i + 1; k < mSize; k++) {
            if (abs(aug(k + 1, i + 1)) > abs(aug(maxRow + 1, i + 1))) {
                maxRow = k;
            }
        }

        // Swap rows if needed
        if (maxRow != i) {
            for (int k = i; k <= mSize; k++) {
                swap(aug(i + 1, k + 1), aug(maxRow + 1, k + 1));
            }
        }

        // Eliminate below
        for (int j = i + 1; j < mSize; j++) {
            double factor = aug(j + 1, i + 1) / aug(i + 1, i + 1);

            for (int k = i; k <= mSize; k++) {
                aug(j + 1, k + 1) -= factor * aug(i + 1, k + 1);
            }
        }
    }

    //& 3. Back substitution
    for (int i = mSize - 1; i >= 0; i--) {
        result(i + 1) = aug(i + 1, mSize + 1);
        for (int j = i + 1; j < mSize; j++) {
            result(i + 1) -= aug(i + 1, j + 1) * result(j + 1);
        }
        result(i + 1) /= aug(i + 1, i + 1);
    }
    cout << "I GOT  THREE";

    return result;
}

//* ----------Over-determined----------
Vector LinearSystem::SolveLeastSquares() const {
    //? Rows > Col
    assert(mpA->getNumRows() > mpA->getNumCols());

    Matrix At = mpA->transpose();
    Matrix AtA = At * (*mpA);
    Vector Atb = At * (*mpb);

    // Solve the normal equations AtA * x = Atb
    LinearSystem ls(&AtA, &Atb);
    return ls.Solve();
}

//* ----------Under-determined----------
Vector LinearSystem::SolveMinimumNorm() const {
    //? Rows < Col
    assert(mpA->getNumRows() < mpA->getNumCols());

    Matrix At = mpA->transpose();
    Matrix AAt = (*mpA) * At;

    // Solve AAt * y = b for y
    LinearSystem sysAAt(&AAt, mpb);
    Vector y = sysAAt.Solve();

    // x = At * y
    Vector x = At * y;

    return x;
}
