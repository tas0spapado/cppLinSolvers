#ifndef MATRIX_H
#define MATRIX_H

/*
 * Square matrix with full storage
 */


#include "Tensor.h"
#include <cstddef>

class Matrix: public Tensor{
    public:
        /* Constructors */
        Matrix() = default;
        Matrix(size_t m, double value);     //constructor for uniform value
        Matrix(std::initializer_list<std::initializer_list<double>> init);  //initializer list constructor
        Matrix(const Tensor& other);
};

#endif
