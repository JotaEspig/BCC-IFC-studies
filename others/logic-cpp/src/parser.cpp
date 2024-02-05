#include <vector>

#include "logic/parser.hpp"
#include "logic/token.hpp"

namespace logic
{

Parser::Parser()
{
}

Parser::Parser(const std::vector<Token> &tokens) :
    tokens{tokens}
{
}

} // namespace logic
