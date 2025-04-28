#ifndef JACOBI_H
#define JACOBI_H

#include "SystemSolver.h"

class Jacobi: public SystemSolver{
    public:
        /* Constructors */
        Jacobi(Tensor& A, Vector& x, Vector& b);
        void solve() override;
};


#endif
