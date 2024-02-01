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

std::unique_ptr<SymbolNode> operator+(const Symbol &sym, double value)
{
    Symbol sym_op = Symbol{"+"};
    sym_op.type = Symbol::Type::OPERATOR;
    std::unique_ptr<SymbolNode> root = SymbolNode::create_node(sym_op);
    root->left = SymbolNode::create_node(sym);
    root->right = SymbolNode::create_node(Symbol{value});
    return root;
}

std::unique_ptr<SymbolNode> operator+(double value, const Symbol &sym)
{
    return sym + value;
}

std::ostream &operator<<(std::ostream &os, const Symbol &sym)
{
    if (sym.type == Symbol::Type::NUMBER)
        os << sym.value;
    else
        os << sym.id;
    return os;
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

std::unique_ptr<SymbolNode>
operator+(double value, std::unique_ptr<SymbolNode> node)
{
    return std::move(node) + value;
}

std::ostream &operator<<(std::ostream &os, const SymbolNode &node)
{
    if (node.left != nullptr && node.right != nullptr)
        os << "(";
    os << node.left;
    os << node.sym;
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
    os << node->sym;
    os << node->right;
    if (node->left != nullptr && node->right != nullptr)
        os << ")";
    return os;
}

}
