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
    size_t max_n = std::max(n, other.n);
    size_t min_n = std::min(n, other.n);
    Polynomial new_p(max_n);
    size_t i;
    for (i = 0; i < min_n; ++i)
        new_p.set_coefficient(i, values[i] + other.values[i]);
    
    double *values_greater_p;
    if (min_n == other.n)
        values_greater_p = values;
    else
        values_greater_p = other.values;

    for (size_t j = i; j < max_n; ++j)
        new_p.set_coefficient(j, values_greater_p[j]);

    return new_p;
}
