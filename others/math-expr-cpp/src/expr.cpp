#include "mathexpr/expr.hpp"

namespace mathexpr
{

Expr &Expr::operator=(std::unique_ptr<Node> node)
{
    root = std::move(node);
    return *this;
}

} // namespace mathexpr
