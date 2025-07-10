#include "system_solvers.h"
#include "Jacobi.h"
#include "pJacobi.h"
#include "GaussSeidel.h"

const std::unordered_map<std::string, std::unique_ptr<SystemSolver> (*)(Tensor& A, Vector& x, Vector&b)> system_solvers::solvers =
{
    {"Jacobi", [](Tensor& A, Vector& x, Vector&b) -> std::unique_ptr<SystemSolver>{return std::make_unique<Jacobi>(A,x,b);}},
    {"pJacobi", [](Tensor& A, Vector& x, Vector&b) -> std::unique_ptr<SystemSolver>{return std::make_unique<pJacobi>(A,x,b);}},
    {"GaussSeidel", [](Tensor& A, Vector& x, Vector&b) -> std::unique_ptr<SystemSolver>{return std::make_unique<GaussSeidel>(A,x,b);}}
};



