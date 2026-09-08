#pragma once

#include "var_type.hpp"
#include <string>
#include <variant>

enum Token {
    LBRACE = 253,
    RBRACE = 252,
    VAR_TYPE = 254,
    WORD = 255,
    NUMBER = 256,
};

using TokenVal = std::variant<int, std::string, VarType>;
