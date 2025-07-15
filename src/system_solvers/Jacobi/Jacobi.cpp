#include "Jacobi.h"
#include <cstddef>
#include <omp.h>
#include "openmp_settings.h"

REGISTER_DERIVED
(
    SystemSolver, 
    Jacobi, 
    (const Tensor& A, Vector& x, const Vector& b),
    (A, x, b)
)


Jacobi::Jacobi(const Tensor& A, Vector& x, const Vector& b):
SystemSolver("Jacobi", A, x, b)
{}


void Jacobi::solve()
{
    std::cout << "Solving in " << openmp_settings::num_threads << " threads\n";
    iter_ = 0;
    initial_residual_ = (b_ - A_*x_).norm();
    residual_ = 1.0;
    
    print_info();
    std::cout << "Absolute initial residual: " << initial_residual_ << '\n';
    print_iter(); 

    Vector x_old_(x_);

    while(++iter_ <= max_iter_)
    {
        #pragma omp parallel for
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
        swap(x_,x_old_);
    }

    if (iter_ > max_iter_)
        std::cout << "NOT CONVERGED after " << iter_ - 1 << " iterations.\n";
    
}

