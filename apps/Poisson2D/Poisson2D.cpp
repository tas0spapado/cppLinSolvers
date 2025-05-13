#include "SparseMatrix.h"
#include "Vector.h"
#include "system_solvers.h"
#include <cstddef>
#include <memory>
#include <cmath>
#include <fstream>


/*
    Solution of the PDE u_xx + u_yy = 4 using the Finite Difference method
    Analytical solution u(x,y) = x^2 + y^2
    x in [0,1]
    y in [0,1]
*/


class solverControl{
    std::string solver_name_;
    std::size_t Nx_,Ny_;  //number of intervals in the x and y direction
    double relaxation_factor_; 
    std::size_t max_iter_;
    double tolerance_;
    public:
    solverControl();
    solverControl(const std::string& file_name);    //read controls from a file, named "controls" 
    void write_coordinates() const; 
    inline const std::string& solver_name() const {return solver_name_;}    
    inline std::size_t Nx() const {return Nx_;}
    inline std::size_t Ny() const {return Ny_;}
    inline double relaxation_factor() const {return relaxation_factor_;}
    inline std::size_t max_iter() const {return max_iter_;}
    inline double tolerance() const {return tolerance_;}
    inline std::size_t imax() const {return Nx_+1;}
    inline std::size_t jmax() const {return Ny_+1;}
};

Vector fill_system(Tensor& A, Vector& b, const solverControl& control);


int main()
{
    
    solverControl control("controls");
    std::size_t imax = control.imax();
    std::size_t jmax = control.jmax();
    std::string solver_name = control.solver_name();
    std::size_t max_iter = control.max_iter();
    double tolerance = control.tolerance();
    double relaxation_factor = control.relaxation_factor();

    SparseMatrix A(imax*jmax);
    Vector b(imax*jmax,4.0);
    Vector u(imax*jmax,1.0);   
    Vector an_solution = fill_system(A,b,control);
    
    std::unique_ptr<SystemSolver> solver = system_solvers::create_solver(solver_name,A,u,b);
    solver->set_max_iter(max_iter);
    solver->set_tol(tolerance);
    solver->set_rel_factor(relaxation_factor);
    solver->solve();
    
    //solver->write_matrix("A");
    //solver->write_source("b");


    Vector error = u - an_solution;
    std::cout << "Normalized error norm: " << error.norm()/error.size() << '\n';
    solver->write("u"); 
    control.write_coordinates();

    return 0;
}

solverControl::solverControl()
{
    solver_name_ = "GaussSeidel";
    Nx_ = 100;
    Ny_ = 100;
    relaxation_factor_ = 1.0;
    max_iter_ = 1000;
    tolerance_ = 1.0e-12;
}

solverControl::solverControl(const std::string& file_name)
{
    std::ifstream controls_file;
    controls_file.open(file_name);
    
    controls_file >> solver_name_;
    controls_file >> Nx_;
    controls_file >> Ny_;
    controls_file >> relaxation_factor_;
    controls_file >> max_iter_;
    controls_file >> tolerance_;

    controls_file.close();
}

void solverControl::write_coordinates() const 
{
    std::ofstream output_file;
    output_file.open("coordinates");

    double dx = 1.0/Nx_;
    double dy = 1.0/Ny_;
    std::size_t imax = Nx_ + 1;
    std::size_t jmax = Ny_ + 1;

    for (std::size_t j=0; j<jmax; ++j)
    {
        for (std::size_t i=0; i<imax; ++i)
        {
            output_file << i*dx << '\t' << j*dy << '\n'; 
        }
    }

    output_file.close();
}

Vector fill_system(Tensor& A, Vector& b, const solverControl& control)
{
    double dx = 1.0/control.Nx();
    double dy = 1.0/control.Ny();
    double rdx2 = 1.0/dx * 1.0/dx;
    double rdy2 = 1.0/dy * 1.0/dy;
    std::size_t imax = control.Nx()+1;    
    std::size_t jmax = control.Ny()+1;    
    
    Vector an_solution(imax*jmax,0.0);
    std::size_t k = 0;

    //internal nodes
    for (std::size_t i=1; i<imax-1; ++i)
    {
        for (std::size_t j=1; j<jmax-1; ++j)
        {
            k = i + imax*j;
            an_solution[k] = pow(i*dx,2) + pow(j*dy,2);
            A.set(k,k,-2.0*rdx2-2.0*rdy2);
            A.set(k,k+1,rdx2);
            A.set(k,k-1,rdx2);
            A.set(k,k+imax,rdy2);
            A.set(k,k-jmax,rdy2);
            b[k] = 4.0;
        }
    }

    //x boundaries (x=0 , x=1)
    for (std::size_t j=0; j<jmax; ++j)
    {
        //boundary x=0 (i=0)
        k = imax*j;
        an_solution[k] = pow(j*dy,2);
        A.set(k,k,1.0);
        b[k] = an_solution[k];
        //boundary x=1 (i=imax-1)
        k = imax - 1 + imax*j;
        an_solution[k] = 1.0 + pow(j*dy,2);
        A.set(k,k,1.0);
        b[k] = an_solution[k];
    }

    //y boundaries (y=0 , y=1)
    for (std::size_t i=1; i<imax-1; ++i)
    {
        //boundary y=0 (j=0)
        k = i;
        an_solution[k] = pow(i*dx,2);
        A.set(k,k,1.0);
        b[k] = an_solution[k];
        //boundary y=1 (j=jmax-1)
        k = i + imax*(jmax-1);
        an_solution[k] = pow(i*dx,2) + 1.0;
        A.set(k,k,1.0);
        b[k] = an_solution[k];
    }

    return an_solution;
}
