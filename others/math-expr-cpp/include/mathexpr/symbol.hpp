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
     * \brief Default Symbol constructor
     * \author João Vitor Espig (JotaEspig)
     * \date February 01, 2024
     * \version February 01, 2024
     *
     * It just create the object with default values:
     * id = ""
     * value = 0
     * type = Type::INVALID
     **/
    Symbol();
    /**
     * \brief Symbol constructor for VARIABLE or OPERATOR
     * \author João Vitor Espig (JotaEspig)
     * \date February 01, 2024
     * \version February 01, 2024
     * \param id - Symbol ID
     *
     * It initializes as a VARIABLE by default. So if you want the symbol to
     * represent an operator instead, you must reassign Symbol::type:
     * sym.type = Symbol::Type::OPERATOR
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
     *
     * It creates a small Tree, the root being a + Symbol, left = sym and
     * right = Symbol{value}
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
     *
     * It creates a small Tree, the root being a + Symbol, left = Symbol{value}
     * and right = sym
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
 * \brief Represents a node of a tree containing a Symbol object
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
     *
     * Left and right leaf starts as nullptr
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
     *
     * It creates a small Tree, the root being a + Symbol, left = node and
     * right = Symbol{value}.
     * It MOVES the pointer of node to the left leaf
     **/
    friend std::unique_ptr<SymbolNode>
    operator+(std::unique_ptr<SymbolNode> &node, double value);
    /**
     * \brief SymbolNode + operator overload (allows commutativity)
     * \author João Vitor Espig (JotaEspig)
     * \date February 01, 2024
     * \version February 01, 2024
     * \param value - value
     * \param node - pointer to SymbolNode
     *
     * It creates a small Tree, the root being a + Symbol, left = Symbol{value}
     * and right = node.
     * It MOVES the pointer of node to the right leaf
     **/
    friend std::unique_ptr<SymbolNode>
    operator+(double value, std::unique_ptr<SymbolNode> &node);

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
