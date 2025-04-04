#pragma once

#include "matrix.hpp"
#include <cassert>
#include <exception>
#include <iostream>
#include <limits>
#include <list>
#include <vector>

namespace matrix_chain {

template <typename T>
class Chain final {
    struct DpResult {
        size_t min_operations;
        size_t split_point;
    };

    using DpTable = std::vector<std::vector<DpResult>>;

public:
    struct MultiplyCountOrder
    {
        size_t num_operations;
        std::vector<size_t> order;
    };

    void Push(const matrix::Matrix<T> &mat) {
        chain_.push_back(mat);
        if (chain_.size() == 1)
            sizes_.push_back(chain_.back().GetRowCount());
        else if (sizes_.back() != chain_.back().GetRowCount())
            throw std::logic_error("Sizes of matrixes don't match");

        sizes_.push_back(chain_.back().GetColumnCount());
        assert(chain_.size() + 1U == sizes_.size());
    }

    void Push(matrix::Matrix<T> &&mat) {
        chain_.push_back(std::move(mat));
        if (chain_.size() == 1U)
            sizes_.push_back(chain_.back().GetRowCount());
        else if (sizes_.back() != chain_.back().GetRowCount())
            throw std::logic_error("Sizes of matrixes don't match");

        sizes_.push_back(chain_.back().GetColumnCount());
        assert(chain_.size() + 1U == sizes_.size());
    }

    template <typename... Args>
    void Emplace(Args &&...args) {
        chain_.emplace_back(std::forward<Args>(args)...);
        if (chain_.size() == 1)
            sizes_.push_back(chain_.back().GetRowCount());
        else if (sizes_.back() != chain_.back().GetRowCount())
            throw std::logic_error("Sizes of matrixes don't match");

        sizes_.push_back(chain_.back().GetColumnCount());
        assert(chain_.size() + 1U == sizes_.size());
    }

    MultiplyCountOrder GetOptimalMultiplyCountOrder() const {
        size_t n = sizes_.size() - 1U;
        DpTable dp(n + 1, std::vector<DpResult>(n + 1, {0, 0}));

        for (size_t l = 2U; l <= n; ++l) {
            for (size_t i = 1U; i <= n - l + 1U; ++i) {
                size_t j = i + l - 1U;

                dp[i][j].min_operations = std::numeric_limits<size_t>::max();
                for (size_t k = i; k <= j - 1U; ++k) {
                    size_t val =
                        dp[i][k].min_operations + dp[k + 1][j].min_operations + sizes_[i - 1] * sizes_[k] * sizes_[j];
                    if (val < dp[i][j].min_operations)
                        dp[i][j] = {val, k};
                }
            }
        }

        std::vector<size_t> order = GetOrderVector(1, n, dp);
        assert(order.size() + 1U == chain_.size());
        return MultiplyCountOrder{dp[1][n].min_operations, order};
    }

    size_t GetMultiplyCount() const {
        size_t count = 0, size = sizes_.size();

        for (int i = 1; i < size - 1U; ++i)
            count += sizes_[i] * sizes_[i + 1];
        count *= sizes_[0];

        return count;
    }

    matrix::Matrix<T> DoMultiply(const std::vector<size_t> &order) const {
        size_t order_size = order.size();
        size_t chain_size = chain_.size();

        if (chain_.empty())
            throw std::runtime_error("The chain of matrix is empty");
        if (order.empty() || order_size + 1U != chain_size)
            throw std::runtime_error("The order of multiplication is incorrect");

        std::list<matrix::Matrix<T>> current_chain {chain_.begin(), chain_.end()};
        auto current_order = order;

        for (size_t i = 0; i < current_order.size(); ++i) {
            int matrix_i = current_order[i];

            if (matrix_i < 0 || matrix_i >= current_chain.size())
                throw std::out_of_range("Invalid value of order");

            auto it = current_chain.begin();
            std::advance(it, matrix_i);
            auto it_next = std::next(it);

            if (it_next == current_chain.end())
                throw std::out_of_range(std::string("Invalid value of order") + std::to_string(i));

            (*it) *= (*it_next);
            current_chain.erase(it_next);

            for (size_t j = 0; j < current_order.size(); ++j) {
                if (current_order[j] > matrix_i)
                    current_order[j]--;
            }
        }

        return current_chain.front();
    }

private:
    static std::vector<size_t> GetOrderVector(size_t i, size_t j, DpTable &dp) {
        if (i == j)
            return {};

        size_t k = dp[i][j].split_point;
        std::vector<size_t> left = GetOrderVector(i, k, dp);
        std::vector<size_t> right = GetOrderVector(k + 1U, j, dp);
        left.insert(left.end(), right.begin(), right.end());
        left.push_back(k - 1U);
        return left;
    }

    static std::string GetOrderString(int i, int j, std::vector<std::vector<int>> &split) {
        if (i == j)
            return "A" + std::to_string(i);

        int k = split[i][j];
        return "(" + GetOrderString(i, k, split) + GetOrderString(k + 1, j, split) + ")";
    }

    std::vector<matrix::Matrix<T>> chain_;
    std::vector<size_t> sizes_;
};  // class Chain

}  // namespace matrix_chain