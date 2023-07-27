#include <iostream>
#include <cmath>
#include <stdexcept>
#include <cstddef>

#include "polynomial.hpp"

jota::Polynomial::Polynomial(size_t _n)
{
    n = _n;
    values = new double[n];
}

jota::Polynomial::~Polynomial()
{
    n = 0;
    delete[] values;
}

void jota::Polynomial::set_coefficient(size_t pos, double val)
{
    if (pos >= n)
        std::invalid_argument("pos greater than size of polynomial");

    values[pos] = val;
}

double jota::Polynomial::eval(double x)
{
    double sum = 0;
    for (size_t i = 0; i < n; ++i)
        sum += values[i] * pow(x, i);

    return sum;
}

void jota::Polynomial::print()
{
    for (size_t i = 0; i < n - 1; ++i)
        std::cout << values[n - i - 1] << "x^" << n - i - 1 << " + ";

    std::cout << values[0] << std::endl;
}

jota::Polynomial jota::Polynomial::operator+(const Polynomial &other)
{
    Polynomial new_p(std::max(n, other.n));
    size_t min_n = std::min(n, other.n);
    for (size_t i = 0; i < min_n; ++i)
        new_p.set_coefficient(i, values[i] + other.values[i]);

    return new_p;
}
