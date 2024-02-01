/**
 * \file expr.hpp
 * \brief Symbol and SymbolNode classes
 * \author João Vitor Espig (JotaEspig)
 * \date February 01, 2024
 * \version February 01, 2024
 **/
#pragma once

#include <memory>
#include <ostream>

#include "mathexpr/symbol.hpp"

namespace mathexpr
{

/**
 * \brief Represents a math expression
 * \author João Vitor Espig (JotaEspig)
 * \date February 01, 2024
 * \version February 01, 2024
 **/
class Expr
{
public:
    /** pointer to root of the tree **/
    std::unique_ptr<SymbolNode> root = nullptr;

    /**
     * \brief Expr constructor
     * \author João Vitor Espig (JotaEspig)
     * \date February 01, 2024
     * \version February 01, 2024
     **/
    Expr();
    /**
     * \brief Expr constructor
     * \author João Vitor Espig (JotaEspig)
     * \date February 01, 2024
     * \version February 01, 2024
     * \param node - pointer to Node
     **/
    Expr(std::unique_ptr<SymbolNode> &&node);

    /**
     * \brief evals the expression
     * \author João Vitor Espig (JotaEspig)
     * \date February 01, 2024
     * \version February 01, 2024
     * \param sym - Symbol object of type VARIABLE
     * \param value - Value that will replace symbol
     **/
    double eval(const Symbol &sym, double value) const;

    /**
     * \brief Expr << operator overload
     * \author João Vitor Espig (JotaEspig)
     * \date February 01, 2024
     * \version February 01, 2024
     * \param os - ostream object
     * \param expr - Expr object
     **/
    friend std::ostream &operator<<(std::ostream &os, const Expr &expr);

private:
    /**
     * \brief evals the expression
     * \author João Vitor Espig (JotaEspig)
     * \date February 01, 2024
     * \version February 01, 2024
     * \param node - pointer to node
     * \param sym - Symbol object of type VARIABLE
     * \param value - Value that will replace symbol
     **/
    double eval_nodes(
        const std::unique_ptr<SymbolNode> &node, const Symbol &sym, double value
    ) const;
};

} // namespace mathexpr
