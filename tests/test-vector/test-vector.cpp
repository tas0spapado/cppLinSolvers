#include "Vector.h"
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
    print("Vector Test");

    /*print("Test Default Constructor");
    Vector V1; 
    V1.print();*/


    print("Test Uniform Constructor");
    Vector V2(5,1.0);
    V2.print();

    print("Test Initializer List Constructor");
    Vector V3{1,2,3,4,5};
    V3.print();
    
    print("Test operator+=(const Tensor& rhs)");
    V3 += V2; 
    V3.print();

    print("Test operator+=(double rhs)");
    V3 += 10;
    V3.print();  

    print("Test Dot Product");
    Vector V4 = {1,2,3};
    Vector V5(3,1);
    V4.print();
    V5.transpose();
    V5.print();
    std::cout << "dot product = " << (V4&V5) << "\n\n";

    print("Test operator-");
    Vector V6 = {1,2,3};
    V6.print();
    V6 = -V6; 
    V6.print();

    return 0;
}
