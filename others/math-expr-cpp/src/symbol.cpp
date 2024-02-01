#include <memory>
#include <ostream>
#include <string>

#include "mathexpr/symbol.hpp"

namespace mathexpr
{

Symbol::Symbol()
{
}

Symbol::Symbol(std::string id) :
    id{id},
    type{Type::VARIABLE}
{
}

Symbol::Symbol(double value) :
    value{value},
    type{Type::NUMBER}
{
}

std::unique_ptr<SymbolNode> Symbol::operator+(double value)
{
    Symbol sym = Symbol{"+"};
    sym.type = Symbol::Type::OPERATOR;
    std::unique_ptr<SymbolNode> root = SymbolNode::create_node(sym);
    root->left = SymbolNode::create_node(*this);
    root->right = SymbolNode::create_node(Symbol{value});
    return root;
}

SymbolNode::SymbolNode()
{
}

SymbolNode::SymbolNode(Symbol symbol) :
    sym{symbol}
{
}

std::unique_ptr<SymbolNode> SymbolNode::create_node(Symbol symbol)
{
    return std::unique_ptr<SymbolNode>{new SymbolNode{symbol}};
}

std::unique_ptr<SymbolNode>
operator+(std::unique_ptr<SymbolNode> node, double value)
{
    Symbol sym = Symbol{"+"};
    sym.type = Symbol::Type::OPERATOR;
    std::unique_ptr<SymbolNode> root = SymbolNode::create_node(sym);
    root->left = std::move(node);
    root->right = SymbolNode::create_node(Symbol{value});
    return root;
}

std::ostream &operator<<(std::ostream &os, const SymbolNode &node)
{
    if (node.left != nullptr && node.right != nullptr)
        os << "(";
    os << node.left;

    if (node.sym.type == Symbol::Type::NUMBER)
        os << node.sym.value;
    else
        os << node.sym.id;

    os << node.right;
    if (node.left != nullptr && node.right != nullptr)
        os << ")";
    return os;
}

std::ostream &
operator<<(std::ostream &os, const std::unique_ptr<SymbolNode> &node)
{
    if (node == nullptr)
        return os;

    if (node->left != nullptr && node->right != nullptr)
        os << "(";
    os << node->left;

    if (node->sym.type == Symbol::Type::NUMBER)
        os << node->sym.value;
    else
        os << node->sym.id;

    os << node->right;
    if (node->left != nullptr && node->right != nullptr)
        os << ")";
    return os;
}

}
