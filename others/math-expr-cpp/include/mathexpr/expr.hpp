#pragma once

#include <memory>
#include <ostream>

#include "mathexpr/symbol.hpp"

namespace mathexpr
{

class Expr
{
public:
    std::unique_ptr<SymbolNode> root = nullptr;

    Expr();
    Expr(std::unique_ptr<SymbolNode> &&node);

    double eval(const Symbol &sym, double value) const;

    friend std::ostream &operator<<(std::ostream &os, const Expr &expr);

private:
    double eval_nodes(
        const std::unique_ptr<SymbolNode> &node, const Symbol &sym, double value
    ) const;
};

} // namespace mathexpr
