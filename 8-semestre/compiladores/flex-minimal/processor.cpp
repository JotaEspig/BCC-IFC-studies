#include <iostream>

#include "scanner.hpp"

class Parser {
public:
    explicit Parser(Scanner &scanner) : scanner(scanner) {}

    void run() {
        advance();
        while (token != 0) {
            int result = expr();
            std::cout << result << "\n";
            if (token == '\n') advance();
        }
    }

private:
    Scanner &scanner;
    int token = 0;
    TokenVal tokenval;

    void advance() {
        token = scanner.yylex();
        tokenval = scanner.yylval;
    }

    int factor() {
        int v;
        if (token == NUMBER) {
            v = std::get<int>(tokenval);
            advance();
        } else if (token == '(') {
            advance();
            v = expr();
            if (token == ')') advance();
        } else {
            v = 0;
        }
        return v;
    }

    int term() {
        int v = factor();
        while (token == '*' || token == '/') {
            int op = token;
            advance();
            int v2 = factor();
            v = (op == '*') ? v * v2 : v / v2;
        }
        return v;
    }

    int expr() {
        int v = term();
        while (token == '+' || token == '-') {
            int op = token;
            advance();
            int v2 = term();
            v = (op == '+') ? v + v2 : v - v2;
        }
        return v;
    }
};

int main() {
    Scanner scanner;
    Parser parser(scanner);
    parser.run();
    return 0;
}
