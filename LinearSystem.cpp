#include "LinearSystem.h"

#include <iostream>
#include <stdexcept>

using namespace std;

// swap rows (i, j)
LinearSystem::LinearSystem(Matrix *A, Vector *b)
{
    mpA = A;
    mpb = b;
    mSize = A->getNumRows();
}

LinearSystem::LinearSystem(const LinearSystem &ls)
{
    mpA = ls.mpA;
    mpb = ls.mpb;
    mSize = ls.mSize;
}
Vector LinearSystem::Solve() const
{
    // Take the size of the matrix
    // Assuming the size matrix is square
    // Vector result(mSize);
    // // Assert(mpA->getNumRows() == mpA->getNumCols());

    // if (mpA->getNumRows() != mpA->getNumCols())
    // {
    //     throw std::invalid_argument("Matrix A must be square.");
    // }
    // for (int i = 0; i < mSize; i++)
    // {
    //     int pivot = *(mpA(i, i));
    //     if (pivot == 0)
    //     {
    //         for (int j = i + 1; j < mSize; j++)
    //         {
    //             if (*(mpA(j, i)) != 0)
    //                 swap_row(i, j);
    //         }
    //     }
    //     if (*(mpA(i, i)) == 0)
    //     {
    //         throw std::invalid_argument("Matrix A is singular.");
    //     }

    //     // Now we have a pivot, we can do the elimination
    //     for (int j = i + 1; j < mSize; j++)
    //     {
    //         double factor = *(mpA(i, j)) / pivot;
    //         for (int k = i; k < mSize + 1; k++)
    //         {
    //             *(mpA(j, k)) -= factor * *(mpA(i, k));
    //         } // mSize + 1 is the size of the augmented matrix
    //     }
    // }

    // // Back substitution
    // for (int i = mSize - 1; i >= 0; i--)
    // {
    //     result(i) = *(mpA(i, mSize));
    //     for (int j = i + 1; j < mSize; j++)
    //     {
    //         result(i) -= *(mpA(i, j)) * result(j);
    //         result(i) /= *(mpA(i, i));
    //     }
    // }
    // The cols here is the number of variables
    // Check the size of the vector
    // 1. Form augmented matrix [A | b]
    Matrix aug(mSize, mSize + 1); // Augmented matrix
    Vector result(mSize);         // Result vector
    for (int i = 0; i < mSize; i++)
    {
        for (int j = 0; j < mSize; j++)
        {
            aug(i + 1, j + 1) = (*mpA)(i + 1, j + 1);
            aug(i + 1, mSize + 1) = (*mpb)(i + 1);
        }
    }

    // 2. Forward elimination
    for (int i = 0; i < mSize; i++)
    {
        // Partial pivoting: find max row in column i
        int maxRow = i;
        for (int k = i + 1; k < mSize; k++)
            if (abs(aug(k + 1, i + 1)) > abs(aug(maxRow + 1, i + 1)))
                maxRow = k;
        // Swap rows if needed
        if (maxRow != i)
        {
            for (int k = i; k <= mSize; k++)
                swap(aug(i + 1, k + 1), aug(maxRow + 1, k + 1));
        }

        // Eliminate below
        for (int j = i + 1; j < mSize; j++)
        {
            double factor = aug(j + 1, i + 1) / aug(i + 1, i + 1);
            for (int k = i; k <= mSize; k++)
                aug(j + 1, k + 1) -= factor * aug(i + 1, k + 1);
        }
    }

    // 3. Back substitution
    for (int i = mSize - 1; i >= 0; i--)
    {
        result(i + 1) = aug(i + 1, mSize + 1);
        for (int j = i + 1; j < mSize; j++)
            result(i + 1) -= aug(i + 1, j + 1) * result(j + 1);
        result(i + 1) /= aug(i + 1, i + 1);
    }
    return result;
}

// In case there are seperate matrix and vector
