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

double Expr::eval(const Symbol &sym, double value) const
{
    return eval_nodes(root, sym, value);
}

std::ostream &operator<<(std::ostream &os, const Expr &expr)
{
    if (expr.root != nullptr)
        os << expr.root;
    return os;
}

double Expr::eval_nodes(
    const std::unique_ptr<SymbolNode> &node, const Symbol &sym, double value
) const
{
    if (node == nullptr)
        return 0;

    if (node->sym.type == Symbol::Type::NUMBER)
        return node->sym.value;
    else if (node->sym.type == Symbol::Type::VARIABLE && node->sym.id == sym.id)
        return value;

    double left_val = eval_nodes(node->left, sym, value);
    double right_val = eval_nodes(node->right, sym, value);
    double val = 0;
    if (node->sym.id == "+")
        val = left_val + right_val;

    return val;
}

} // namespace mathexpr
