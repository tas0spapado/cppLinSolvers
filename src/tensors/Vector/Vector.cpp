#include "Vector.h"
#include <cstdlib>
#include <iostream>

Vector::Vector(int m, double value):
Tensor(m,1,value)
{}

Vector::Vector(const Tensor& other):
Tensor(other)
{
    if (M>1 && N>1) 
    {
        std::cerr << "FATAL ERROR: initiated vector with more than 1 rows and columns\n";
        std::exit(EXIT_FAILURE);
    }
}

const double& Vector::at(int ii) const 
{
    return 
    (
        (M>1)?A.at(ii).at(0):A.at(0).at(ii)
    );
}

double& Vector::at(int ii) 
{
    return 
    (
        (M>1)?A.at(ii).at(0):A.at(0).at(ii)
    );
}

int Vector::size() const 
{
    if (M>1) 
        return M; 
    else 
        return N;
}

double Vector::operator&(const Vector& rhs) const 
{
    double dot_product = 0.0;

    if (this->size() != rhs.size())
    {
        std::cerr << "FATAL ERROR: cannot compute dot product of vectors with different length\n";
        std::exit(EXIT_FAILURE);
    }

    for (int i=0; i<size(); ++i)
        dot_product += this->at(i)*rhs.at(i);

    return dot_product;
}

