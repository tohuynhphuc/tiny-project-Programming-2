#ifndef POS_SYM_LIN_SYSTEM_HEADER
#define POS_SYM_LIN_SYSTEM_HEADER

#include "LinearSystem.h"

class PosSymLinSystem : public LinearSystem {
   public:
    // Constructor
    PosSymLinSystem(Matrix *A, Vector *b) : LinearSystem(A, b) {}

    int isSymmetric(const Matrix &A) const;
    Vector Solve() const override;
};

#endif