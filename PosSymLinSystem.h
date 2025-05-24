#ifndef POS_SYM_LIN_SYSTEM_HEADER
#define POS_SYM_LIN_SYSTEM_HEADER

#include "LinearSystem.h"

class PosSymLinSystem : public LinearSystem
{
public:
    Vector Solve() const override;
};

#endif