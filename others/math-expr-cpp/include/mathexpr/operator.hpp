#pragma once

#include <memory>

#include "mathexpr/symbol.hpp"

namespace mathexpr
{

/**
 * \brief Interface that represents a binary or an unary operator
 * \author João Vitor Espig (JotaEspig)
 * \date February 02, 2024
 * \version February 02, 2024
 **/
class Operator
{
public:
    /**
     * \brief Do the operation and return the expected value
     * \author João Vitor Espig (JotaEspig)
     * \date February 02, 2024
     * \version February 02, 2024
     *
     * Works for binary or unary operators, the classes that inherit from this
     * should handle itself
     **/
    virtual double get_value(double left, double right) = 0;
};

class Addition : public Operator
{
public:
    Addition();

    double get_value(double left, double right) override;
};

class Subtraction : public Operator
{
public:
    Subtraction();

    double get_value(double left, double right) override;
};

class Multiplication : public Operator
{
public:
    Multiplication();

    double get_value(double left, double right) override;
};

class Division : public Operator
{
public:
    Division();

    double get_value(double left, double right) override;
};

/**
 * \brief Class that creates an object that implements Operator
 * \author João Vitor Espig (JotaEspig)
 * \date February 02, 2024
 * \version February 02, 2024
 **/
class OperatorFactory
{
public:
    /**
     * \brief Creates an operator
     * \author João Vitor Espig (JotaEspig)
     * \date February 02, 2024
     * \version February 02, 2024
     *
     * It reads the symbol and detects which operator should be made
     **/
    static std::unique_ptr<Operator> create(const Symbol &sym);
};

} // namespace mathexpr
