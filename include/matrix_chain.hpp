#pragma once

#include "matrix.hpp"
#include <vector>
#include <list>
#include <cassert>
#include <exception>
#include <iostream>
#include <limits>

namespace matrix_chain {

template <typename T>
class Chain final {
public:
    void Push(matrix::Matrix<T> &mat) {
        chain_.push_back(mat);
        if (chain_.size() == 1)
            sizes_.push_back(mat.GetRowCount());
        else
            if (sizes_.back() != mat.GetRowCount())
                throw std::logic_error("Sizes of matrixes don't match");

        sizes_.push_back(mat.GetColumnCount());
        assert(chain_.size() + 1 == sizes_.size());
    }

    std::pair<int, std::vector<int>> GetOptimalMultiplyCountOrder() const {
        int n = sizes_.size() - 1;
        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(n + 1, 0));
        std::vector<std::vector<int>> split(n + 1, std::vector<int>(n + 1, 0));
		
		for (int l = 2; l <= n; ++l) {
			for (int i = 1; i <= n - l + 1; ++i) {
				int j = i + l - 1;
				dp[i][j] = std::numeric_limits<int>::max();
				for (int k = i; k <= j - 1; ++k) {
                    int val = dp[i][k] + dp[k + 1][j] + sizes_[i - 1] * sizes_[k] * sizes_[j];
                    if (val < dp[i][j])
                    {
                        dp[i][j] = val;
                        split[i][j] = k;
                    }                   
                }
			}
		}

        std::vector<int> order = GetOrderVector(1, n, split);
        assert(order.size() + 1 == chain_.size());
		return std::make_pair(dp[1][n], order);
    }

    int GetMultiplyCount() const {
        int count = 0;
        size_t size = sizes_.size();
        
        for (int i = 1; i < size - 1; ++i) {
            count += sizes_[0] * sizes_[i] * sizes_[i + 1];
        }

        return count;
    }

    matrix::Matrix<T> DoMultiply(const std::vector<int> &order) const {
        size_t order_size = order.size();
        size_t chain_size = chain_.size();

        if (chain_.empty())
            throw std::runtime_error("The chain of matrix is empty");
        if (order.empty() || order_size + 1U != chain_size)
            throw std::runtime_error("The order of multiplication is incorrect");
        
        std::list<matrix::Matrix<T>> current_chain{chain_.begin(), chain_.end()};
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

            *it = *it * *it_next;
            
            current_chain.erase(it_next);
            
            for (size_t j = 0; j < current_order.size(); ++j) {
                if(current_order[j] > matrix_i)
                    current_order[j]--;
            }
        }

        return current_chain.front();
    }

private:
    static std::vector<int> GetOrderVector(int i, int j, std::vector<std::vector<int>> &split) {
        if (i == j)
            return {};

        int k = split[i][j];
        std::vector<int> left = GetOrderVector(i, k, split);
        std::vector<int> right = GetOrderVector(k + 1, j, split);
        left.insert(left.end(), right.begin(), right.end());
        left.push_back(k - 1);
        return left;
    }

    static std::string GetOrderString(int i, int j, std::vector<std::vector<int>> &split) {
        if (i == j)
            return "A" + std::to_string(i);

        int k = split[i][j];
        return "(" + GetOrderString(i, k, split) + GetOrderString(k + 1, j, split) + ")";
    }

    std::vector<matrix::Matrix<T>> chain_;
    std::vector<int> sizes_;
}; // class Chain

} // namespace matrix_chain