#ifndef SYSTEM_SOLVERS_H
#define SYSTEM_SOLVERS_H

#include "SystemSolver.h"
#include "Jacobi.h"
#include "GaussSeidel.h"

#include <memory>
#include <string>
#include <unordered_map>

namespace system_solvers{

    static const std::unordered_map<std::string, std::unique_ptr<SystemSolver> (*)(Tensor& A, Vector& x, Vector&b)> solvers =
    {
        {"Jacobi", [](Tensor& A, Vector& x, Vector&b) -> std::unique_ptr<SystemSolver>{return std::make_unique<Jacobi>(A,x,b);}},
        {"GaussSeidel", [](Tensor& A, Vector& x, Vector&b) -> std::unique_ptr<SystemSolver>{return std::make_unique<GaussSeidel>(A,x,b);}}
    };

    inline std::unique_ptr<SystemSolver> create_solver(const std::string& solver_name, Tensor& A, Vector& x, Vector& b)
    {
        auto it = solvers.find(solver_name);

        if (it != solvers.end())
            return it->second(A,x,b);
        else
        {
            std::cerr << "ERROR: Solver " << solver_name << " not found. Available solvers:\n";
            for (const auto& pair: solvers)
                std::cerr << pair.first << std::endl;
        }
        return nullptr;
    }
}


#endif
