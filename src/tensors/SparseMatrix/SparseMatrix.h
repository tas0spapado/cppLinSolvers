#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

#include "Tensor.h"
#include <cstddef>
#include <vector>


class SparseMatrix: public Tensor{
    std::vector<size_t> col_index_;     //vector storing the column numbers of non-zero entries
    std::vector<size_t> row_ptr_;       //row pointers
                                        //size = number or rows + 1
                                        //row_ptr_[0] = 0 always
                                        //row_ptr_.back() = the total number of non-zero entries
                                        //row_ptr_[i+1] = the number of non-zero entries up to row i

    public:
        static constexpr double zero_value = 0.0;

        /* Constructors */
        SparseMatrix(size_t m);
        SparseMatrix(const std::initializer_list<std::initializer_list<double>>& init);
        SparseMatrix(const Tensor& other);
        //move constructor

        //copy assignment
        //copy constructor

        const double& at(size_t i, size_t j) const override;
        void set(size_t i, size_t j, double value) override;
        void transpose() override;
        void print_sparse() const;
        void swap(Tensor& other) noexcept override;

        inline size_t non_zero() const {return row_ptr_.back();}
};


#endif
