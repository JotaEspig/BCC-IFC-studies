#pragma once

#include <memory>

#include "mathexpr/ast.hpp"

namespace mathexpr
{

class Expr : public AST
{
public:
    Expr &operator=(std::unique_ptr<Node> node);
};

} // namespace mathexpr
