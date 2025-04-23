#ifndef VECTOR_H
#define VECTOR_H

#include "Tensor.h"
#include <cstddef>
#include <initializer_list>

class Vector: public Tensor{
    public:
        /* Constructors */
        Vector() {}
        Vector(size_t m, double value);             //constructor for uniform value
        Vector(std::initializer_list<double> init); //initializer_list constructor
        Vector(const Tensor& other);                //construct from Tensor - no actual slicing

        size_t size() const;

        /* Operators */
        double& operator[](size_t i);
        const double& operator[](size_t i) const;
        double operator&(const Vector& rhs) const;  //dot product

};

#endif
