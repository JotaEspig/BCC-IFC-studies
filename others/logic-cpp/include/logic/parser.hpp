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
    std::string error;

    Parser();
    Parser(const token_vec &tokens);

    AST generate_ast();
    AST::node_ptr parse_expression(
        const token_vec::iterator &begin, const token_vec::iterator &end
    );
    AST::node_ptr parse_term(
        const token_vec::iterator &begin, const token_vec::iterator &end
    );
    AST::node_ptr parse_factor(
        const token_vec::iterator &begin, const token_vec::iterator &end
    );
};

} // namespace logic
