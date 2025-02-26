#include "matrix.hpp"
#include "matrix_chain.hpp"
#include <cmath>
#include <gtest/gtest.h>
#include <string>

TEST(MatrixChainTest, Test1) {
    matrix::Matrix<int> mat1(30, 35);
    matrix::Matrix<int> mat2(35, 15);
    matrix::Matrix<int> mat3(15, 5);
    matrix::Matrix<int> mat4(5, 10);

    matrix_chain::Chain<int> chain;
    chain.Push(mat1);
    chain.Push(mat2);
    chain.Push(mat3);
    chain.Push(mat4);

    auto optim = chain.GetOptimalMultiplyCountOrder();
    int optim_count = optim.first;
    std::vector<int> order = optim.second;
    int count = chain.GetMultiplyCount();

    std::vector<int> right_order{1, 0, 2};

    ASSERT_EQ(optim_count, 9375);
    ASSERT_EQ(count, 19500);
    ASSERT_EQ(order, right_order);
}

TEST(MatrixChainTest, Test2) {
    matrix::Matrix<int> mat1(10, 30);
    matrix::Matrix<int> mat2(30, 5);
    matrix::Matrix<int> mat3(5, 60);

    matrix_chain::Chain<int> chain;
    chain.Push(mat1);
    chain.Push(mat2);
    chain.Push(mat3);

    auto optim = chain.GetOptimalMultiplyCountOrder();
    int optim_count = optim.first;
    std::vector<int> order = optim.second;
    int count = chain.GetMultiplyCount();

    std::vector<int> right_order{0, 1};

    ASSERT_EQ(optim_count, 4500);
    ASSERT_EQ(count, 4500);
    ASSERT_EQ(order, right_order);
}