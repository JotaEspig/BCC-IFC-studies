#pragma once

#include <unordered_map>

#include "var.hpp"
#include "var_id.hpp"

struct Context {
    std::unordered_map<VarId, Var> variables;
    int next_id = 0;
};
