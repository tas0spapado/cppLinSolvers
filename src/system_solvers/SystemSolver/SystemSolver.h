#ifndef SYSTEM_SOLVER_H
#define SYSTEM_SOLVER_H

#include <cstddef>
#include <string>
#include <iostream>
#include "Tensor.h"
#include "Vector.h"


class SystemSolver{
    protected:
        std::string name_;      //solver name
        Tensor& A_;             //coefficient matrix - either sparse or full
        Vector& x_;             //solution vector
        Vector& b_;             //source vector
        size_t iter_, max_iter_;  //iterations and maximum number of iterations
        double tolerance_, relative_tolerance_;   //absolute and relative tolerance
        double relaxation_factor_;
        double initial_residual_, residual_;
    public:
        /* Constructors */
        SystemSolver(const std::string& name, Tensor& A, Vector& x, Vector& b);

        virtual ~SystemSolver() = default;

        /* Utilities */
        virtual void solve() = 0;
        void write(const std::string& file_name) const;
        void write_matrix(const std::string& file_name) const;
        void write_source(const std::string& file_name) const;
        inline void print_info() const
        {
            std::cout << "Solver Info" << std::endl;
            std::cout << "===========" << std::endl;
            std::cout << "Solver: " << name_ << std::endl;
            std::cout << "Maximum number of iterations: " << max_iter_ << std::endl;
            std::cout << "Tolerance: " << tolerance_ << std::endl;
            std::cout << "Relative tolerance: " << relative_tolerance_ << std::endl;
            std::cout << "Relaxation factor: " << relaxation_factor_ << std::endl;
            std::cout << "==============================================" << std::endl;
        }
        inline void print_iter() const
        {
            std::cout << "Iteration: " << iter_ << "\t\tResidual: " << residual_ << std::endl;
        }

        /* Accessors */
        inline void set_max_iter(double value) {max_iter_ = value;}
        inline void set_tol(double value) {tolerance_ = value;}
        inline void set_rel_tol(double value) {relative_tolerance_ = value;}
        inline void set_rel_factor(double value) {relaxation_factor_ = value;}
        inline const std::string& name() const {return name_;}
        inline std::string& name() {return name_;}
        inline double residual() const {return residual_;}
};

#endif
