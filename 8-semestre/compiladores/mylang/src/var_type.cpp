#include "var_type.hpp"

std::string to_string(VarType type) {
    switch (type) {
    case VarType::INT:
        return "int";
    case VarType::FLOAT:
        return "float";
    default:
        return "unknown";
    }
}
