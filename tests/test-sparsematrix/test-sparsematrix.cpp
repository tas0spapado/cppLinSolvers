#include "SparseMatrix.h"
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
    print("SparseMatrix Test");
    
    SparseMatrix S1(5);
    std::cout << "Rows: " << S1.rows() << std::endl;
    std::cout << "Columns: " << S1.columns() << std::endl;
    std::cout << "Square: " << S1.is_square() << std::endl;
    S1.print();

    
    print("Initializer List Constructor");
    SparseMatrix S2 = {
        {0, 5.0, 0, 0},
        {1.1, 0, 2.2, 0},
        {0, 0, 0, 3.3},
        {4.4, 0, 0, 0}
    };
    S2.print();
    S2.print_sparse();


    print("Construct from Tensor");
    SparseMatrix S3(Tensor::eye(9));
    S3.print();
    S3.print_sparse();
    std::cout << "Norm2 = " << S3.norm() << std::endl;

    
    print("SparseMatrix Transpose");
    SparseMatrix S4 = {
        {1,2,3,4},
        {0,0,0,0},
        {0,0,0,0},
        {0,0,0,0}
    };
    S4.transpose();
    S4.print();
    S4.print_sparse();
    std::cout << "Adding a non-zero element.\n";
    S4.set(3,3,5);
    S4.print();
    S4.print_sparse();
    std::cout << "Non-zero elements: " << S4.non_zero() << '\n';


    return 0;
}
