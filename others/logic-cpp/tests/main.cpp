#include <iostream>

#include "logic/greetings.hpp"
#include "logic/lexer.hpp"
#include "logic/parser.hpp"

int main()
{
    logic::greetings();
    std::cout << std::endl;

    std::string str;
    while (std::getline(std::cin, str))
    {
        logic::Lexer lex{str};
        auto tokens = lex.generate_tokens();

        auto parser = logic::Parser{tokens};
        auto ast = parser.generate_ast();
        std::cout << ast << std::endl;
        std::cout << parser.error << std::endl;
    }
    return 0;
}
