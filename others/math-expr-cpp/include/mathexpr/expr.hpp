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

    // double Eval(const Symbol &sym, double value) const;

    friend std::ostream &operator<<(std::ostream &os, const Expr &expr);
};

// typedef std::unique_ptr<ExprNode> Expr;

} // namespace mathexpr
