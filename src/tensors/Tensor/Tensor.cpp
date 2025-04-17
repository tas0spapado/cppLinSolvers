#include "Tensor.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

void Tensor::initialize()
{
    if(M==1 && N==1)
        order = 0;
    else if ((M>1 && N==1) || (M==1 && N>1))
        order =1; 
    else 
        order =2;
}

Tensor::Tensor(): 
M(1), 
N(1), 
A(1,std::vector<double>(1,0.0)) 
{
    initialize();
}

Tensor::Tensor(int m, int n, double value): 
M(m), 
N(n), 
A(m,std::vector<double>(n,value)) 
{
    initialize();
}

Tensor::Tensor(const Tensor& other):
M(other.M),
N(other.N),
A(other.A),
order(other.order)
{}

Tensor::Tensor(Tensor&& other):
M(other.M),
N(other.N),
A(std::move(other.A)),
order(other.order)
{
    other.M = 0;
    other.N = 0;
    other.order = 0; 
}

Tensor& Tensor::operator=(const Tensor& rhs)
{
    if (this == &rhs)
        return *this;
    
    M = rhs.M;
    N = rhs.N;
    A = rhs.A;
    order = rhs.order;

    return *this;
}

Tensor& Tensor::operator=(Tensor&& rhs)
{
    if (this == &rhs)
        return *this;
    
    M = rhs.M;
    N = rhs.N;
    A = std::move(rhs.A);
    order = rhs.order;
    
    rhs.M = 0;
    rhs.N = 0;
    rhs.order =0;

    return *this;
}

Tensor Tensor::operator*(const Tensor& rhs) const
{
    if (N!=rhs.M)
    {
        std::cerr << "FATAL ERROR: tensor dimension mismatch in opeator*\n";
        std::exit(EXIT_FAILURE);
    }

    Tensor Tnew(M, rhs.N, 0.0);
    
    for (int i=0; i<this->M; ++i)
    {
        for (int j=0; j<rhs.N; ++j)
        {
            for (int k=0; k<this->N; ++k)
                Tnew.at(i,j) += this->at(i,k)*rhs.at(k,j);  
        }
    }

    return Tnew; 
}

Tensor Tensor::operator+(const Tensor& rhs) const
{
    if ((M!=rhs.M) || (N!=rhs.N))
    {
        std::cerr << "FATAL ERROR: tensor dimension mismatch in opeator+\n";
        std::exit(EXIT_FAILURE);
    }

    Tensor Tnew(M, N, 0.0);
    
    for (int i=0; i<M; ++i)
        for (int j=0; j<N; ++j)
            Tnew.at(i,j) = this->at(i,j) + rhs.at(i,j);

    return Tnew; 
}

Tensor Tensor::operator-(const Tensor& rhs) const
{
    Tensor Tnew(M, N, 0.0);
    if ((M!=rhs.M) || (N!=rhs.N))
    {
        std::cerr << "FATAL ERROR: tensor dimension mismatch in opeator-\n";
        std::exit(EXIT_FAILURE);
    }

    for (int i=0; i<M; ++i)
        for (int j=0; j<N; ++j)
            Tnew.at(i,j) = this->at(i,j) - rhs.at(i,j);

    return Tnew; 
}

const double& Tensor::at(int ii, int jj) const 
{
    return A.at(ii).at(jj);
}

double& Tensor::at(int ii, int jj) 
{
    return A.at(ii).at(jj);
}

void Tensor::print() const 
{
    for (const auto& row: A)
    {
        for (const double& val: row)
            std::cout << val << " ";
        std::cout << '\n';
    }
    std::cout << '\n';
}

double Tensor::norm() const 
{
    double n2 = 0.0;
    for (const auto& row: A)
        for (const double& val: row)
            n2 += pow(val,2);
    n2 = sqrt(n2);
    return n2;
}

void Tensor::transpose()
{
    Tensor Tt(N, M, 0.0);
    
    for (int i=0; i<N; ++i)
        for (int j=0; j<M; ++j)
            Tt.at(i,j) = this->at(j,i);

    *this = Tt; 
}
