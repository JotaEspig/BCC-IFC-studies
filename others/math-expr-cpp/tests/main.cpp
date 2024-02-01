#include <iostream>

#include "mathexpr/ast.hpp"
#include "mathexpr/expr.hpp"
#include "mathexpr/greetings.hpp"

using namespace mathexpr;

int main()
{
    greetings();
    auto pica = AST(Symbol{});
    std::cout << pica.root->sym.value << std::endl;

    auto sym = Symbol{"x"};
    Expr expr = (sym + 20) + 10 + 20;
    std::cout << expr << std::endl;
    return 0;
}
