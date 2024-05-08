#include <array>
#include <iostream>

#include "matrix.hpp"

using namespace matx;

int main() {
    std::cout << "bla\n";
    mat_arr<3, 3, int> arr({std::array<int, 3>{0, 1, 2}, {3, 4, 5}, {6, 7, 8}});
    Matrix<3, 3, int> mat(arr);

    return 0;
}
