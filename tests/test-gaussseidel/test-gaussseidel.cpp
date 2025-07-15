#include "SparseMatrix.h"
#include "Vector.h"
#include "SystemSolver.h"
#include "GaussSeidel.h"
#include <iostream>
#include <string>
#include <memory>
#include "openmp_settings.h"

void print(const std::string& msg)
{
    std::cout << "=====" << msg << "=====" << std::endl;
}

int main()
{
    openmp_settings::set_num_threads(1); 

    print("GaussSeidel Test");
    std::cout << "Solution of a tri-diagonal system.\n\n";

    print("Coefficient Matrix");
    SparseMatrix A = 
    {
        {4,1,0,0,0},
        {1,4,1,0,0},
        {0,1,4,1,0},
        {0,0,1,4,1},
        {0,0,0,1,4}
    };
    A.print(); 

    print("Source Vector");
    Vector b = {6,12,18,24,24};
    b.print();

    print("Initial Guess");
    Vector x(b.size(),0.0);
    x.print();

    std::unique_ptr<SystemSolver> solver = std::make_unique<GaussSeidel>(A,x,b);

    solver->set_rel_factor(0.5);
    solver->set_max_iter(100);
    solver->set_tol(1e-10);

    solver->solve();
    print("Solution");
    x.print();

    return 0;
}

