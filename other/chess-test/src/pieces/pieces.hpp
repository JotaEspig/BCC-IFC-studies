#pragma once

namespace chess
{
    enum class Pieces : u_int8_t
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
