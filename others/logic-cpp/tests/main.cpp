#include <iostream>

#include "logic/greetings.hpp"
#include "logic/lexer.hpp"
#include "logic/token.hpp"

int main()
{
    std::cout << "Fuck\n";
    logic::greetings();

    std::string fuck = "true    fuck 123hel lo";
    logic::Lexer lex{fuck};

    while (lex.curr() < lex.end())
    {
        logic::Token t = lex.read_bool();
        if (t.type != logic::Token::Type::UNKNOWN)
        {
            std::cout << t.value << std::endl;
            continue;
        }

        t = lex.read_variable();
        if (t.type != logic::Token::Type::UNKNOWN)
            std::cout << t.value << std::endl;
        else
            lex.next();
    }
    return 0;
}
