#include <iostream>

#include "mathexpr/expr.hpp"
#include "mathexpr/greetings.hpp"

using namespace mathexpr;

int main()
{
    greetings();

    Symbol sym{"x"};
    Expr expr = 1 + (10 + sym);
    std::cout << expr << std::endl;
    std::cout << expr.eval(sym, 15) << std::endl;
    return 0;
}
