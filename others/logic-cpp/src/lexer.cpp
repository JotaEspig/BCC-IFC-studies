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
    char curr_ch = curr_char();
    while (curr_ch != 0)
    {
        // jumps space characters
        if (curr_ch == ' ')
        {
            next();
            curr_ch = curr_char();
            continue;
        }

        Token t;
        bool need_next = true;
        if (curr_ch == '-' || curr_ch == 'v' || curr_ch == '&'
            || curr_ch == '<')
        {
            t = read_operator();
            // prevents a syntax error to stop the lexer
            if (t.type != Token::Type::UNKNOWN)
                need_next = false;
        }
        else if (std::isalpha(curr_ch))
        {
            t = read_bool();
            if (t.type == Token::Type::UNKNOWN)
                t = read_variable();

            // prevents a syntax error to stop the lexer
            if (t.type != Token::Type::UNKNOWN)
                need_next = false;
        }
        else if (curr_ch == '(' || curr_ch == ')')
        {
            t = Token{{curr_ch}, Token::Type::PARENTHESIS};
        }
        else
            t.value = {curr_ch};

        if (need_next)
            next();
        curr_ch = curr_char();

        tokens.push_back(t);
    }
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
    if (curr_ch == 0 || !isupper(curr_ch))
        return token;

    token.type = Token::Type::VARIABLE;
    while (curr_ch != 0 && isupper(curr_ch))
    {
        token.value += curr_ch;
        next();
        curr_ch = curr_char();
    }
    return token;
}

Token Lexer::read_operator()
{
    Token token;
    char curr_ch = curr_char();
    if (curr_ch == '&' || curr_ch == 'v')
    {
        token = Token({curr_ch}, Token::Type::OPERATOR);
        next();
    }
    else if (curr_ch == '<')
    {
        if (_curr + 2 < _end && *(_curr + 1) == '-' && *(_curr + 2) == '>')
        {
            token = Token{"<->", Token::Type::OPERATOR};
            _curr += 3;
        }
    }
    else if (curr_ch == '-')
    {
        if (_curr + 1 < _end && *(_curr + 1) == '>')
        {
            token = Token{"->", Token::Type::OPERATOR};
            _curr += 2;
        }
        else
        {
            token = Token{"-", Token::Type::OPERATOR};
            next();
        }
    }

    return token;
}

} // namespace logic
