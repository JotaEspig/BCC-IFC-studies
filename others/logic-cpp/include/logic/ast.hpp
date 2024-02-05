/**
 * \file AST operations
 * \author João Vitor Espig (JotaEspig)
 * \date 05 February, 2024
 * \version 05 February, 2024
 **/
#pragma once

#include <memory>

#include "logic/token.hpp"

namespace logic
{

struct AST
{
    struct Node
    {
        Token value;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;

        Node();
        Node(const Token &token);
    };

    std::unique_ptr<Node> root;

    AST();
};

} // namespace logic;
