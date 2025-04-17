#ifndef VECTOR_H
#define VECTOR_H

#include "Tensor.h"

class Vector: public Tensor{
    public:
        Vector() {};
        Vector(int m, double value);
        Vector(const Tensor& other);
        const double& at(int ii) const;
        double& at(int ii);
        int size() const;
        double operator&(const Vector& rhs) const;  //dot product
};

#endif
