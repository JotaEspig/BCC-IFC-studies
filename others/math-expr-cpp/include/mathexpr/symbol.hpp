#pragma once

#include <memory>
#include <string>

/*
 * C++ is a real piece of shit
 * */

namespace mathexpr
{

// Previous declaration because of operators overloads in Symbol class
class SymbolNode;

class Symbol
{
public:
    enum class Type
    {
        VARIABLE,
        NUMBER,
        OPERATOR,
        INVALID
    };

    std::string id = "";
    double value = 0;
    Type type = Type::INVALID;

    Symbol();
    Symbol(std::string id);
    Symbol(double value);

    friend std::unique_ptr<SymbolNode>
    operator+(const Symbol &sym, double value);
    friend std::unique_ptr<SymbolNode>
    operator+(double value, const Symbol &sym);

    friend std::ostream &operator<<(std::ostream &os, const Symbol &sym);
};

// Symbol operators commutative

class SymbolNode
{
public:
    Symbol sym;
    std::unique_ptr<SymbolNode> left = nullptr;
    std::unique_ptr<SymbolNode> right = nullptr;

    SymbolNode();
    SymbolNode(Symbol symbol);
    static std::unique_ptr<SymbolNode> create_node(Symbol symbol = Symbol{});

    friend std::unique_ptr<SymbolNode>
    operator+(std::unique_ptr<SymbolNode> node, double value);
    friend std::unique_ptr<SymbolNode>
    operator+(double value, std::unique_ptr<SymbolNode> node);

    friend std::ostream &operator<<(std::ostream &os, const SymbolNode &node);
    friend std::ostream &
    operator<<(std::ostream &os, const std::unique_ptr<SymbolNode> &node);
};

} // namespace mathexpr
