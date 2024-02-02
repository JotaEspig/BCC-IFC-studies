#include <iostream>

#include "mathexpr/expr.hpp"
#include "mathexpr/greetings.hpp"

using namespace mathexpr;

int main()
{
    greetings();

    Symbol x{"x"};
    Expr expr = 8 + 2 * (10 + x) - 1.0 / 9;
    std::cout << expr << std::endl;
    std::cout << expr.eval(x, 0) << std::endl;
    return 0;
}
