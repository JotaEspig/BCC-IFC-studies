#include "logic/lexer.hpp"

namespace logic
{

Lexer::Lexer()
{
}

Lexer::Lexer(const string_it &begin, const string_it &end)
{
    _begin = begin;
    _end = end;
    _curr = begin;
}

inline Lexer::string_it Lexer::begin() const
{
    return _begin;
}

inline Lexer::string_it Lexer::end() const
{
    return _end;
}

inline Lexer::string_it Lexer::curr() const
{
    return _curr;
}

inline void Lexer::next()
{
    ++_curr;
}

} // namespace logic
