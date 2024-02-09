#include <memory>
#include <string>

#include "logic/parser.hpp"
#include "logic/token.hpp"

namespace logic
{

Parser::Parser()
{
}

Parser::Parser(const token_vec &tokens) :
    tokens{tokens},
    begin{Parser::tokens.begin()},
    end{Parser::tokens.end()}
{
}

AST::node_ptr Parser::set_error(std::string str)
{
    std::string base = "parser error: ";
    std::string final = base + str;
    error = final;
    begin = end;
    return nullptr;
}

void Parser::next()
{
    ++begin;
}

AST Parser::generate_ast()
{
    AST ast{};
    ast.root = parse_expression();
    if (error != "")
        ast.root = nullptr;

    return ast;
}

AST::node_ptr Parser::parse_expression()
{
    if (begin >= end)
    {
        set_error("parser: begin <= end at parse_expression");
        return nullptr;
    }
    else if (begin->type == Token::Type::UNKNOWN)
    {
        set_error("parser: Unknown token type");
        return nullptr;
    }

    auto node = parse_term();
    if (node == nullptr)
        return nullptr;

    while (begin < end && begin->type == Token::Type::OPERATOR
           && (begin->value == "->" || begin->value == "<->"))
    {
        auto temp = std::move(node);
        node = std::make_unique<AST::Node>();

        node->value = *begin;
        node->left = std::move(temp);
        next();
        node->right = parse_term();
        if (node->right == nullptr)
            return nullptr;
    }

    return node;
}

AST::node_ptr Parser::parse_term()
{
    if (begin >= end)
    {
        set_error("parser: begin <= end at parse_term");
        return nullptr;
    }
    else if (begin->type == Token::Type::UNKNOWN)
    {
        set_error("parser: Unknown token type");
        return nullptr;
    }

    auto node = parse_factor();
    if (node == nullptr)
        return nullptr;

    while (begin < end && begin->type == Token::Type::OPERATOR
           && (begin->value == "&" || begin->value == "v"))
    {
        auto temp = std::move(node);
        node = std::make_unique<AST::Node>();

        node->value = *begin;
        node->left = std::move(temp);
        next();
        node->right = parse_factor();
        if (node->right == nullptr)
            return nullptr;
    }

    return node;
}

AST::node_ptr Parser::parse_factor()
{
    if (begin >= end)
    {
        set_error("parser: begin <= end at parse_factor");
        return nullptr;
    }
    else if (begin->type == Token::Type::UNKNOWN)
    {
        set_error("parser: Unknown token type");
        return nullptr;
    }

    auto node = std::make_unique<AST::Node>();

    if (begin->value == "-")
    {
        node->value = *begin;
        next();
        node->left = parse_factor();
    }
    else if (begin->type == Token::Type::BOOL || begin->type == Token::Type::VARIABLE)
    {
        node->value = *begin;
        next();
    }
    else if (begin->value == "(")
    {
        next();
        node = parse_expression();
        if (begin->value != ")")
        {
            set_error("parser: not found expected \")\"");
            return nullptr;
        }
        next();
    }
    else
    {
        set_error("parser: not found Factor at parse_factor");
        return nullptr;
    }

    return node;
}

} // namespace logic
