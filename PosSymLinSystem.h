#ifndef POS_SYM_LIN_SYSTEM_HEADER
#define POS_SYM_LIN_SYSTEM_HEADER

#include "LinearSystem.h"

class PosSymLinSystem : public LinearSystem
{
public:
    Matrix transposed_matrix(const Matrix& other) const;
    int isSymmetric(Matrix* A) const;
    Vector Solve() const override;
};

#endif