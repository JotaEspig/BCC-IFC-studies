#pragma once

#include <cstdint>

#include "../pieces/pieces.hpp"

namespace chess
{
    struct Move
    {
        Pieces piece;
        uint8_t rank;
        uint8_t file;
        uint8_t rankTarget;
        uint8_t fileTarget;

        Move(Pieces piece, uint8_t rank, uint8_t file,
             uint8_t rankTarget, uint8_t fileTarget);
        ~Move();
    };

} // namespace chess
