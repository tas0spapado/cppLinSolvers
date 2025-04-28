#include "Jacobi.h"
#include <cstddef>

Jacobi::Jacobi(Tensor& A, Vector& x, Vector& b):
SystemSolver("Jacobi", A, x, b)
{}


void Jacobi::solve()
{
    print_info();
    print_iter(); 

    Vector x_old_(x_);

    while(++iter_ <= max_iter_)
    {
        for (size_t i=0; i<x_.size(); ++i)
        {
            x_[i] = (1-relaxation_factor_)*x_old_[i] 
                    + relaxation_factor_/A_(i,i)*b_[i];
            for (size_t j=0; j<x_.size(); ++j)
            {
                if (i==j)
                    continue;

                x_[i] -= relaxation_factor_/A_(i,i)*A_(i,j)*x_old_[j];
            }
        }

        residual_ = (b_ - A_*x_).norm()/initial_residual_;
        
        print_iter();
        
        if (residual_ <= tolerance_ )
        {
            std::cout << "CONVERGED after " << iter_ << " iterations.\n";
            break;
        }
        x_old_ = x_;
    }

    if (iter_ > max_iter_)
        std::cout << "NOT CONVERGED after " << iter_ - 1 << " iterations.\n";
    
}

