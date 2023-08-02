#include <stdio.h>
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
        throw std::invalid_argument("pos greater than size of polynomial");

    values[pos] = val;
}

double jota::Polynomial::eval(double x)
{
    double sum = 0;
    for (size_t i = 0; i < n; ++i)
        sum += values[i] * pow(x, i);

    return sum;
}

void jota::Polynomial::print(int precision)
{
    for (size_t i = 0; i < n - 1; ++i)
        printf("%.*lfx^%ld + ", precision, values[n - i - 1], n -i - 1);

    printf("%.*lf\n", precision, values[0]);
}

void jota::Polynomial::reduce_degree()
{
    size_t j;
    for (size_t i = 0; i < n; ++i)
        if (values[i] != 0)
            j = i + 1;

    double *aux = new double[j];
    for (size_t i = 0; i < j; ++i)
        aux[i] = values[i];

    delete[] values;
    values = aux;
    n = j;
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

jota::Polynomial jota::Polynomial::operator-(const Polynomial &other)
{
    size_t max_n = std::max(n, other.n);
    size_t min_n = std::min(n, other.n);
    Polynomial new_p(max_n);
    size_t i;
    for (i = 0; i < min_n; ++i)
        new_p.set_coefficient(i, values[i] - other.values[i]);    
        
    if (min_n == n)
        for (size_t j = i; j < max_n; ++j)
            new_p.set_coefficient(j, -other.values[j]);
    else
        for (size_t j = i; j < max_n; ++j)
            new_p.set_coefficient(j, values[j]);

    new_p.reduce_degree();
    return new_p;
}

jota::Polynomial jota::Polynomial::operator*(const Polynomial &other)
{
    size_t new_n = n + other.n - 1;
    Polynomial new_p(new_n);
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < other.n; ++j)
        {
            double prev = new_p.values[i + j];
            new_p.set_coefficient(i + j, prev + values[i] * other.values[j]);
        }
    }

    return new_p;
}

jota::Polynomial jota::Polynomial::operator/(const Polynomial &other)
{
}

bool jota::Polynomial::operator==(const Polynomial &other)
{
    size_t min_n = std::min(n, other.n);
    for (size_t i = 0; i < min_n; ++i)
        if (values[i] != other.values[i])
            return false;

    return true;
}

bool jota::Polynomial::operator!=(const Polynomial &other)
{
    return !(*this == other);
}
