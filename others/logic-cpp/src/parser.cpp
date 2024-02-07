#include <iostream>
#include <memory>
#include <string>

#include "logic/parser.hpp"

namespace logic
{

Parser::Parser()
{
}

Parser::Parser(const token_vec &tokens) :
    tokens{tokens}
{
}

AST Parser::generate_ast()
{
    auto tk_begin = tokens.begin();
    auto tk_end = tokens.end();

    AST ast{};
    ast.root = parse_expression(tk_begin, tk_end);

    return ast;
}

AST::node_ptr Parser::parse_expression(
    const token_vec::iterator &begin, const token_vec::iterator &end
)
{
    if (begin >= end)
    {
        error = "parser: begin <= end at parse_expression";
        return nullptr;
    }

    auto node = std::make_unique<AST::Node>();

    token_vec::iterator operator_it = begin;
    while (operator_it->value != "&" && operator_it->value != "v"
           && operator_it < end)
        ++operator_it;
    if (operator_it >= end)
    {
        node = parse_term(begin, end);
    }
    else
    {
        node->value = *operator_it;
        node->left = parse_term(begin, operator_it);
        node->right = parse_term(operator_it + 1, end);
    }

    return node;
}

AST::node_ptr Parser::parse_term(
    const token_vec::iterator &begin, const token_vec::iterator &end
)
{
    auto node = std::make_unique<AST::Node>();
    node->value.value = "SEXO";
    return node;
}

AST::node_ptr Parser::parse_factor(
    const token_vec::iterator &begin, const token_vec::iterator &end
)
{
    auto node = std::make_unique<AST::Node>();
    node->value.value = "SEXO";
    return node;
}

} // namespace logic
