#include "PosSymLinSystem.h"

#include <cassert>
#include <iostream>
#include <stdexcept>

using namespace std;

int PosSymLinSystem::isSymmetric(const Matrix& A) const {
    Matrix result(A.transpose());
    int flag = 1;
    for (int i = 0; i < A.getNumRows(); i++) {
        for (int j = 0; j < A.getNumCols(); j++) {
            if (result(i, j) != A(i, j)) {
                flag = 0;
            }
        }
    }
    if (flag == 1) {
        return 1;
    } else {
        return 0;
    }
}

Vector PosSymLinSystem::Solve() const {
    int max_interations = 1000;
    double tolerance = 1e-10;
    Vector x(mSize);               // Initialize the [0, 0, ..., 0] vector
    Vector r = *mpb - (*mpA) * x;  // Initial residual
    // r0 = b - Ax
    Vector p = r;  // p0 = r0

    double rsold = r * r;  // Initial residual squared

    for (int i = 0; i < max_interations; i++) {
        Vector Ap = (*mpA) * p;  // Compute Ap
        double alpha = rsold / (p * Ap);
        // Update solution
        x = x + p * alpha;
        // Update residual
        Vector r_next = r - Ap * alpha;
        double rsnew = r_next * r_next;  // New residual squared
        // Check convergence
        if (rsnew < tolerance * tolerance) {
            break;  // Converged
        }
        // beta
        double beta = rsnew / rsold;
        // update p
        p = r_next + p * beta;
        // update residual
        r = r_next;
        rsold = rsnew;  // Update rsold for next iteration
    }
    return x;
}