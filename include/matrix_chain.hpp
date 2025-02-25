#pragma once

#include "matrix.hpp"
#include <vector>
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
    }

    int GetOptimalMultiplyCount() const {
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

        std::cout << GetOrderString(1, n, split) << std::endl;

        std::vector<int> ord = GetOrderVector(1, n, split);

        for (auto&& elem : ord)
            std::cout << elem << " ";
        std::cout << std::endl;

		return dp[1][n];
    }

    int GetMultiplyCount() const {
        int count = 0;
        for (int i = 1; i < sizes_.size() - 1; i++)
        {
            count += sizes_[0] * sizes_[i] * sizes_[i + 1];
        }
        return count;
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