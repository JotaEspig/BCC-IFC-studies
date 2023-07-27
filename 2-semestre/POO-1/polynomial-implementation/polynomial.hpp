#pragma once

#include <cstddef>

namespace jota
{
    class Polynomial
    {
        double *values;
        size_t n;

    public:
        Polynomial(size_t n);
        ~Polynomial();

        void set_coefficient(size_t pos, double val);
        double eval(double x);
        void print();
        Polynomial operator+(const Polynomial &other);
    };
}
