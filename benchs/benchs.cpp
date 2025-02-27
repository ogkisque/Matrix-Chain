#include <cassert>
#include <iostream>
#include <vector>
#include <ctime>
#include <vector>
#include <random>
#include <algorithm>

#include "hayai.hpp"
#include "hayai_main.hpp"
#include "matrix_chain.hpp"

matrix_chain::Chain<int> chain;
std::vector<int> optim_order;
std::vector<int> naive_order;

BENCHMARK(MatrixMultiply, Optimal, 1, 10) {
    auto mat = chain.DoMultiply(optim_order);
}

BENCHMARK(MatrixMultiply, Naive, 1, 10) {
    auto mat = chain.DoMultiply(naive_order);
}

int main() {
    matrix::Matrix<int> mat1{100, 1};
    for (size_t i = 0; i < 100; ++i)
        for (size_t j = 0; j < 1; ++j)
            mat1[i][j] = 1;

    matrix::Matrix<int> mat2{1, 100};
    for (size_t i = 0; i < 1; ++i)
        for (size_t j = 0; j < 100; ++j)
            mat2[i][j] = 5;

    matrix::Matrix<int> mat3{100, 5};
    for (size_t i = 0; i < 100; ++i)
        for (size_t j = 0; j < 5; ++j)
            mat3[i][j] = 5;
    
    matrix::Matrix<int> mat4{5, 200};
    for (size_t i = 0; i < 5; ++i)
        for (size_t j = 0; j < 200; ++j)
            mat4[i][j] = 10;
    
    matrix::Matrix<int> mat5{200, 50};
    for (size_t i = 0; i < 200; ++i)
        for (size_t j = 0; j < 50; ++j)
            mat5[i][j] = 3;
    
    matrix::Matrix<int> mat6{50, 300};
    for (size_t i = 0; i < 50; ++i)
        for (size_t j = 0; j < 300; ++j)
            mat6[i][j] = 5;

    matrix::Matrix<int> mat7{300, 1};
    for (size_t i = 0; i < 300; ++i)
        for (size_t j = 0; j < 1; ++j)
            mat7[i][j] = 11;
    
    matrix::Matrix<int> mat8{1, 700};
    for (size_t i = 0; i < 1; ++i)
        for (size_t j = 0; j < 700; ++j)
            mat8[i][j] = 23;
    
    matrix::Matrix<int> mat9{700, 100};
    for (size_t i = 0; i < 700; ++i)
        for (size_t j = 0; j < 100; ++j)
            mat9[i][j] = 13;

    matrix::Matrix<int> mat10{100, 1000};
    for (size_t i = 0; i < 100; ++i)
        for (size_t j = 0; j < 1000; ++j)
            mat10[i][j] = -19;

    matrix::Matrix<int> mat11{1000, 20};
    for (size_t i = 0; i < 1000; ++i)
        for (size_t j = 0; j < 20; ++j)
            mat11[i][j] = 1;

    matrix::Matrix<int> mat12{20, 500};
    for (size_t i = 0; i < 20; ++i)
        for (size_t j = 0; j < 500; ++j)
            mat12[i][j] = 7;

    matrix::Matrix<int> mat13{500, 500};
    for (size_t i = 0; i < 500; ++i)
        for (size_t j = 0; j < 500; ++j)
            mat13[i][j] = 6;

    matrix::Matrix<int> mat14{500, 600};
    for (size_t i = 0; i < 500; ++i)
        for (size_t j = 0; j < 600; ++j)
            mat14[i][j] = -9;

    matrix::Matrix<int> mat15{600, 10};
    for (size_t i = 0; i < 600; ++i)
        for (size_t j = 0; j < 10; ++j)
            mat15[i][j] = 13;

    chain.Push(mat1);
    chain.Push(mat2);
    chain.Push(mat3);
    chain.Push(mat4);
    chain.Push(mat5);
    chain.Push(mat6);
    chain.Push(mat7);
    chain.Push(mat8);
    chain.Push(mat9);
    chain.Push(mat10);
    chain.Push(mat11);
    chain.Push(mat12);
    chain.Push(mat13);
    chain.Push(mat14);
    chain.Push(mat15);

    auto optim = chain.GetOptimalMultiplyCountOrder();
    optim_order = optim.second;
    naive_order = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

    hayai::MainRunner runner;
    return runner.Run();
}