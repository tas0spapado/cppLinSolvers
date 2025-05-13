#include "SparseMatrix.h"
#include "Tensor.h"
#include <cstddef>
#include <iostream>

SparseMatrix::SparseMatrix(size_t m):
Tensor(),
col_index_(),
row_ptr_(m+1,0)
{
    rows_ = m;
    cols_ = m;
}


SparseMatrix::SparseMatrix(const std::initializer_list<std::initializer_list<double>>& init):
Tensor(),
col_index_(),
row_ptr_(init.size()+1, 0)
{
    if (init.size() == 0)
    {
        std::cerr << "FATAL ERROR: Initializer list for Tensor is empty.\n";
        std::exit(EXIT_FAILURE);
    }
    
    size_t i = 0;
    size_t j = 0;
    
    rows_ = init.size();
    cols_ = init.begin()->size();

    if (this->rows() != this->columns())
    {
        std::cerr << "FATAL ERROR: Attempt to create non-square SparseMatrix.\n";
        std::exit(EXIT_FAILURE);
    }
    
    for (const auto& row: init)
    {
        if (row.size() != cols_)
        {
            std::cerr << "FATAL ERROR: Inconsistent row sizes in initializer list.\n";
            std::exit(EXIT_FAILURE);
        }
        
        for (const double& value: row)
        {
            if (value != 0.0)
                this->set(i,j,value);
            ++j;
        }
        ++i;
        j=0;
    }
}


SparseMatrix::SparseMatrix(const Tensor& other):
Tensor(),
col_index_(),
row_ptr_(other.rows()+1)
{
    rows_ = other.rows();
    cols_ = other.columns();
    
    if (this->rows() != this->columns())
    {
        std::cerr << "FATAL ERROR: Attempt to create non-square SparseMatrix.\n";
        std::exit(EXIT_FAILURE);
    }
    
    for (size_t i=0; i<rows_; ++i)
    {
        for (size_t j=0; j<cols_; ++j)
        {
            if (other.at(i,j) != 0.0)
                this->set(i,j,other.at(i,j));
        }
    }
}


const double& SparseMatrix::at(size_t i, size_t j) const
{
    if (i>=this->rows() || j>=this->columns())                                                                                                                                                                                                          
    {                                                                                                                    
        std::cerr << "FATAL ERROR: Attempted to access element (" << i << "," << j << ") of a "                          
            << rows_ << "x" << cols_ << "tensor.\n";                                                                     
        std::exit(EXIT_FAILURE);                                                                                         
    } 

    size_t k_start = row_ptr_.at(i);
    size_t k_end = row_ptr_.at(i+1);
    
    for (auto it = col_index_.begin() + k_start ; it != col_index_.begin() + k_end ; ++it)
    {
        if (*it == j)
        {
            std::size_t k = std::distance(col_index_.begin(), it);
            return A_.at(k);
        }
    }
    return zero_value;
}


void SparseMatrix::set(size_t i, size_t j, double value)
{
    if (value == 0.0) return;

    if (i>=this->rows() || j>=this->columns())                                                                                                                                                                                                          
    {                                                                                                                    
        std::cerr << "FATAL ERROR: Attempted to insert or modify element (" << i << "," << j << ") of a "                          
            << rows_ << "x" << cols_ << " tensor.\n";                                                                     
        std::exit(EXIT_FAILURE);                                                                                         
    } 
   
    std::size_t k_start = row_ptr_.at(i);
    std::size_t k_end = row_ptr_.at(i+1);

    for (auto it = col_index_.begin() + k_start ; it != col_index_.begin() + k_end ; ++it)
    {
        if (*it == j)
        {
            std::size_t k = std::distance(col_index_.begin(), it);
            A_.at(k) = value;
            return;
        }
    }

    auto it_insert = col_index_.begin() + k_start;
    auto it_end = col_index_.begin() + k_end;
    while (it_insert!=it_end && *it_insert<j)
        ++it_insert;
    
    std::size_t insert_index = std::distance(col_index_.begin(), it_insert);
    col_index_.insert(it_insert, j);
    A_.insert(A_.begin() + insert_index, value);
    for (std::size_t ii = i + 1; ii < row_ptr_.size(); ++ii)
        ++row_ptr_.at(ii);
}


void SparseMatrix::transpose()
{
    SparseMatrix T(this->rows());
    
    for (size_t i=0; i<T.rows(); ++i)
    {
        for (size_t j=0; j<T.columns(); ++j)
        {
            T.set(i,j,this->at(j,i)); 
        }
    }

    *this = std::move(T);
}


void SparseMatrix::print_sparse() const 
{
    std::cout << "Non-zero elements:\n";
    for (const double& value: A_)
        std::cout << value << " ";
    std::cout << '\n';

    std::cout << "Column index vector:\n";
    for (size_t index: col_index_)
        std::cout << index << " ";
    std::cout << '\n';

    std::cout << "Row pointer vector:\n";
    for (size_t rowptr: row_ptr_)
        std::cout << rowptr << " ";
    std::cout << '\n';
}


void SparseMatrix::swap(Tensor& other) noexcept
{
    auto& oth = static_cast<SparseMatrix&>(other);
    Tensor::swap(other);
    
    std::swap(col_index_, oth.col_index_);
    std::swap(row_ptr_, oth.row_ptr_);
}




