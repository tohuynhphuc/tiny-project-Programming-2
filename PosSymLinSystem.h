#ifndef POS_SYM_LIN_SYSTEM_HEADER
#define POS_SYM_LIN_SYSTEM_HEADER

#include "LinearSystem.h"

class PosSymLinSystem : public LinearSystem {
   public:
    // Constructor
    PosSymLinSystem(Matrix *A, Vector *b) : LinearSystem(A, b) {}

    bool isPositiveDefinite() const;
    bool isSymmetric() const;
    Vector Solve() const override;
};

#endif