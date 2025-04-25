#include "Tensor.h"
#include <cstddef>
#include <iostream>
#include <cmath>

void Tensor::initialize()
{
    n_rows = storage_rows;
    n_cols = storage_cols;
}

Tensor Tensor::eye(size_t m)
{
    Tensor result(m,m,0.0);
    for (size_t i=0; i<m; ++i)
        result.at(i,i) = 1.0;

    return result;
}


Tensor::Tensor():
storage_rows(1),
storage_cols(1),
A(1, std::vector<double>(1,0.0))
{
    initialize();
}


Tensor::Tensor(size_t m, size_t n, double value):
storage_rows(m),
storage_cols(n),
A(m,std::vector<double>(n,value))
{
    initialize();
}


Tensor::Tensor(std::initializer_list<std::initializer_list<double>> init)
{
    if (init.size() == 0)
    {
        std::cerr << "FATAL ERROR: Initializer list for Tensor is empty.\n";
        std::exit(EXIT_FAILURE);
    }

    storage_rows = init.size();
    storage_cols = init.begin()->size();

    for (const auto& row: init)
    {
        if (row.size() != storage_cols)
        {
            std::cerr << "FATAL ERROR: Inconsistent row sizes in initializer list.\n";
            std::exit(EXIT_FAILURE);
        }
    }

    A.resize(storage_rows,std::vector<double>(storage_cols,0.0));

    size_t i = 0;
    for (const auto& row: init)
    {
        size_t j = 0;
        for (double val: row)
            A.at(i).at(j++) = val;
        ++i;
    }

    initialize();
}


Tensor::Tensor(const Tensor& other):
storage_rows(other.storage_rows),
storage_cols(other.storage_cols),
A(other.A)
{
    initialize();
}


Tensor::Tensor(Tensor&& other) noexcept:
storage_rows(other.storage_rows), 
storage_cols(other.storage_cols), 
A(std::move(other.A))
{
    other.storage_rows = 0;
    other.storage_cols = 0;
    other.n_rows = 0;
    other.n_cols =0;
    initialize();
}


const double& Tensor::at(size_t i, size_t j) const
{
    return A.at(i).at(j);
}


double& Tensor::at(size_t i, size_t j)
{
    return A.at(i).at(j);
}


Tensor Tensor::extract_row(size_t i) const
{
    if (i >= this->rows())
    {
        std::cerr << "FATAL ERROR: extract_row index " << i << " out of bounds for Tensor with " << this->rows() << " rows.\n";
        std::exit(EXIT_FAILURE);
    }

    Tensor row(1,this->columns(),0.0);

    for (size_t j=0; j<this->columns(); j++)
        row.at(0,j) = this->at(i,j);

    return row;
}


Tensor Tensor::extract_column(size_t j) const 
{
    if (j >= this->columns())
    {
        std::cerr << "FATAL ERROR: extract_column index " << j << " out of bounds for Tensor with " << this->columns() << " columns.\n";
        std::exit(EXIT_FAILURE);
    }

    Tensor column(this->rows(), 1, 0.0);

    for (size_t i=0; i<this->rows(); i++)
        column.at(i,0) = this->at(i,j);

    return column;
}


Tensor& Tensor::operator=(const Tensor& rhs)
{
    if (this == &rhs)
        return *this;

    storage_rows = rhs.storage_rows;
    storage_cols = rhs.storage_cols;
    A = rhs.A;
    
    initialize();

    return *this;
}


Tensor& Tensor::operator=(Tensor&& rhs) noexcept
{
    if (this == &rhs)   
        return *this;

    storage_rows = rhs.storage_rows;
    storage_cols = rhs.storage_cols;
    A = std::move(rhs.A);
    initialize();

    rhs.storage_rows = 0;
    rhs.storage_cols = 0;
    rhs.n_rows = 0;
    rhs.n_cols = 0;

    return *this;
}

Tensor Tensor::operator*(const Tensor& rhs) const
{
    if (this->columns() != rhs.rows())
    {
        std::cerr << "FATAL ERROR: Tensor multiplication dimension mismatch:\n"
            << "Attempted: (" << this->rows() << "x" << this->columns() << ") * (" 
            << rhs.rows() << "x" << rhs.columns() << ").\n";
        std::exit(EXIT_FAILURE);
    }

    Tensor result(this->rows(),rhs.columns(),0.0);
    
    for (size_t i=0; i<result.rows(); ++i)
    {
        for (size_t j=0; j<result.columns(); ++j)
        {
            for (size_t k=0; k < this->columns(); ++k)
            {
                result(i,j) += this->at(i,k)*rhs.at(k,j);
            }
        }
    }

    return result;
}


Tensor Tensor::operator+(const Tensor& rhs) const
{
    if (this->rows() != rhs.rows() || this->columns() != rhs.columns())
    {
        std::cerr << "FATAL ERROR: Tensor addition dimension mismatch:\n"
            << "Attempted: (" << this->rows() << "x" << this->columns() << ") + (" 
            << rhs.rows() << "x" << rhs.columns() << ").\n";
        std::exit(EXIT_FAILURE);
    }

    Tensor result(this->rows(), this->columns(), 0.0);

    for (size_t i=0; i<this->rows(); ++i)
    {
        for (size_t j=0; j < this->columns(); ++j)
        {
            result(i,j) = this->at(i,j)+rhs.at(i,j);
        }
    }

    return result;
}


Tensor Tensor::operator-(const Tensor& rhs) const
{
    if (this->rows() != rhs.rows() || this->columns() != rhs.columns())
    {
        std::cerr << "FATAL ERROR: Tensor subtraction dimension mismatch:\n"
            << "Attempted: (" << this->rows() << "x" << this->columns() << ") - (" 
            << rhs.rows() << "x" << rhs.columns() << ").\n";
        std::exit(EXIT_FAILURE);
    }

    Tensor result(this->rows(), this->columns(), 0.0);

    for (size_t i=0; i<this->rows(); ++i)
    {
        for (size_t j=0; j < this->columns(); ++j)
        {
            result(i,j) = this->at(i,j)-rhs.at(i,j);
        }
    }

    return result;
}


Tensor Tensor::operator+(double rhs) const 
{
    Tensor result(*this);
    for (auto& row: result.A)
        for (double& value: row)
            value += rhs;

    return result; 
}


Tensor Tensor::operator-(double rhs) const 
{
    Tensor result(*this);
    for (auto& row: result.A)
        for (double& value: row)
            value -= rhs;

    return result; 
}


Tensor operator*(double lhs, const Tensor& rhs)
{
    Tensor result(rhs);
    for (auto& row: result.A)
        for (double& value: row)
            value *= lhs;

    return result; 
}


Tensor& Tensor::operator+=(const Tensor& rhs)
{
    /*for (size_t i=0; i<this->rows(); ++i)
    {
        for (size_t j=0; j<this->columns(); ++j)
            this->at(i,j) += rhs.at(i,j);
    }*/

    *this = *this + rhs; 
    return *this;
}


Tensor& Tensor::operator+=(double rhs)
{
    /*for (size_t i=0; i<this->rows(); ++i)
    {
        for (size_t j=0; j<this->columns(); ++j)
            this->at(i,j) += rhs;
    }*/

    *this = *this + rhs;
    return *this;
}


Tensor& Tensor::operator-=(const Tensor& rhs)
{
    /*for (size_t i=0; i<this->rows(); ++i)
    {
        for (size_t j=0; j<this->columns(); ++j)
            this->at(i,j) -= rhs.at(i,j);
    }*/

    *this = *this - rhs;
    return *this;
}


Tensor& Tensor::operator-=(double rhs)
{
    /*for (size_t i=0; i<this->rows(); ++i)
    {
        for (size_t j=0; j<this->columns(); ++j)
            this->at(i,j) -= rhs;
    }*/

    *this = *this - rhs; 
    return *this;
}


Tensor& Tensor::operator*=(const Tensor& rhs)
{
    /*for (size_t i=0; i<this->rows(); ++i)
    {
        for (size_t j=0; j<this->columns(); ++j)
            this->at(i,j) *= rhs.at(i,j);
    }*/

    *this = *this * rhs;
    return *this;
}


Tensor& Tensor::operator*=(double rhs)
{
    /*for (size_t i=0; i<this->rows(); ++i)
    {
        for (size_t j=0; j<this->columns(); ++j)
            this->at(i,j) *= rhs;
    }*/

    *this = rhs * (*this);
    return *this;
}


Tensor Tensor::operator-() const 
{
    Tensor result(*this);
    for (size_t i=0; i<this->rows(); ++i)
    {
        for (size_t j=0; j<this->columns(); ++j)
            result.at(i,j) = -result.at(i,j);
    }

    return result;
}


void Tensor::print() const 
{
    for (size_t i=0; i<this->rows(); ++i)
    {
        for (size_t j=0; j<this->columns(); ++j)
            std::cout << this->at(i,j) << " ";
        std::cout << '\n';
    }
    std::cout << '\n';
}


double Tensor::norm() const 
{
    double result= 0.0;

    for (size_t i=0; i<this->rows(); ++i)
    {
        for (size_t j=0; j<this->columns(); ++j)
            result += pow(at(i,j),2);
    }
    
    return sqrt(result); 
}


void Tensor::transpose()
{
    Tensor T(columns(), rows(), 0.0);

    for (size_t i=0; i<this->rows(); ++i)
    {
        for (size_t j=0; j<this->columns(); ++j)
        {
            T(j,i) = this->at(i,j);
        }
    }

    *this = std::move(T);
}


