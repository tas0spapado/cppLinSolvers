#include <iostream>
#include <string>
#include "Tensor.h"
#include "Vector.h"
#include "Matrix.h"
#include "SparseMatrix.h"


void print(const std::string& msg)
{
    std::cout << "=====" << msg << "=====" << std::endl;
}

int main()
{
    print("Swap Test");

    std::cout << '\n';

    print("Tensors");
    Tensor T1 = {{1,2,3}};
    Tensor T2 = {{4,4,4}};
    T2.transpose();
    std::cout << "\nInitial Tensors:\n\n";
    T1.print();
    T2.print();

    swap(T1,T2);
    std::cout << "Tensors after swap:\n\n";
    T1.print();
    T2.print();
   
    ////////////////////////////////////////

    std::cout << '\n';

    print("Vectors");
    Vector V1 = {1,2,3};
    Vector V2 = {3,2,4};
    V2.transpose();
    std::cout << "\nInitial Vectors:\n\n";
    V1.print();
    V2.print();

    //swap(static_cast<Tensor&>(V1),static_cast<Tensor&>(V2));
    swap(V1,V2);
    std::cout << "Vectors after swap:\n\n";
    V1.print();
    V2.print();
   
    ////////////////////////////////////////

    std::cout << '\n';

    print("Matrices");
    Matrix M1 = {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };
    Matrix M2 = {
        {1,1},
        {2,2}
    };
    std::cout << "\nInitial Matrices:\n\n";
    M1.print();
    M2.print();

    swap(M1,M2);
    std::cout << "Matrices after swap:\n\n";
    M1.print();
    M2.print();
   
    ////////////////////////////////////////

    std::cout << '\n';

    print("Sparse Matrices");
    SparseMatrix SM1 = {
        {1,2,0},
        {0,0,0},
        {0,8,0}
    };
    SparseMatrix SM2 = {
        {1,0},
        {0,2}
    };
    std::cout << "\nInitial Sparse Matrices:\n\n";
    SM1.print_sparse();
    SM2.print_sparse();

    swap(SM1,SM2);
    std::cout << "Sparse Matrices after swap:\n\n";
    SM1.print_sparse();
    SM2.print_sparse();

    






    return 0;

}

