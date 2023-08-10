#include <iostream>

#include "polynomial.hpp"

int main()
{
    using namespace jota;

    Polynomial p(3);
    p.set_coefficient(0, 9);
    p.set_coefficient(1, 6);
    p.set_coefficient(2, 1);

    Polynomial p2(3);
    p2.set_coefficient(0, -5);
    p2.set_coefficient(1, -2);
    p2.set_coefficient(2, 1);

    Polynomial new_p = p - p2;
    // x² + 8x + 14
    std::cout << (p == p2) << std::endl;

    new_p.print(0);

    for (int i = -10; i < 11; ++i)
        std::cout << "p(" << i << ") = " << new_p.eval(i) << std::endl;

    
    std::cout << std::endl;
    Polynomial p3(2);
    p3.set_coefficient(0, -3);
    p3.set_coefficient(1, 1);
    Polynomial p4(2);
    p4.set_coefficient(0, 3);
    p4.set_coefficient(1, 1);
    p3.print();
    std::cout << "*" << std::endl;
    p4.print();
    std::cout << "=" << std::endl;
    Polynomial p5 = p3 * p4;
    (p5).print();


    return 0;
}
