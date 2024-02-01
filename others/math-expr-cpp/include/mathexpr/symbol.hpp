/**
 * \file symbol.hpp
 * \brief Symbol and SymbolNode classes
 * \author João Vitor Espig (JotaEspig)
 * \date February 01, 2024
 * \version February 01, 2024
 **/
#pragma once

#include <memory>
#include <string>

/*
 * C++ is a real piece of shit
 * */

namespace mathexpr
{

class SymbolNode;

/**
 * \brief Represents a math symbol, it can be a operator, number or variable
 * \author João Vitor Espig (JotaEspig)
 * \date February 01, 2024
 * \version February 01, 2024
 **/
class Symbol
{
public:
    /**
     * \brief Symbol enum class
     * \author João Vitor Espig (JotaEspig)
     * \date February 01, 2024
     * \version February 01, 2024
     **/
    enum class Type
    {
        VARIABLE,
        NUMBER,
        OPERATOR,
        INVALID
    };

    /** Symbol ID **/
    std::string id = "";
    /** Symbol value if it's a number **/
    double value = 0;
    /** Symbol type **/
    Type type = Type::INVALID;

    /**
     * \brief Symbol constructor
     * \author João Vitor Espig (JotaEspig)
     * \date February 01, 2024
     * \version February 01, 2024
     **/
    Symbol();
    /**
     * \brief Symbol constructor for NUMBER and VARIABLE
     * \author João Vitor Espig (JotaEspig)
     * \date February 01, 2024
     * \version February 01, 2024
     * \param id - Symbol ID
     **/
    Symbol(std::string id);
    /**
     * \brief Symbol constructor for NUMBER
     * \author João Vitor Espig (JotaEspig)
     * \date February 01, 2024
     * \version February 01, 2024
     * \param value - Symbol value
     **/
    Symbol(double value);

    /**
     * \brief Symbol + operator overload
     * \author João Vitor Espig (JotaEspig)
     * \date February 01, 2024
     * \version February 01, 2024
     * \param sym - Symbol
     * \param value - value
     **/
    friend std::unique_ptr<SymbolNode>
    operator+(const Symbol &sym, double value);
    /**
     * \brief Symbol + operator overload (allows commutativity)
     * \author João Vitor Espig (JotaEspig)
     * \date February 01, 2024
     * \version February 01, 2024
     * \param value - value
     * \param sym - Symbol
     **/
    friend std::unique_ptr<SymbolNode>
    operator+(double value, const Symbol &sym);

    /**
     * \brief Symbol << operator overload
     * \author João Vitor Espig (JotaEspig)
     * \date February 01, 2024
     * \version February 01, 2024
     * \param os - ostream
     * \param sym - Symbol
     **/
    friend std::ostream &operator<<(std::ostream &os, const Symbol &sym);
};

/**
 * \brief SymbolNode class
 * \author João Vitor Espig (JotaEspig)
 * \date February 01, 2024
 * \version February 01, 2024
 **/
class SymbolNode
{
public:
    /** Symbol object **/
    Symbol sym;
    /** ptr to left Symbol **/
    std::unique_ptr<SymbolNode> left = nullptr;
    /** ptr to right Symbol **/
    std::unique_ptr<SymbolNode> right = nullptr;

    /**
     * \brief SymbolNode constructor
     * \author João Vitor Espig (JotaEspig)
     * \date February 01, 2024
     * \version February 01, 2024
     **/
    SymbolNode();
    /**
     * \brief SymbolNode constructor
     * \author João Vitor Espig (JotaEspig)
     * \date February 01, 2024
     * \version February 01, 2024
     * \param symbol - Symbol
     **/
    SymbolNode(Symbol symbol);
    /**
     * \brief create a pointer to Symbol
     * \author João Vitor Espig (JotaEspig)
     * \date February 01, 2024
     * \version February 01, 2024
     * \param symbol - Symbol
     **/
    static std::unique_ptr<SymbolNode> create_node(Symbol symbol = Symbol{});

    /**
     * \brief SymbolNode + operator overload
     * \author João Vitor Espig (JotaEspig)
     * \date February 01, 2024
     * \version February 01, 2024
     * \param node - pointer to SymbolNode
     * \param value - value
     **/
    friend std::unique_ptr<SymbolNode>
    operator+(std::unique_ptr<SymbolNode> node, double value);
    /**
     * \brief SymbolNode + operator overload (allows commutativity)
     * \author João Vitor Espig (JotaEspig)
     * \date February 01, 2024
     * \version February 01, 2024
     * \param value - value
     * \param node - pointer to SymbolNode
     **/
    friend std::unique_ptr<SymbolNode>
    operator+(double value, std::unique_ptr<SymbolNode> node);

    /**
     * \brief SymbolNode << operator overload
     * \author João Vitor Espig (JotaEspig)
     * \date February 01, 2024
     * \version February 01, 2024
     * \param os - ostream object
     * \param node - SymbolNode object
     **/
    friend std::ostream &operator<<(std::ostream &os, const SymbolNode &node);
    /**
     * \brief SymbolNode << operator overload
     * \author João Vitor Espig (JotaEspig)
     * \date February 01, 2024
     * \version February 01, 2024
     * \param os - ostream object
     * \param node - pointer to SymbolNode
     **/
    friend std::ostream &
    operator<<(std::ostream &os, const std::unique_ptr<SymbolNode> &node);
};

} // namespace mathexpr
