#include "GaussSeidel.h"
#include <cstddef>

GaussSeidel::GaussSeidel(Tensor& A, Vector& x, Vector& b):
SystemSolver("GaussSeidel", A, x, b)
{}


void GaussSeidel::solve()
{
    print_info();
    print_iter(); 


    while(++iter_ <= max_iter_)
    {
        for (size_t i=0; i<x_.size(); ++i)
        {
            x_[i] = (1-relaxation_factor_)*x_[i] 
                    + relaxation_factor_/A_(i,i)*b_[i];
            for (size_t j=0; j<x_.size(); ++j)
            {
                if (i==j)
                    continue;

                x_[i] -= relaxation_factor_/A_(i,i)*A_(i,j)*x_[j];
            }
        }

        residual_ = (b_ - A_*x_).norm()/initial_residual_;
        
        print_iter();
        
        if (residual_ <= tolerance_ )
        {
            std::cout << "CONVERGED after " << iter_ << " iterations.\n";
            break;
        }
    }

    if (iter_ > max_iter_)
        std::cout << "NOT CONVERGED after " << iter_ - 1 << " iterations.\n";
    
}


