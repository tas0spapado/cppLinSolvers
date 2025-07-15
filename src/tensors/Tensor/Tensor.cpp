#include "Tensor.h"
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <typeinfo>
#include "openmp_settings.h"

Tensor Tensor::eye(size_t m)
{
    Tensor result(m,m,0.0);
    for (size_t i=0; i<m; ++i)
        result.set(i,i,1.0);

    return result;
}


Tensor::Tensor():
A_(),
rows_(0),
cols_(0)
{}


Tensor::Tensor(size_t m, size_t n, double value):
A_(m*n,value),
rows_(m),
cols_(n)
{}


Tensor::Tensor(const std::initializer_list<std::initializer_list<double>>& init)
{
    if (init.size() == 0)
    {
        std::cerr << "FATAL ERROR: Initializer list for Tensor is empty.\n";
        std::exit(EXIT_FAILURE);
    }

    rows_ = init.size();
    cols_ = init.begin()->size();

    for (const auto& row: init)
    {
        if (row.size() != cols_)
        {
            std::cerr << "FATAL ERROR: Inconsistent row sizes in initializer list.\n";
            std::exit(EXIT_FAILURE);
        }
    }
    
    for (const auto& row: init)
    {
        for (const double& val: row)
            A_.push_back(val);
    }
}


Tensor::Tensor(const Tensor& other):
A_(other.A_),
rows_(other.rows_),
cols_(other.cols_)
{}


Tensor::Tensor(Tensor&& other) noexcept:
A_(std::move(other.A_)),
rows_(other.rows_),
cols_(other.cols_)
{
    other.rows_ = 0;
    other.cols_ =0;
}


const double& Tensor::at(size_t i, size_t j) const
{
    if (i>=this->rows() || j>=this->columns())
    {
        std::cerr << "FATAL ERROR: Attempted to access element (" << i << "," << j << ") of a " 
            << rows_ << "x" << cols_ << "tensor.\n";  
        std::exit(EXIT_FAILURE);
    }

    return A_.at(i*cols_+j);
}


void Tensor::set(size_t i, size_t j, double value)
{
    if (i>=this->rows() || j>=this->columns())
    {
        std::cerr << "FATAL ERROR: Attempted to modify element (" << i << "," << j << ") of a " 
            << rows_ << "x" << cols_ << " tensor.\n";  
        std::exit(EXIT_FAILURE);
    }
    
    A_.at(i*cols_+j) = value;
}


Tensor Tensor::row(size_t i) const
{
    if (i >= this->rows())
    {
        std::cerr << "FATAL ERROR: row index " << i << " out of bounds for Tensor with " << this->rows() << " rows.\n";
        std::exit(EXIT_FAILURE);
    }

    Tensor row(1,this->columns(),0.0);

    for (size_t j=0; j<this->columns(); j++)
        row.set(0,j,this->at(i,j));

    return row;
}


Tensor Tensor::column(size_t j) const 
{
    if (j >= this->columns())
    {
        std::cerr << "FATAL ERROR: column index " << j << " out of bounds for Tensor with " << this->columns() << " columns.\n";
        std::exit(EXIT_FAILURE);
    }

    Tensor column(this->rows(), 1, 0.0);

    for (size_t i=0; i<this->rows(); i++)
        column.set(i,0,this->at(i,j));

    return column;
}


Tensor& Tensor::operator=(const Tensor& rhs)
{
    if (this == &rhs)
        return *this;

    A_ = rhs.A_;
    rows_ = rhs.rows_;
    cols_ = rhs.cols_;

    return *this;
}


Tensor& Tensor::operator=(Tensor&& rhs) noexcept
{
    if (this == &rhs)   
        return *this;

    A_ = std::move(rhs.A_);
    rows_ = rhs.rows_;
    cols_ = rhs.cols_;

    rhs.rows_ = 0;
    rhs.cols_ = 0;

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
    
    #pragma omp parallel for
    for (size_t i=0; i<result.rows(); ++i)
    {
        for (size_t j=0; j<result.columns(); ++j)
        {
            for (size_t k=0; k < this->columns(); ++k)
            {
                result.A_.at(i*result.columns()+j) += this->at(i,k)*rhs.at(k,j);
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

    /*#pragma omp parallel for
    for (size_t i=0; i<this->rows(); ++i)
    {
        for (size_t j=0; j < this->columns(); ++j)
        {
            result.set(i,j,this->at(i,j)+rhs.at(i,j));
        }
    }*/
    size_t N = result.A_.size();
    #pragma omp parallel for 
    for (std::size_t i=0; i<N; ++i)
        result.A_[i] = this->A_[i] + rhs.A_[i];

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

    /*#pragma omp parallel for
    for (size_t i=0; i<this->rows(); ++i)
    {
        for (size_t j=0; j < this->columns(); ++j)
        {
            result.set(i,j,this->at(i,j)-rhs.at(i,j));
        }
    }*/

    size_t N = result.A_.size();
    #pragma omp parallel for 
    for (std::size_t i=0; i<N; ++i)
        result.A_[i] = this->A_[i] - rhs.A_[i];
    
    return result;
}


Tensor Tensor::operator+(double rhs) const 
{
    Tensor result(*this);
    size_t N = result.A_.size();
    #pragma omp parallel for 
    for (size_t i=0; i<N; ++i)
        result.A_[i] += rhs;

    return result; 
}


Tensor Tensor::operator-(double rhs) const 
{
    Tensor result(*this);

    return result+(-rhs); 
}


Tensor operator*(double lhs, const Tensor& rhs)
{
    Tensor result(rhs);
    size_t N = result.A_.size();
    #pragma omp parallel for 
    for (size_t i=0; i<N; ++i)
        result.A_[i] *= lhs;

    return result; 
}


Tensor& Tensor::operator+=(const Tensor& rhs)
{
    *this = *this + rhs; 
    
    return *this;
}


Tensor& Tensor::operator+=(double rhs)
{
    *this = *this + rhs;
    
    return *this;
}


Tensor& Tensor::operator-=(const Tensor& rhs)
{
    *this = *this - rhs;
    
    return *this;
}


Tensor& Tensor::operator-=(double rhs)
{
    *this = *this - rhs; 
    
    return *this;
}


Tensor& Tensor::operator*=(const Tensor& rhs)
{
    *this = *this * rhs;
    
    return *this;
}


Tensor& Tensor::operator*=(double rhs)
{
    *this = rhs * (*this);
    
    return *this;
}


Tensor Tensor::operator-() const 
{
    Tensor result(*this);
    size_t N = result.A_.size();
    
    #pragma omp parallel for 
    for (size_t i=0; i<N; ++i)
        result.A_[i] = -result.A_[i];

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

    size_t N = A_.size();
    #pragma omp parallel for reduction(+:result)
    for (size_t i=0; i<N; ++i)
        result += A_[i] * A_[i];

    return sqrt(result); 
}


void Tensor::transpose()
{
    Tensor T(columns(), rows(), 0.0);

    for (size_t i=0; i<this->rows(); ++i)
    {
        for (size_t j=0; j<this->columns(); ++j)
        {
            T.set(j,i,this->at(i,j));
        }
    }

    *this = std::move(T);
}


void Tensor::swap(Tensor& other) noexcept
{
    using std::swap;
    swap(A_, other.A_);
    swap(rows_, other.rows_);
    swap(cols_, other.cols_);
}

void swap(Tensor& T1, Tensor& T2) noexcept
{
    if (typeid(T1) != typeid(T2))
    {
        std::cerr << "FATAL ERROR: Attempted to swap '"
                  << typeid(T1).name() 
                  << "' and '"
                  << typeid(T2).name()
                  << "'.\n";
        std::exit(EXIT_FAILURE);
    }

    T1.swap(T2);
}

bool Tensor::is_symmetric(double tol) const 
{
    if (!is_square())
    {
        std::cout << "Cannot check symmetry of non-square tensors\n";
        return false;
    }

    for (size_t i=0; i<rows(); ++i)
    {
        for (size_t j=0; j<i; ++j)
        {
            if (std::abs(at(i,j) - at(j,i)) > tol)
            {
                return false; 
            }
        }
    }
    
    return true; 
}
