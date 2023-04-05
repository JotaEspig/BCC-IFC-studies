#include <algorithm>

#include "board.hpp"
#include "../pieces/pieces.hpp"

using namespace chess;

Position initialPosition = {
    // 8 rank
    {Pieces::BlackRook, Pieces::BlackKnight, Pieces::BlackBishop, Pieces::BlackQueen,
     Pieces::BlackKing, Pieces::BlackBishop, Pieces::BlackKnight, Pieces::BlackRook},
    // 7 rank
    {Pieces::BlackPawn, Pieces::BlackPawn, Pieces::BlackPawn, Pieces::BlackPawn,
     Pieces::BlackPawn, Pieces::BlackPawn, Pieces::BlackPawn, Pieces::BlackPawn},
    // 6 rank
    {Pieces::Blank, Pieces::Blank, Pieces::Blank, Pieces::Blank, Pieces::Blank,
     Pieces::Blank, Pieces::Blank, Pieces::Blank},
    // 5 rank
    {Pieces::Blank, Pieces::Blank, Pieces::Blank, Pieces::Blank, Pieces::Blank,
     Pieces::Blank, Pieces::Blank, Pieces::Blank},
    // 4 rank
    {Pieces::Blank, Pieces::Blank, Pieces::Blank, Pieces::Blank, Pieces::Blank,
     Pieces::Blank, Pieces::Blank, Pieces::Blank},
    // 3 rank
    {Pieces::Blank, Pieces::Blank, Pieces::Blank, Pieces::Blank, Pieces::Blank,
     Pieces::Blank, Pieces::Blank, Pieces::Blank},
    // 2 rank
    {Pieces::WhitePawn, Pieces::WhitePawn, Pieces::WhitePawn, Pieces::WhitePawn,
     Pieces::WhitePawn, Pieces::WhitePawn, Pieces::WhitePawn, Pieces::WhitePawn},
    // 1 rank
    {Pieces::WhiteRook, Pieces::WhiteKnight, Pieces::WhiteBishop, Pieces::WhiteQueen,
     Pieces::WhiteKing, Pieces::WhiteBishop, Pieces::WhiteKnight, Pieces::WhiteRook}};

Board::Board()
{
    std::copy(&initialPosition[0][0], &initialPosition[0][0] + 8 * 8, &pos[0][0]);
}

Board::~Board()
{
}
