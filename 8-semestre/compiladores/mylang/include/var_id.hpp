#pragma once

#include <cstddef>
#include <functional>

struct VarId {
    int id, ref_id;

    bool operator==(const VarId &other) const {
        return id == other.id && ref_id == other.ref_id;
    }
};

namespace std {
template <>
struct hash<VarId> {
    std::size_t operator()(const VarId &k) const {
        return std::hash<int>()(k.id) ^ std::hash<int>()(k.ref_id);
    }
};
}
