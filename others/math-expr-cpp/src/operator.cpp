#include <memory>

#include "mathexpr/operator.hpp"

namespace mathexpr
{

Addition::Addition()
{
}

double Addition::get_value(double left, double right)
{
    return left + right;
}

Subtraction::Subtraction()
{
}

double Subtraction::get_value(double left, double right)
{
    return left - right;
}

Multiplication::Multiplication()
{
}

double Multiplication::get_value(double left, double right)
{
    return left * right;
}

Division::Division()
{
}

double Division::get_value(double left, double right)
{
    return left / right;
}

std::unique_ptr<Operator> OperatorFactory::create(const Symbol &sym)
{
    std::unique_ptr<Operator> op;
    if (sym.id == "+")
        op = std::make_unique<Addition>();
    else if (sym.id == "-")
        op = std::make_unique<Subtraction>();
    else if (sym.id == "*")
        op = std::make_unique<Multiplication>();
    else if (sym.id == "/")
        op = std::make_unique<Division>();

    return op;
}

} // namespace mathexpr
