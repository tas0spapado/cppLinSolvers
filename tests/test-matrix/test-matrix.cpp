#include "Matrix.h"
#include "Tensor.h"
#include <iostream>
#include <string>

void print(const std::string& msg)
{
    std::cout << "=====" << msg << "=====" << std::endl;
}

int main()
{

    print("Matrix Test");
    
    print("Test Uniform Constructor");
    Matrix M1(4,1);
    M1.print();

    print("Test Construction from Tensor");
    Matrix M2(Tensor::eye(3));
    M2.print();

    return 0;
}
