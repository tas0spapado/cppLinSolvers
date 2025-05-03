#include "Matrix.h"
#include "SparseMatrix.h"
#include "Vector.h"
#include "SystemSolver.h"
#include "Jacobi.h"
#include <iostream>
#include <string>
#include <memory>


void print(const std::string& msg)
{
    std::cout << "=====" << msg << "=====" << std::endl;
}

int main()
{
    print("Jacobi Test");
    std::cout << "Solution of a tri-diagonal system.\n\n";

    std::cout << "Solution Using Matrix\n";
    std::cout << "=========================\n";

    print("Coefficient Matrix");
    Matrix A = 
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

    std::unique_ptr<SystemSolver> solver = std::make_unique<Jacobi>(A,x,b);

    solver->set_rel_factor(0.5);
    solver->set_max_iter(100);
    solver->set_tol(1e-10);

    solver->solve();
    print("Solution");
    x.print();


    std::cout << "Solution Using SparseMatrix\n";
    std::cout << "=========================\n";

    SparseMatrix A_s(A);
    Vector b_s(b);
    Vector x_s(b.size(),0.0);
    
    std::unique_ptr<SystemSolver> solver_s = std::make_unique<Jacobi>(A_s,x_s,b_s);

    solver_s->set_rel_factor(0.5);
    solver_s->set_max_iter(100);
    solver_s->set_tol(1e-10);

    solver_s->solve();
    print("Solution");
    x_s.print();



    return 0;
}
