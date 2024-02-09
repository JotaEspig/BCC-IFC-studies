/**
 * \file Parser operations
 * \author João Vitor Espig (JotaEspig)
 * \date 05 February, 2024
 * \version 05 February, 2024
 **/
#pragma once

#include <string>
#include <vector>

#include "logic/ast.hpp"
#include "logic/token.hpp"

namespace logic
{

class Parser
{
    typedef std::vector<Token> token_vec;

public:
    std::string error;

    Parser();
    Parser(const token_vec &tokens);

    const token_vec &tokens() const;
    const token_vec::iterator &begin() const;
    const token_vec::iterator &end() const;
    const token_vec::iterator &curr() const;
    AST::node_ptr set_error(std::string msg);
    void next();
    AST generate_ast();
    AST::node_ptr parse_expression();
    AST::node_ptr parse_term();
    AST::node_ptr parse_factor();

private:
    token_vec _tokens;
    token_vec::iterator _begin;
    token_vec::iterator _end;
    token_vec::iterator _curr;
};

} // namespace logic
