#include "Vector.h"
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <cstdlib>


Vector::Vector(size_t m, double value):
Tensor(m,1,value)
{}


Vector::Vector(std::initializer_list<double> init):
Tensor(1,init.size(),0.0)
{
    size_t j=0;
    for (double val: init)
        this->at(0,j++) = val;
}


Vector::Vector(const Tensor& other):
Tensor(other)
{
    if (!(this->rows()==1 || this->columns()==1))
    {
        std::cerr << "FATAL ERROR: Cannot construct Vector from Tensor - not 1D.\n";
        std::exit(EXIT_FAILURE);
    }
}


size_t Vector::size() const 
{
    return 
    (
        (this->rows() > this->columns()) ? this->rows() : this->columns()
    );
}


double& Vector::operator[](size_t i)
{
    if (i>=this->size())
    {
        std::cerr << "FATAL ERROR: index " << i << " out of bounds for Vector with size: " << this->size() << ".\n";
        std::exit(EXIT_FAILURE);
    }
    
    return 
    (
        (this->rows() > this->columns())
        ?
        this->at(i,0)
        :
        this->at(0,i)
    );
}


const double& Vector::operator[](size_t i) const 
{
    if (i>=this->size())
    {
        std::cerr << "FATAL ERROR: index " << i << " out of bounds for Vector with size: " << this->size() << ".\n";
        std::exit(EXIT_FAILURE);
    }
    
    return 
    (
        (this->rows() > this->columns())
        ?
        this->at(i,0)
        :
        this->at(0,i)
    );
}


double Vector::operator&(const Vector& rhs) const 
{
    if (this->size()!=rhs.size())
    {
        std::cerr << "FATAL ERROR: Vector dot product dimension mismatch.\n";
        std::exit(EXIT_FAILURE);
    }
    double result = 0.0;

    for (size_t i=0; i<this->size(); ++i)
        result += this->operator[](i)*rhs[i];

    return result; 
}

