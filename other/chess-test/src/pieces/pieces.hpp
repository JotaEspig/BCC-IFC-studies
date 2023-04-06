#pragma once

#include <cstdint>

namespace chess
{
    enum class Pieces : uint8_t
    {
        Blank,
        BlackKing,
        BlackQueen,
        BlackRook,
        BlackBishop,
        BlackKnight,
        BlackPawn,
        WhiteKing,
        WhiteQueen,
        WhiteRook,
        WhiteBishop,
        WhiteKnight,
        WhitePawn
    };
    typedef enum Pieces Position[8][8];
} // namespace chess
