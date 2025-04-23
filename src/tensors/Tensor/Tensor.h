#ifndef TENSOR_H
#define TENSOR_H

#include <vector>
#include <initializer_list>
#include <cstddef>

using std::size_t;

class Tensor
{
    protected:
        size_t storage_rows;                    //storage i dimension
        size_t storage_cols;                    //storage j dimension
        std::vector<std::vector<double>> A;     //the container to store the tensor entries
        size_t n_rows;                          //number of rows
        size_t n_cols;                          //numer of columns
        virtual void initialize();
    public:
        /* Constructors & Destructors */
        Tensor();
        Tensor(size_t m, size_t n, double value);                           //constructor for uniform value
        Tensor(std::initializer_list<std::initializer_list<double>> init);  //initializer list constructor
        Tensor(const Tensor& other);
        Tensor(Tensor&& other) noexcept;
        virtual ~Tensor() = default;

        /* Accessors */
        virtual const double& at(size_t i, size_t j) const;     //return A(i,j), overriden in derived classes
        virtual double& at(size_t i, size_t j);
        Tensor extract_row(size_t i) const;                     //return row i
        Tensor extract_column(size_t j) const;                  //return column j

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

        /* Tensor Handling */
        void print() const;
        double norm() const;        //computes the norm2 of the tensor
        virtual void transpose();

        /* Inline Functions */
        inline double& operator()(size_t i, size_t j) {return this->at(i,j);}
        inline const double& operator()(size_t i, size_t j) const {return this->at(i,j);}
        inline size_t istorage() const {return storage_rows;}
        inline size_t jstorage() const {return storage_cols;}
        inline size_t rows() const {return n_rows;}
        inline size_t columns() const {return n_cols;}
};

#endif
