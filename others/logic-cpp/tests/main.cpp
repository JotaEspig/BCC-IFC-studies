#include <iostream>

#include "logic/greetings.hpp"
#include "logic/lexer.hpp"
#include "logic/parser.hpp"

int main()
{
    logic::greetings();
    std::cout << std::endl;

    std::string str;
    std::cout << "Expression: ";
    while (std::getline(std::cin, str))
    {
        logic::Lexer lex{str};
        auto tokens = lex.generate_tokens();

        logic::Parser parser{tokens};
        auto ast = parser.generate_ast();
        std::cout << str << " - " << ast << std::endl;
        std::cout << parser.error << std::endl;

        std::cout << "Expression: ";
    }
    return 0;
}
