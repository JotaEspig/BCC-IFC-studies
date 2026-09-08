#pragma once

#include <string>
#include <variant>

enum Token {
    VAR_TYPE = 254,
    WORD = 255,
    NUMBER = 256,
};

using TokenVal = std::variant<int, std::string>;
