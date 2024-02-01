#include <memory>

#include "mathexpr/ast.hpp"
#include "mathexpr/symbol.hpp"

namespace mathexpr
{

AST::AST()
{
}

AST::AST(Symbol symbol)
{
    root = AST::Node::create_node(symbol);
}

} // namespace mathexpr
