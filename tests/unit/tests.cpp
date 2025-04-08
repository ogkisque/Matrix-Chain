#include "matrix.hpp"
#include "matrix_chain.hpp"
#include <cmath>
#include <gtest/gtest.h>
#include <string>
#include <iostream>

TEST(MatrixChainTest, MultiplyOrder1) {
    matrix::Matrix<int> mat1(30, 35);
    matrix::Matrix<int> mat2(35, 15);
    matrix::Matrix<int> mat3(15, 5);
    matrix::Matrix<int> mat4(5, 10);

    matrix_chain::Chain<int> chain;

    chain.Push(mat1);
    chain.Push(mat2);
    chain.Push(mat3);
    chain.Push(mat4);

    auto count_order_opt = chain.GetOptimalMultiplyCountOrder();
    size_t count = chain.GetMultiplyCount();
    auto optim_count = count_order_opt.num_operations;
    auto&& order = count_order_opt.order;

    std::vector<size_t> right_order {1, 0, 2};

    ASSERT_EQ(optim_count, 9375);
    ASSERT_EQ(count, 19500);
    ASSERT_EQ(order, right_order);
}

TEST(MatrixChainTest, MultiplyOrder2) {
    matrix::Matrix<int> mat1(10, 30);
    matrix::Matrix<int> mat2(30, 5);
    matrix::Matrix<int> mat3(5, 60);

    matrix_chain::Chain<int> chain;
    chain.Push(mat1);
    chain.Push(mat2);
    chain.Push(mat3);

    auto count_order_opt = chain.GetOptimalMultiplyCountOrder();
    size_t count = chain.GetMultiplyCount();
    auto optim_count = count_order_opt.num_operations;
    auto&& order = count_order_opt.order;

    std::vector<size_t> right_order {0, 1};

    ASSERT_EQ(optim_count, 4500);
    ASSERT_EQ(count, 4500);
    ASSERT_EQ(order, right_order);
}

TEST(MatrixChainTest, Multiply1) {
    std::vector<int> v1 {1, 2, 1, 0, -2, 1, 2, -1};
    std::vector<int> v2 {1, 0, -1, 0, 2, 0, 3, -3};
    std::vector<int> v3 {1, 2, 1, 3, -2, 0, -3, 3, 1, -2, 0, 4, 1, 2, 0, -1};
    std::vector<int> result {4, -12, 5, 41, 0, 4, 1, -1, 2, -16, 0, 23, -2, 16, 0, -23};

    matrix::Matrix<int> mat1(4, 2, v1.begin(), v1.end());
    matrix::Matrix<int> mat2(2, 4, v2.begin(), v2.end());
    matrix::Matrix<int> mat3(4, 4, v3.begin(), v3.end());

    matrix_chain::Chain<int> chain;
    chain.Push(mat1);
    chain.Push(mat2);
    chain.Push(mat3);

    auto count_order_opt = chain.GetOptimalMultiplyCountOrder();
    auto optim_count = count_order_opt.num_operations;
    auto&& order = count_order_opt.order;
    
    std::vector<size_t> naive_order = {0, 1};
    auto &&matrix1 = matrix_chain::DoMultiply(chain.begin(), chain.end(), naive_order);
    auto &&matrix2 = matrix_chain::DoMultiply(chain.begin(), chain.end(), order);

    ASSERT_EQ(matrix1, matrix2);
    for (size_t i = 0; i < 4; ++i)
        for (size_t j = 0; j < 4; ++j)
            ASSERT_EQ(result[i * 4 + j], matrix1[i][j]);
}

TEST(MatrixChainTest, Multiply2) {
    matrix::Matrix<int> mat1(100, 1);
    matrix::Matrix<int> mat2(1, 100);
    matrix::Matrix<int> mat3(100, 1000);
    matrix::Matrix<int> mat4(1000, 1);

    matrix_chain::Chain<int> chain;
    chain.Push(mat1);
    chain.Push(mat2);
    chain.Push(mat3);
    chain.Push(mat4);

    auto count_order_opt = chain.GetOptimalMultiplyCountOrder();
    auto optim_count = count_order_opt.num_operations;
    auto&& order = count_order_opt.order;

    std::vector<size_t> naive_order = {0, 1, 2};
    auto &&matrix1 = matrix_chain::DoMultiply(chain.begin(), chain.end(), naive_order);
    auto &&matrix2 = matrix_chain::DoMultiply(chain.begin(), chain.end(), order);

    ASSERT_EQ(matrix1, matrix2);
}

TEST(MatrixChainTest, Multiply3) {
    matrix::Matrix<int> mat1(100, 2);
    matrix::Matrix<int> mat2(2, 100);
    matrix::Matrix<int> mat3(100, 1000);
    matrix::Matrix<int> mat4(1000, 10000);
    matrix::Matrix<int> mat5(10000, 11);

    for (size_t i = 0; i < 100; ++i)
        for (size_t j = 0; j < 2; ++j)
            mat1[i][j] = 1;

    for (size_t i = 0; i < 2; ++i)
        for (size_t j = 0; j < 100; ++j)
            mat2[i][j] = 2;

    for (size_t i = 0; i < 100; ++i)
        for (size_t j = 0; j < 1000; ++j)
            mat3[i][j] = 3;

    for (size_t i = 0; i < 1000; ++i)
        for (size_t j = 0; j < 10000; ++j)
            mat4[i][j] = 2;

    for (size_t i = 0; i < 10000; ++i)
        for (size_t j = 0; j < 11; ++j)
            mat5[i][j] = 3;

    matrix_chain::Chain<int> chain;
    chain.Push(mat1);
    chain.Push(mat2);
    chain.Push(mat3);
    chain.Push(mat4);
    chain.Push(mat5);

    auto count_order_opt = chain.GetOptimalMultiplyCountOrder();
    auto optim_count = count_order_opt.num_operations;
    auto&& order = count_order_opt.order;

    std::vector<size_t> naive_order = {0, 1, 2, 3};
    auto &&matrix1 = matrix_chain::DoMultiply(chain.begin(), chain.end(), naive_order);
    auto &&matrix2 = matrix_chain::DoMultiply(chain.begin(), chain.end(), order);

    ASSERT_EQ(matrix1, matrix2);
}

TEST(MatrixChainTest, Multiply4) {
    matrix::Matrix<int> mat1(1000, 200);
    matrix::Matrix<int> mat2(200, 100);
    matrix::Matrix<int> mat3(100, 100);
    matrix::Matrix<int> mat4(100, 1000);
    matrix::Matrix<int> mat5(1000, 10);

    for (size_t i = 0; i < 1000; ++i)
        for (size_t j = 0; j < 200; ++j)
            mat1[i][j] = 1;

    for (size_t i = 0; i < 200; ++i)
        for (size_t j = 0; j < 100; ++j)
            mat2[i][j] = 2;

    for (size_t i = 0; i < 100; ++i)
        for (size_t j = 0; j < 100; ++j)
            mat3[i][j] = 3;

    for (size_t i = 0; i < 100; ++i)
        for (size_t j = 0; j < 1000; ++j)
            mat4[i][j] = 2;

    for (size_t i = 0; i < 1000; ++i)
        for (size_t j = 0; j < 10; ++j)
            mat5[i][j] = 3;

    matrix_chain::Chain<int> chain;
    chain.Push(mat1);
    chain.Push(mat2);
    chain.Push(mat3);
    chain.Push(mat4);
    chain.Push(mat5);

    auto count_order_opt = chain.GetOptimalMultiplyCountOrder();
    auto optim_count = count_order_opt.num_operations;
    auto&& order = count_order_opt.order;

    std::vector<size_t> naive_order = {0, 1, 2, 3};
    auto &&matrix1 = matrix_chain::DoMultiply(chain.begin(), chain.end(), naive_order);
    auto &&matrix2 = matrix_chain::DoMultiply(chain.begin(), chain.end(), order);

    ASSERT_EQ(matrix1, matrix2);
}

TEST(MatrixChainTest, PushMove) {
    matrix::Matrix<int> mat1(1000, 200);
    matrix::Matrix<int> mat2(200, 100);
    matrix::Matrix<int> mat3(100, 100);
    matrix::Matrix<int> mat4(100, 1000);
    matrix::Matrix<int> mat5(1000, 10);

    for (size_t i = 0; i < 1000; ++i)
        for (size_t j = 0; j < 200; ++j)
            mat1[i][j] = 1;

    for (size_t i = 0; i < 200; ++i)
        for (size_t j = 0; j < 100; ++j)
            mat2[i][j] = 2;

    for (size_t i = 0; i < 100; ++i)
        for (size_t j = 0; j < 100; ++j)
            mat3[i][j] = 3;

    for (size_t i = 0; i < 100; ++i)
        for (size_t j = 0; j < 1000; ++j)
            mat4[i][j] = 2;

    for (size_t i = 0; i < 1000; ++i)
        for (size_t j = 0; j < 10; ++j)
            mat5[i][j] = 3;

    matrix_chain::Chain<int> chain;
    chain.Push(std::move(mat1));
    chain.Push(std::move(mat2));
    chain.Push(std::move(mat3));
    chain.Push(std::move(mat4));
    chain.Push(std::move(mat5));

    auto count_order_opt = chain.GetOptimalMultiplyCountOrder();
    auto optim_count = count_order_opt.num_operations;
    auto&& order = count_order_opt.order;

    std::vector<size_t> naive_order = {0, 1, 2, 3};
    auto &&matrix1 = matrix_chain::DoMultiply(chain.begin(), chain.end(), naive_order);
    auto &&matrix2 = matrix_chain::DoMultiply(chain.begin(), chain.end(), order);

    ASSERT_EQ(matrix1, matrix2);
}

TEST(MatrixChainTest, Emplace) {
    std::vector<int> v1 {1, 2, 1, 0, -2, 1, 2, -1};
    std::vector<int> v2 {1, 0, -1, 0, 2, 0, 3, -3};
    std::vector<int> v3 {1, 2, 1, 3, -2, 0, -3, 3, 1, -2, 0, 4, 1, 2, 0, -1};
    std::vector<int> result {4, -12, 5, 41, 0, 4, 1, -1, 2, -16, 0, 23, -2, 16, 0, -23};

    matrix_chain::Chain<int> chain;
    chain.Emplace(4, 2, v1.begin(), v1.end());
    chain.Emplace(2, 4, v2.begin(), v2.end());
    chain.Emplace(4, 4, v3.begin(), v3.end());

    auto count_order_opt = chain.GetOptimalMultiplyCountOrder();
    auto optim_count = count_order_opt.num_operations;
    auto&& order = count_order_opt.order;

    std::vector<size_t> naive_order = {0, 1};
    auto &&matrix1 = matrix_chain::DoMultiply(chain.begin(), chain.end(), naive_order);
    auto &&matrix2 = matrix_chain::DoMultiply(chain.begin(), chain.end(), order);

    ASSERT_EQ(matrix1, matrix2);
    for (size_t i = 0; i < 4; ++i)
        for (size_t j = 0; j < 4; ++j)
            ASSERT_EQ(result[i * 4 + j], matrix1[i][j]);
}

TEST(MatrixChainTest, MultiplyNotMatrix1) {
    std::vector<size_t> forder = {0, 1, 2, 3, 4, 5, 6};
    std::vector<size_t> sorder = {4, 6, 3, 5, 1, 0, 2};
    std::vector<int> int_chain1 {1, 2, 1, 0, -2, 1, 2, -1};
    auto &&result1 = matrix_chain::DoMultiply(int_chain1.begin(), int_chain1.end(), forder);
    auto &&result2 = matrix_chain::DoMultiply(int_chain1.begin(), int_chain1.end(), sorder);

    ASSERT_EQ(result1, result2);
    ASSERT_EQ(result1, 0);

    std::vector<int> int_chain2 {1, 2, 1, 4, -2, 3, 2, -1};
    auto &&result3 = matrix_chain::DoMultiply(int_chain2.begin(), int_chain2.end(), forder);
    auto &&result4 = matrix_chain::DoMultiply(int_chain2.begin(), int_chain2.end(), sorder);

    ASSERT_EQ(result3, result4);
    ASSERT_EQ(result3, 2 * 4 * 2 * 3 * 2);
}

TEST(MatrixChainTest, MultiplyNotMatrix2) {
    struct S {
        int x;
        S &operator*=(const S &other) {
            x *= other.x;
            return *this;
        }

        bool operator==(const S &other) const {
            return (x == other.x);
        }
    };

    std::vector<size_t> forder = {0, 1, 2, 3, 4, 5, 6};
    std::vector<size_t> sorder = {4, 6, 3, 5, 1, 0, 2};
    std::vector<S> chain1 {{1}, {2}, {1}, {0}, {-2}, {1}, {2}, {-1}};
    S result1 = matrix_chain::DoMultiply(chain1.begin(), chain1.end(), forder);
    S result2 = matrix_chain::DoMultiply(chain1.begin(), chain1.end(), sorder);

    ASSERT_EQ(result1, result2);
    ASSERT_EQ(result1, S{0});

    std::vector<S> chain2 {{1}, {2}, {1}, {4}, {-2}, {3}, {2}, {-1}};
    S result3 = matrix_chain::DoMultiply(chain2.begin(), chain2.end(), forder);
    S result4 = matrix_chain::DoMultiply(chain2.begin(), chain2.end(), sorder);

    ASSERT_EQ(result3, result4);
    ASSERT_EQ(result3, S{2 * 4 * 2 * 3 * 2});
}