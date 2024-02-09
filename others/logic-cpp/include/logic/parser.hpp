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

/**
 * \brief Parser
 * \author João Vitor Espig (JotaEspig)
 * \date 09 February, 2024
 * \version 09 February, 2024
 **/
class Parser
{
    typedef std::vector<Token> token_vec;

public:
    /** Error occured during parsing **/
    std::string error;

    /**
     * \brief Default Lexer constructor
     * \author João Vitor Espig (JotaEspig)
     * \date 04 February, 2024
     * \version 04 February, 2024
     **/
    Parser();
    /**
     * \brief Default Lexer constructor
     * \author João Vitor Espig (JotaEspig)
     * \date 04 February, 2024
     * \version 04 February, 2024
     * \param tokens - token_vec reference
     **/
    Parser(const token_vec &tokens);

    /**
     * \brief member tokens get
     * \author João Vitor Espig (JotaEspig)
     * \date 09 February, 2024
     * \version 09 February, 2024
     **/
    const token_vec &tokens() const;
    /**
     * \brief member begin get
     * \author João Vitor Espig (JotaEspig)
     * \date 09 February, 2024
     * \version 09 February, 2024
     **/
    const token_vec::iterator &begin() const;
    /**
     * \brief member end get
     * \author João Vitor Espig (JotaEspig)
     * \date 09 February, 2024
     * \version 09 February, 2024
     **/
    const token_vec::iterator &end() const;
    /**
     * \brief member curr get
     * \author João Vitor Espig (JotaEspig)
     * \date 09 February, 2024
     * \version 09 February, 2024
     **/
    const token_vec::iterator &curr() const;
    /**
     * \brief set error as msg and returns nullptr
     * \author João Vitor Espig (JotaEspig)
     * \date 09 February, 2024
     * \version 09 February, 2024
     * \param msg - error message
     **/
    AST::node_ptr set_error(std::string msg);
    /**
     * \brief increments the curr iterator
     * \author João Vitor Espig (JotaEspig)
     * \date 09 February, 2024
     * \version 09 February, 2024
     **/
    void next();
    /**
     * \brief generates the AST according to the token_vec tokens
     * \author João Vitor Espig (JotaEspig)
     * \date 09 February, 2024
     * \version 09 February, 2024
     **/
    AST generate_ast();
    /**
     * \brief parses an expression
     * \author João Vitor Espig (JotaEspig)
     * \date 09 February, 2024
     * \version 09 February, 2024
     **/
    AST::node_ptr parse_expression();
    /**
     * \brief parses a term
     * \author João Vitor Espig (JotaEspig)
     * \date 09 February, 2024
     * \version 09 February, 2024
     **/
    AST::node_ptr parse_term();
    /**
     * \brief parses a factor
     * \author João Vitor Espig (JotaEspig)
     * \date 09 February, 2024
     * \version 09 February, 2024
     **/
    AST::node_ptr parse_factor();

private:
    /** tokens vector **/
    token_vec _tokens;
    /**  begin iterator **/
    token_vec::iterator _begin;
    /**  end iterator **/
    token_vec::iterator _end;
    /** curr iterator **/
    token_vec::iterator _curr;
};

} // namespace logic
