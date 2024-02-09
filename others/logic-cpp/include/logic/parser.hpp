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
    token_vec tokens;
    token_vec::iterator begin;
    token_vec::iterator end;
    std::string error;

    Parser();
    Parser(const token_vec &tokens);

    AST::node_ptr set_error(std::string msg);
    void next();
    AST generate_ast();
    AST::node_ptr parse_expression();
    AST::node_ptr parse_term();
    AST::node_ptr parse_factor();
};

} // namespace logic
