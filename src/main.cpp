#include "matrix_chain.hpp"
#include "matrix.hpp"

int main() {
    matrix_chain::Chain<int> chain;
    matrix::Matrix<int> mat1{10, 20};
    matrix::Matrix<int> mat2{20, 30};
    matrix::Matrix<int> mat3{30, 40};
    matrix::Matrix<int> mat4{40, 5};

    chain.Push(mat1);
    chain.Push(mat2);
    chain.Push(mat3);
    chain.Push(mat4);

    std::cout << chain.GetOptimalMultiplyCount() << std::endl;
    std::cout << chain.GetMultiplyCount() << std::endl;

    matrix_chain::Chain<int> chain1;
    matrix::Matrix<int> mat5{10, 30};
    matrix::Matrix<int> mat6{30, 5};
    matrix::Matrix<int> mat7{5, 60};

    chain1.Push(mat5);
    chain1.Push(mat6);
    chain1.Push(mat7);

    std::cout << chain1.GetOptimalMultiplyCount() << std::endl;
    std::cout << chain1.GetMultiplyCount() << std::endl;

    matrix_chain::Chain<int> chain2;
    matrix::Matrix<int> mat8{30, 35};
    matrix::Matrix<int> mat9{35, 15};
    matrix::Matrix<int> mat10{15, 5};
    matrix::Matrix<int> mat11{5, 10};

    chain2.Push(mat8);
    chain2.Push(mat9);
    chain2.Push(mat10);
    chain2.Push(mat11);

    std::cout << chain2.GetOptimalMultiplyCount() << std::endl;
    std::cout << chain2.GetMultiplyCount() << std::endl;
}