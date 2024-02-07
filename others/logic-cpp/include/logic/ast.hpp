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

/**
 * \brief Represents an AST of Tokens
 * \author João Vitor Espig (JotaEspig)
 * \date 07 February, 2024
 * \version 07 February, 2024
 **/
struct AST
{
    /**
     * \brief Represents a node of the AST of Tokens
     * \author João Vitor Espig (JotaEspig)
     * \date 07 February, 2024
     * \version 07 February, 2024
     **/
    struct Node
    {
        /** Node value **/
        Token value;
        /** Left Node **/
        std::unique_ptr<Node> left;
        /** Right Node **/
        std::unique_ptr<Node> right;

        /**
         * \brief Node constructor
         * \author João Vitor Espig (JotaEspig)
         * \date 07 February, 2024
         * \version 07 February, 2024
         **/
        Node();
        /**
         * \brief Node constructor
         * \author João Vitor Espig (JotaEspig)
         * \date 07 February, 2024
         * \version 07 February, 2024
         * \param token - const reference to token
         **/
        Node(const Token &token);
    };

    /** Root of the tree **/
    std::unique_ptr<Node> root;

    /**
     * \brief AST constructor
     * \author João Vitor Espig (JotaEspig)
     * \date 07 February, 2024
     * \version 07 February, 2024
     **/
    AST();
};

} // namespace logic;
