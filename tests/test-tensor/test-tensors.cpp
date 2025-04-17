#include "Tensor.h"
#include <iostream>

int main()
{

    std::cout << "Testing class Tensor\n" << "====================================\n";
    Tensor T1(1,3,1.0);
    Tensor T2(3,1,2.0);
    T1.print();
    T2.print();

    Tensor T3 = T1*T2;
    T3.print();

    T1.transpose();
    T1.print();

    Tensor T4 = T1 + T2; 
    T4.print();

    std::cout << "Norm of T1: " << T1.norm() << '\n';
    std::cout << "Norm of T2: " << T2.norm() << '\n';
    std::cout << "Norm of T3: " << T3.norm() << '\n';

    return 0;
}
