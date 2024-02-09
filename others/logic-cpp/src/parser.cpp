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
    _tokens{tokens},
    _begin{_tokens.begin()},
    _end{_tokens.end()},
    _curr{_tokens.begin()}
{
}

const Parser::token_vec &Parser::tokens() const
{
    return _tokens;
}

const Parser::token_vec::iterator &Parser::begin() const
{
    return _begin;
}

const Parser::token_vec::iterator &Parser::end() const
{
    return _end;
}

const Parser::token_vec::iterator &Parser::curr() const
{
    return _curr;
}

AST::node_ptr Parser::set_error(std::string str)
{
    std::string base = "parser error: ";
    std::string final = base + str;
    error = final;
    _curr = _end;
    return nullptr;
}

void Parser::next()
{
    ++_curr;
}

AST Parser::generate_ast()
{
    AST ast{};
    ast.root = parse_expression();
    if (error == "" && _begin < _end)
        ast.root = set_error("begin < end at the end of the parsing");

    return ast;
}

AST::node_ptr Parser::parse_expression()
{
    if (_curr >= _end)
    {
        return set_error("begin <= end at parse_expression");
    }
    else if (_curr->type == Token::Type::UNKNOWN)
    {
        return set_error("Unknown token type");
    }

    auto node = parse_term();
    if (node == nullptr)
        return nullptr;

    while (_curr < _end && _curr->type == Token::Type::OPERATOR
           && (_curr->value == "->" || _curr->value == "<->"))
    {
        auto temp = std::move(node);
        node = std::make_unique<AST::Node>();

        node->value = *_curr;
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
    if (_curr >= _end)
    {
        return set_error("begin <= end at parse_term");
    }
    else if (_curr->type == Token::Type::UNKNOWN)
    {
        return set_error("Unknown token type");
    }

    auto node = parse_factor();
    if (node == nullptr)
        return nullptr;

    while (_curr < _end && _curr->type == Token::Type::OPERATOR
           && (_curr->value == "&" || _curr->value == "v"))
    {
        auto temp = std::move(node);
        node = std::make_unique<AST::Node>();

        node->value = *_curr;
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
    if (_curr >= _end)
    {
        return set_error("begin <= end at parse_factor");
    }
    else if (_curr->type == Token::Type::UNKNOWN)
    {
        return set_error("Unknown token type");
    }

    auto node = std::make_unique<AST::Node>();

    if (_curr->value == "-")
    {
        node->value = *_curr;
        next();
        node->left = parse_factor();
    }
    else if (_curr->type == Token::Type::BOOL || _curr->type == Token::Type::VARIABLE)
    {
        node->value = *_curr;
        next();
    }
    else if (_curr->value == "(")
    {
        next();
        node = parse_expression();
        if (_curr->value != ")")
        {
            return set_error("not found expected \")\"");
        }
        next();
    }
    else
    {
        return set_error("not found Factor at parse_factor");
    }

    return node;
}

} // namespace logic
