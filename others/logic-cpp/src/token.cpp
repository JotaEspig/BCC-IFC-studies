#include "logic/token.hpp"

namespace logic
{

Token::Token()
{
}

Token::Token(Type type) :
    type{type}
{
}

Token::Token(std::string value, Type type) :
    value{value},
    type{type}
{
}

} // namespace logic
