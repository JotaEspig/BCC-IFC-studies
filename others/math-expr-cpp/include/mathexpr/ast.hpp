#pragma once

#include <memory>

#include "mathexpr/symbol.hpp"

namespace mathexpr
{

class AST
{
public:
    typedef SymbolNode Node;

    std::unique_ptr<Node> root = nullptr;

    AST();
    AST(Symbol symbol);
};

} // namespace mathexpr
