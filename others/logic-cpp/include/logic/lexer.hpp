/**
 * \file Lexer operations
 * \author João Vitor Espig (JotaEspig)
 * \date 04 February, 2024
 * \version 04 February, 2024
 **/
#pragma once

#include <string>
#include <vector>

#include "logic/token.hpp"

namespace logic
{

/**
 * \brief Lexer
 * \author João Vitor Espig (JotaEspig)
 * \date 04 February, 2024
 * \version 04 February, 2024
 **/
class Lexer
{
    typedef std::string::iterator string_it;

public:
    /**
     * \brief Default Lexer constructor
     * \author João Vitor Espig (JotaEspig)
     * \date 04 February, 2024
     * \version 04 February, 2024
     **/
    Lexer();
    /**
     * \brief Lexer constructor
     * \author João Vitor Espig (JotaEspig)
     * \date 04 February, 2024
     * \version 04 February, 2024
     * \param string - string
     **/
    Lexer(std::string &string);
    /**
     * \brief Lexer constructor
     * \author João Vitor Espig (JotaEspig)
     * \date 04 February, 2024
     * \version 04 February, 2024
     * \param begin - string begin iterator
     * \param end - string end iterator
     **/
    Lexer(const string_it &begin, const string_it &end);

    /**
     * \brief member begin get
     * \author João Vitor Espig (JotaEspig)
     * \date 04 February, 2024
     * \version 04 February, 2024
     **/
    string_it begin() const;
    /**
     * \brief member end get
     * \author João Vitor Espig (JotaEspig)
     * \date 04 February, 2024
     * \version 04 February, 2024
     **/
    string_it end() const;
    /**
     * \brief member curr get
     * \author João Vitor Espig (JotaEspig)
     * \date 04 February, 2024
     * \version 04 February, 2024
     **/
    string_it curr() const;
    /**
     * \brief Gets current char in _curr iterator
     * \author João Vitor Espig (JotaEspig)
     * \date 05 February, 2024
     * \version 05 February, 2024
     **/
    char curr_char() const;
    /**
     * \brief Increase iterator at current position by one
     * \author João Vitor Espig (JotaEspig)
     * \date 04 February, 2024
     * \version 04 February, 2024
     **/
    void next();
    /**
     * \brief Generates a vector of tokens for the given string
     * \author João Vitor Espig (JotaEspig)
     * \date 05 February, 2024
     * \version 05 February, 2024
     **/
    std::vector<Token> generate_tokens();

    /**
     * \brief Reads a bool at given _curr iterator
     * \author João Vitor Espig (JotaEspig)
     * \date 05 February, 2024
     * \version 05 February, 2024
     *
     * It changes _curr iterator
     **/
    Token read_bool();
    /**
     * \brief Reads a variable at given _curr iterator
     * \author João Vitor Espig (JotaEspig)
     * \date 05 February, 2024
     * \version 05 February, 2024
     *
     * It changes _curr iterator
     **/
    Token read_variable();

private:
    string_it _begin;
    string_it _end;
    string_it _curr;
};

} // namespace logic
