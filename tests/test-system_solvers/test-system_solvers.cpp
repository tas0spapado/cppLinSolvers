#include <SparseMatrix.h>
#include <Vector.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <memory>
#include "SystemSolver.h"
#include "openmp_settings.h"


void print(const std::string& msg)
{
    std::cout << "=====" << msg << "=====" << std::endl;
}

int main()
{
    openmp_settings::set_num_threads(1);

    print("system_solvers Test");
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

    std::string solver_name;
    size_t i = 0;
    std::cout << "Available solvers:\n";
    for (const auto& pair: SystemSolver::SystemSolver_registry())
        std::cout << ++i << ". " << pair.first << std::endl;
    std::cout << "Select solver: ";
    std::cin >> solver_name;

    std::unique_ptr<SystemSolver> solver = 
        SystemSolver::create(solver_name,A,x,b); 

    if (!solver)
    {
        std::cerr << "FATAL ERROR: No solver selected!\n";
        std::exit(EXIT_FAILURE);
    }

    solver->set_rel_factor(0.5);
    solver->set_max_iter(100);
    solver->set_tol(1e-10);

    solver->solve();
    print("Solution");
    x.print();

    return 0;
}

