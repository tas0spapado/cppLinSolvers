#ifndef JACOBI_H
#define JACOBI_H

#include "SystemSolver.h"

class Jacobi: public SystemSolver{
    public:
        /* Constructors */
        Jacobi(const Tensor& A, Vector& x, const Vector& b);
        void solve() override;
};


#endif
