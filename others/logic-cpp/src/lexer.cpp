#include <cctype>
#include <vector>

#include "logic/lexer.hpp"
#include "logic/token.hpp"

namespace logic
{

Lexer::Lexer()
{
}

Lexer::Lexer(std::string &string) :
    Lexer{string.begin(), string.end()}
{
}

Lexer::Lexer(const string_it &begin, const string_it &end) :
    _begin{begin},
    _end{end},
    _curr{begin}
{
}

Lexer::string_it Lexer::begin() const
{
    return _begin;
}

Lexer::string_it Lexer::end() const
{
    return _end;
}

Lexer::string_it Lexer::curr() const
{
    return _curr;
}

char Lexer::curr_char() const
{
    return _curr < _end ? *_curr : 0;
}

void Lexer::next()
{
    ++_curr;
}

std::vector<Token> Lexer::generate_tokens()
{
    std::vector<Token> tokens;
    return tokens;
}

Token Lexer::read_bool()
{
    Token token;
    std::string first_4letters{_curr, _curr + 4};
    if (first_4letters == "true" || first_4letters == "false")
    {
        token.type = Token::Type::BOOL;
        token.value = first_4letters;
        _curr += 4;
    }
    return token;
}

Token Lexer::read_variable()
{
    Token token;
    char curr_ch = curr_char();
    if (curr_ch == 0 || !islower(curr_ch))
        return token;

    token.type = Token::Type::VARIABLE;
    while (curr_ch != 0 && islower(curr_ch))
    {
        token.value += curr_ch;
        next();
        curr_ch = curr_char();
    }
    return token;
}

} // namespace logic
