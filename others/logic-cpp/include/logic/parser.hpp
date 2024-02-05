/**
 * \file Parser operations
 * \author João Vitor Espig (JotaEspig)
 * \date 05 February, 2024
 * \version 05 February, 2024
 **/
#pragma once

#include <vector>

#include "logic/ast.hpp"
#include "logic/token.hpp"

namespace logic
{

class Parser
{
public:
    std::vector<Token> tokens;

    Parser();
    Parser(const std::vector<Token> &tokens);
};

} // namespace logic
