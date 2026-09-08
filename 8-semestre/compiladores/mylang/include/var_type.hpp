#pragma once

#include <string>

enum VarType { INT, FLOAT, UNKNOWN };

std::string to_string(VarType type);
