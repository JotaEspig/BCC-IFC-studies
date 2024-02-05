#include <iostream>

#include "logic/greetings.hpp"
#include "logic/lexer.hpp"
#include "logic/token.hpp"

int main()
{
    logic::greetings();
    std::cout << std::endl;

    std::string fuck = "Q & R  <-> (S -> T)";
    logic::Lexer lex{fuck};

    auto tokens = lex.generate_tokens();
    for (auto &t : tokens)
    {
        if (t.type != logic::Token::Type::UNKNOWN)
            std::cout << t.value << std::endl;
        else
            std::cout << t.value << " is INVALID" << std::endl;
    }
    return 0;
}
