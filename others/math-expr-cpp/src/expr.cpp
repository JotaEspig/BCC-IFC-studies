#include <memory>

#include "mathexpr/expr.hpp"
#include "mathexpr/symbol.hpp"

namespace mathexpr
{

Expr::Expr()
{
}

Expr::Expr(std::unique_ptr<SymbolNode> &&node)
{
    root = std::move(node);
}

std::ostream &operator<<(std::ostream &os, const Expr &expr)
{
    if (expr.root != nullptr)

        os << expr.root;
    return os;
}

} // namespace mathexpr
