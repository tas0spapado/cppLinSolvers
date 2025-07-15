#include "Matrix.h"
#include "Tensor.h"
#include <iostream>
#include <string>
#include "openmp_settings.h"

void print(const std::string& msg)
{
    std::cout << "=====" << msg << "=====" << std::endl;
}

int main()
{
    openmp_settings::set_num_threads(1);
    
    print("Matrix Test");
    
    print("Test Uniform Constructor");
    Matrix M1(4,1);
    M1.print();

    print("Test Construction from Tensor");
    Matrix M2(Tensor::eye(3));
    M2.print();

    return 0;
}
