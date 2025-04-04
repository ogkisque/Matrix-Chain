#include "matrix_chain.hpp"
#include "matrix.hpp"

#include <iomanip>
#include <limits>
#include <iostream>
#include <exception>

namespace {
template <typename T>
void ProcessInput(matrix_chain::Chain<T> &chain, std::istream &in) {
    int num_sizes = 0;
    in >> num_sizes;
    if (!in.good())
        throw std::runtime_error("Incorrect input data");

    if (num_sizes <= 2)
        throw std::logic_error("Incorrect number of sizes of matrixes");

    size_t size1 = 0;
    size_t size2 = 0;

    in >> size1;
    if (!in.good())
        throw std::runtime_error("Incorrect input data");

    for (int i = 1; i < num_sizes; ++i) {
        in >> size2;
        if (!in.good())
            throw std::runtime_error("Incorrect input data");

        chain.Emplace(size1, size2);
        size1 = size2;
    }
}
}  // namespace

int main() try {
    matrix_chain::Chain<int> chain;
    ProcessInput(chain, std::cin);

    auto count_order_opt = chain.GetOptimalMultiplyCountOrder();
    size_t count = chain.GetMultiplyCount();

    for (auto &&elem : count_order_opt.order)
        std::cout << elem << " "; std::cout << std::endl;
    
    double difference = static_cast<double>(count) / count_order_opt.num_operations;
    auto &&result = chain.DoMultiply(count_order_opt.order);

    if (std::fabs(std::round(difference) - difference) < 1e-5)
        std::cout << static_cast<long>(std::round(difference)) << std::endl;
    else
        std::cout << std::fixed << std::setprecision(3) << difference << std::endl;
} catch (std::exception &ex) {
    std::cout << "Program is failed: " << ex.what() << std::endl;
}