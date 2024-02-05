/**
 * \file Token definitions
 * \author João Vitor Espig (JotaEspig)
 * \date 04 February, 2024
 * \version 04 February, 2024
 **/
#pragma once

#include <string>

namespace logic
{

/**
 * \brief Token
 * \author João Vitor Espig (JotaEspig)
 * \date 04 February, 2024
 * \version 04 February, 2024
 **/
struct Token
{
    /**
     * \brief Token Type
     * \author João Vitor Espig (JotaEspig)
     * \date 04 February, 2024
     * \version 04 February, 2024
     **/
    enum class Type
    {
        UNKNOWN,
        OPERATOR,
        BOOL,
        VARIABLE,
        PARENTHESIS
    };

    std::string value;
    Type type = Type::UNKNOWN;

    Token();
    Token(Type type);
    Token(std::string value, Type type);
};

} // namespace logic
