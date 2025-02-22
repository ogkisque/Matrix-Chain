#pragma once

#include "matrix.hpp"
#include <vector>
#include <cassert>
#include <exception>
#include <iostream>
#include <limits>

namespace matrix_chain {

template <typename T>
class Chain {
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
        std::vector<std::vector<int>> order(n + 1, std::vector<int>(n + 1, 0));
		
		for (int l = 2; l <= n; ++l) {
			for (int i = 1; i <= n - l + 1; ++i) {
				int j = i + l - 1;
				dp[i][j] = std::numeric_limits<int>::max();
				for (int k = i; k <= j - 1; ++k) {
                    int val = dp[i][k] + dp[k + 1][j] + sizes_[i - 1] * sizes_[k] * sizes_[j];
                    if (val < dp[i][j])
                    {
                        dp[i][j] = val;
                        order[i][j] = k;
                    }                   
                }
			}
		}

        std::cout << GetOrderString(1, n, order) << std::endl;

        std::vector<int> ord;
        GetOrderVector(1, n, order, ord);

        for (auto&& elem : ord)
            std::cout << elem << " ";
        std::cout << std::endl;

		return dp[1][n];
    }

private:
    static int GetOrderVector(int i, int j, std::vector<std::vector<int>> &order, std::vector<int> &ord) {
        if (i == j)
            return i;
    
        int k = order[i][j];
        int i1 = GetOrderVector(i, k, order, ord);
        int i2 = GetOrderVector(k + 1, j, order, ord);
        if (i1 != 0) ord.push_back(i1);
        if (i2 != 0) ord.push_back(i2);
    }

    static std::string GetOrderString(int i, int j, std::vector<std::vector<int>> &order) {
        if (i == j)
            return "A" + std::to_string(i);

        int k = order[i][j];
        return "(" + GetOrderString(i, k, order) + GetOrderString(k + 1, j, order) + ")";
    }

    std::vector<matrix::Matrix<T>> chain_;
    std::vector<int> sizes_;

}; // class Chain

} // namespace matrix_chain