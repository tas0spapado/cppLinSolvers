#include "Matrix.h"
#include <cstddef>
#include <cstdlib>
#include <iostream>

Matrix::Matrix(size_t m, double value):
Tensor(m,m,value)
{}


Matrix::Matrix(std::initializer_list<std::initializer_list<double>> init):
Tensor(init)
{
    if (this->rows() != this->columns())
    {
        std::cerr << "FATAL ERROR: Attempt to create non-square Matrix.\n";
        std::exit(EXIT_FAILURE);
    }
}


Matrix::Matrix(const Tensor& other):
Tensor(other)
{
    if (this->rows() != this->columns())
    {
        std::cerr << "FATAL ERROR: Cannot construct Matrix from Tensor - not square.\n";
        std::exit(EXIT_FAILURE);
    }
}
