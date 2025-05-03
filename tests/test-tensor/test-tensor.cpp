#include "Tensor.h"
#include <iostream>
#include <string>

void print(const std::string& msg)
{
    std::cout << "=====" << msg << "=====" << std::endl;
}

int main()
{
    print("Tensor Test");

    /*print("Testing Default Constructor");
    Tensor T1;
    T1.print();*/
   
    print("Testing Uniform Constructor");
    Tensor T2(2,3,1.0);
    T2.print();

    print("Testing Initializer List Constructor");
    Tensor T3({
            {1,2,3},
            {4,5,6}
            });
    T3.print();
    
    print("Testing Addition");
    Tensor T4 = T2 + T3;
    T4.print();

    print("Testing Subtraction");
    T4 = T2 - T3;
    T4.print();

    print("Testing Multiplication");
    T4 = Tensor({{1,0,0}, {0,1,0}, {0,0,1}})*Tensor({{1,2,3}, {4,5,6}, {7,8,9}});
    T4.print(); 

    print("Testing Transpose");
    T3.transpose();
    T3.print();

    print("Testing Other Functions");
    Tensor T5 = {{3,4}};
    T5.print();
    std::cout << "Norm: " << T5.norm() << std::endl;
    std::cout << "Rows: " << T5.rows() << std::endl;
    std::cout << "Columns: " << T5.columns() << std::endl;
    std::cout << std::endl; 

    print("Testing Column and Row Getters");
    T4.print();
    std::cout << "2nd row: \n";
    Tensor T1 = T4.row(1);
    T1.print();
    std::cout << "2nd column: \n";
    T1 = T4.column(1);
    T1.print();

    print("Testing Addition of Double");
    T4.print();
    Tensor T6 = T4 + 1.0;
    T6.print();

    print("Testing Subtraction of Double");
    T4.print();
    Tensor T7 = T4 - 1.0;
    T7.print();

    print("Testing Multiplication with Double");
    T4.print();
    Tensor T8 = 2.0*T4;
    T8.print();

    print("Testing Return std::vector");
    const std::vector<double>& A = T4.A();
    for (const double& val : A)
        std::cout << val << " ";
    std::cout << '\n';

    return 0;
}
