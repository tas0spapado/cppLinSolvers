#ifndef PJACOBI_H
#define PJACOBI_H

#include "SystemSolver.h"

class pJacobi: public SystemSolver{
    public:
        /* Constructors */
        pJacobi(Tensor& A, Vector& x, Vector& b);
        void solve() override;
};


#endif
