#include "Vector.h"
#include <iostream>

int main()
{

    std::cout << "Testing class Vector\n" << "====================================\n";

    std::cout << "\nVector V1\n====================================\n";
    Vector V1(3,1.0);
    V1.print();
    std::cout << "Order: " << V1.getOrder() << std::endl;
    std::cout << "Norm: " << V1.norm() << std::endl;
    V1.transpose();
    V1.print();

    std::cout << "\nVector V2\n====================================\n";
    Vector V2(3,2.0);
    V2.print(); 

    std::cout << "\nVector V3\n====================================\n";
    V1.transpose();
    Vector V3 = V1 + V2; 
    V3.print();

    double dot_product = V1&V3;
    std:: cout << "Dot Product V1*V3 = " << dot_product << std::endl;



    return 0;
}
