#ifndef TENSOR_H
#define TENSOR_H

#include <vector>

class Tensor{
    void initialize();
    protected:
        int M;          //i span
        int N;          //j span
        std::vector<std::vector<double>> A;
        int order;      //order of the tensor
    public:
        Tensor();                           //default constructor
        Tensor(int m, int n, double value); //constructor for uniform value
        Tensor(const Tensor& other);        //copy constructor
        Tensor(Tensor&& other);             //move constructor
        ~Tensor() = default;
        Tensor& operator=(const Tensor& rhs);   //copy assignement operator
        Tensor& operator=(Tensor&& rhs);        //move assignement operator
        Tensor operator*(const Tensor& rhs) const;
        Tensor operator+(const Tensor& rhs) const;
        Tensor operator-(const Tensor& rhs) const;
        const double& at(int ii, int jj) const;
        double& at(int ii, int jj);
        void print() const;
        double norm() const;
        void transpose();
        /* inline member functions */
        inline int getOrder() const {return order;}
};

#endif
