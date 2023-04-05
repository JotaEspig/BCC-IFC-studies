#pragma once

namespace chess
{
    typedef enum Pieces Positions[8][8];

    class Board
    {
    private:
        Positions pos;

    public:
        Board(/* args */);
        ~Board();
    };

    enum class Pieces
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

    extern Positions initialPosition;
} // namespace chess
