#include <iostream>

#include "polynomial.hpp"

int main()
{
    using namespace jota;

    Polynomial p(3);
    p.set_coefficient(0, 9);
    p.set_coefficient(1, 6);
    p.set_coefficient(2, 1);

    Polynomial p2(2);
    p2.set_coefficient(0, -5);
    p2.set_coefficient(1, -2);

    Polynomial new_p = p + p2;
    // x² + 6x + 9

    new_p.print();

    std::cout << new_p.eval(-2) << std::endl;

    return 0;
}
