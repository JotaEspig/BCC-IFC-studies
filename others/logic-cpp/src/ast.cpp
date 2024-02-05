#include "logic/ast.hpp"
#include "logic/token.hpp"

namespace logic
{

AST::Node::Node()
{
}

AST::Node::Node(const Token &token) :
    value{token}
{
}

AST::AST()
{
}

} // namespace logic
