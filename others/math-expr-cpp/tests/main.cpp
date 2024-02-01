#include <iostream>

#include "mathexpr/expr.hpp"
#include "mathexpr/greetings.hpp"

using namespace mathexpr;

int main()
{
    greetings();

    Symbol sym{"x"};
    Expr expr = (sym + 20) + 10 + 20;
    std::cout << expr << std::endl;
    return 0;
}
