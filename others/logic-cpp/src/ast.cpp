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

std::ostream &operator<<(std::ostream &os, const AST &ast)
{
    os << ast.root;
    return os;
}

std::ostream &operator<<(std::ostream &os, const AST::node_ptr &node)
{
    if (node == nullptr)
    {
        return os;
    }
    else if (node->value.type == Token::Type::OPERATOR)
    {
        os << "(";
        if (node->value.value == "-")
        {
            os << node->value.value;
            os << node->left;
        }
        else
        {
            os << node->left;
            os << node->value.value;
            os << node->right;
        }
        os << ")";
    }
    else
    {
        os << node->value.value;
    }
    return os;
}

} // namespace logic
