#include "matrix_chain.hpp"
#include "matrix.hpp"

#include <iostream>
#include <exception>

namespace
{
    template <typename T>
    void ProcessInput(matrix_chain::Chain<T> &chain, std::istream &in) {
        int num_sizes = 0;
        in >> num_sizes;

        if (num_sizes <= 2)
            throw std::logic_error("Incorrect number of sizes of matrixes");

        size_t size1 = 0;
        size_t size2 = 0;

        in >> size1;

        for (int i = 1; i < num_sizes; i++) {
            in >> size2;
            matrix::Matrix<T> matrix{size1, size2};
            chain.Push(matrix);
            size1 = size2;
        }
    }
} // namespace


int main() {
    matrix_chain::Chain<int> chain;
    ProcessInput(chain, std::cin);

    auto optim = chain.GetOptimalMultiplyCountOrder();
    int optim_count = optim.first;
    std::vector<int> order = optim.second;
    int count = chain.GetMultiplyCount();

    for (auto&& elem : order)
        std::cout << elem << " ";
    std::cout << std::endl;
    std::cout << static_cast<double>(count) / optim_count << std::endl;
}