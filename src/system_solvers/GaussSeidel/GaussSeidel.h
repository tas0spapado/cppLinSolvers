#ifndef GAUSS_SEIDEL_H
#define GAUSS_SEIDEL_H

#include "SystemSolver.h"

class GaussSeidel: public SystemSolver{
    public:
        /* Constructors */
        GaussSeidel(Tensor& A, Vector& x, Vector& b);
        void solve() override;
};


#endif

