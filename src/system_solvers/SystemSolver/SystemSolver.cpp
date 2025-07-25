#include "SystemSolver.h"
#include <cstdlib>
#include <fstream>

std::unique_ptr<SystemSolver> SystemSolver::create
(
    const std::string& name,
    const Tensor& A,
    Vector& x,
    const Vector& b
)
{
    auto it = SystemSolver::SystemSolver_registry().find(name);
    if (it != SystemSolver::SystemSolver_registry().end())
        return std::unique_ptr<SystemSolver>(it->second(A,x,b));
    else 
    {
        std::cerr << "Error: Solver " << name << " not found.\nAvailable Solvers:\n";
        for (const auto& [key,value]: SystemSolver::SystemSolver_registry())
            std::cerr << key << std::endl;
        std::cerr << std::endl;
    }
    return nullptr;
}


SystemSolver::SystemSolver(const std::string& name, const Tensor& A, Vector& x, const Vector& b):
name_(name),
A_(A),
x_(x),
b_(b),
iter_(0),
max_iter_(2000),
tolerance_(1e-5),
relative_tolerance_(1e-3),
relaxation_factor_(1.0)
{
    /* Checks */
    if (x_.size() != b_.size())
    {
        std::cerr << "FATAL ERROR: Inconsistent solution vector and source vector dimensions:\n"
            << "Solution vector size: " << x_.size() << std::endl
            << "Source vector size: " << b_.size();
        std::exit(EXIT_FAILURE);
    }
    if (!A_.is_square())
    {
        std::cerr << "FATAL ERROR: Coefficient matrix is not square:\n"
            << "Dimensions: " << A_.rows() << " x " << A_.columns() << std::endl; 
        std::exit(EXIT_FAILURE);
    }
    if (A.columns() != x_.size())
    {
        std::cerr << "FATAL ERROR: Inconsistent system dimensions:\n"
            << "Coefficient matrix dimensions: " << A_.rows() << " x " << A_.columns() << std::endl
            << "Solution vector size: " << x_.size()
            << "Source vector size: " << b_.size() << std::endl;
        std::exit(EXIT_FAILURE);
    }

    initial_residual_ = (b_ - A_*x_).norm();
    residual_ = 1.0;
}


void SystemSolver::write(const std::string& file_name) const 
{
    std::ofstream output_file; 
    output_file.open(file_name);

    for (size_t i=0; i<x_.size(); ++i)
        output_file << x_[i] << std::endl;

    output_file.close();
}


void SystemSolver::write_matrix(const std::string& file_name) const 
{
    std::ofstream output_file;
    output_file.open(file_name);

    for (size_t i=0; i<A_.rows(); ++i)
    {
        for (size_t j=0; j<A_.columns(); ++j)
            output_file << A_(i,j) << " ";
        output_file << '\n';
    }

    output_file.close();
}


void SystemSolver::write_source(const std::string& file_name) const 
{
    std::ofstream output_file; 
    output_file.open(file_name);

    for (size_t i=0; i<b_.size(); ++i)
        output_file << b_[i] << std::endl;

    output_file.close();
}

