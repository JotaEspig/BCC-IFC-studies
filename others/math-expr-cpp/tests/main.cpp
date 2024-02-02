#include <iostream>

#include "mathexpr/expr.hpp"
#include "mathexpr/greetings.hpp"

using namespace mathexpr;

int main()
{
    greetings();

    Symbol x{"x"};
    Expr expr = 1 + (10 + x);
    std::cout << expr << std::endl;
    std::cout << expr.eval(x, 15) << std::endl;
    return 0;
}
