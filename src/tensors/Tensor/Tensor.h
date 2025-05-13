#ifndef TENSOR_H
#define TENSOR_H

#include <vector>
#include <initializer_list>
#include <cstddef>

using std::size_t;

class Tensor
{
    protected:
        std::vector<double> A_;  //the container to store the tensor entries
        size_t rows_;           //number of rows
        size_t cols_;           //numer of columns
    public:
        static Tensor eye(size_t m);   //returns identity tensor

        /* Constructors & Destructors */
        Tensor();
        Tensor(size_t m, size_t n, double value);                           //constructor for uniform value
        Tensor(const std::initializer_list<std::initializer_list<double>>& init);  //initializer list constructor
        Tensor(const Tensor& other);
        Tensor(Tensor&& other) noexcept;
        virtual ~Tensor() = default;

        /* Accessors */
        virtual const double& at(size_t i, size_t j) const;     //return A(i,j), overriden in derived classes
        virtual void  set(size_t i, size_t j, double value);
        Tensor row(size_t i) const;                     //return row i
        Tensor column(size_t j) const;                  //return column j

        /* Operators */
        Tensor& operator=(const Tensor& rhs);
        Tensor& operator=(Tensor&& rhs) noexcept;
        Tensor operator*(const Tensor& rhs) const;
        Tensor operator+(const Tensor& rhs) const;
        Tensor operator-(const Tensor& rhs) const;
        Tensor operator+(double rhs) const;
        Tensor operator-(double rhs) const;
        friend Tensor operator*(double lhs, const Tensor& rhs);
        Tensor& operator+=(const Tensor& rhs);
        Tensor& operator+=(double rhs);
        Tensor& operator-=(const Tensor& rhs);
        Tensor& operator-=(double rhs);
        Tensor& operator*=(const Tensor& rhs);
        Tensor& operator*=(double rhs);
        Tensor operator-() const;

        /* Utilities */
        void print() const;
        double norm() const;        //computes the norm2 of the tensor
        virtual void transpose();
        virtual void swap(Tensor& other) noexcept;
        friend void swap(Tensor& T1, Tensor& T2) noexcept;

        /* Inline Functions */
        inline const double& operator()(size_t i, size_t j) const {return this->at(i,j);}
        inline size_t rows() const {return rows_;}
        inline size_t columns() const {return cols_;}
        inline bool is_square() const {return (this->rows() == this->columns());}
        inline const std::vector<double>& A() const {return A_;}
        inline std::vector<double>& A() {return A_;}
};

#endif
