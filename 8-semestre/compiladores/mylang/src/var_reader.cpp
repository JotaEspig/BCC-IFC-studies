#include <iostream>

#include "context.hpp"
#include "scanner.hpp"
#include "tokens.hpp"
#include "var_type.hpp"

void print_vars(const Context &context) {
    for (const auto &[id, var] : context.variables) {
        std::cout << to_string(var.type) << " " << var.name << "\n";
    }
}

void read_var(Scanner &scanner) {
    const std::string &name = std::get<std::string>(scanner.yylval);
    scanner.context.variables[VarId{scanner.context.next_id++, 0}]
        = Var{VarType::UNKNOWN, name};
}

void read_vars(Scanner &scanner) {
    int token;
    while ((token = scanner.yylex()) != 0) {
        if (token == WORD) {
            read_var(scanner);
        }
    }
}

int main() {
    Context context;
    Scanner scanner(context);
    read_vars(scanner);
    print_vars(context);
    return 0;
}
