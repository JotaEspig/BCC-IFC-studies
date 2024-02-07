#include <iostream>

#include "logic/greetings.hpp"
#include "logic/lexer.hpp"
#include "logic/parser.hpp"
#include "logic/token.hpp"

int main()
{
    logic::greetings();
    std::cout << std::endl;

    std::string a{{'&', 0}};
    std::cout << (a == "&") << std::endl;
    std::string fuck = "Q & R";
    logic::Lexer lex{fuck};

    auto tokens = lex.generate_tokens();
    auto parser = logic::Parser{tokens};
    auto ast = parser.generate_ast();
    std::cout << ast << std::endl;
    std::cout << parser.error << std::endl;
    return 0;
}
