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

std::unique_ptr<Operator> OperatorFactory::create(const Symbol &sym)
{
    std::unique_ptr<Operator> op;
    if (sym.id == "+")
        op = std::make_unique<Addition>();

    return op;
}

} // namespace mathexpr
