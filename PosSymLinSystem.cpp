#include "PosSymLinSystem.h"

#include <cassert>
#include <iostream>
#include <stdexcept>

#include "Vector.h"

using namespace std;

bool PosSymLinSystem::isSymmetric() const {
    Matrix A = *mpA;
    Matrix result(A.transpose());
    int flag = 1;

    for (int i = 1; i <= A.getNumRows(); i++) {
        for (int j = 1; j <= A.getNumCols(); j++) {
            if (result(i, j) != A(i, j)) {
                flag = 0;
            }
        }
    }

    return flag;
}

bool PosSymLinSystem::isPositiveDefinite() const {
    if (!isSymmetric()) return false;

    Matrix A = *mpA;
    int first_pivot = A(1, 1);  // Get the first pivot;

    for (int i = 1; i <= mSize; i++) {
        Matrix sub_matrix = Matrix(i, i);
        for (int j = 1; j <= i; j++) {
            for (int k = 1; k <= i; k++) {
                sub_matrix(j, k) = A(j, k);
            }
        }

        if (sub_matrix.determinant() < 0) return false;
    }

    return true;
}

Vector PosSymLinSystem::Solve() const {
    if (!(isSymmetric() && isPositiveDefinite())) {
        cout << "Cannot solve because system is not positive definite "
                "symmetric\n";
        Vector v(mSize);
        return v;
    }

    int max_interations = 1000;
    double tolerance = 1e-10;
    Vector x(mSize);               // Initialize the [0, 0, ..., 0] vector
    Vector r = *mpb - (*mpA) * x;  // Initial residual
    // r0 = b - Ax
    Vector p = r;  // p0 = r0

    double rsOld = r * r;  // Initial residual squared

    for (int i = 0; i < max_interations; i++) {
        Vector Ap = (*mpA) * p;  // Compute Ap
        double alpha = rsOld / (p * Ap);

        // Update solution
        x = x + p * alpha;
        // Update residual
        Vector rNext = r - Ap * alpha;
        double rsNew = rNext * rNext;  // New residual squared

        // Check convergence
        if (rsNew < tolerance * tolerance) {
            break;  // Converged
        }

        // Update p
        p = rNext + p * (rsNew / rsOld);
        // Update residual
        r = rNext;
        // Update rsOld for next iteration
        rsOld = rsNew;
    }
    return x;
}