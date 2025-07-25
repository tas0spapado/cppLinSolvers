#include "GaussSeidel.h"
#include <cstddef>

REGISTER_DERIVED
(
    SystemSolver, 
    GaussSeidel, 
    (const Tensor& A, Vector& x, const Vector& b),
    (A, x, b)
)


GaussSeidel::GaussSeidel(const Tensor& A, Vector& x, const Vector& b):
SystemSolver("GaussSeidel", A, x, b)
{}


void GaussSeidel::solve()
{
    iter_ = 0;
    initial_residual_ = (b_ - A_*x_).norm();
    residual_ = 1.0;

    print_info();
    std::cout << "Absolute initial residual: " << initial_residual_ << '\n';
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


