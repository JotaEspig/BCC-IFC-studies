#include "board.hpp"
#include <algorithm>

using namespace chess;

Board::Board(){
    copy(pos, initialPosition)}

Board::~Board()
{
}

Positions initialPosition = {
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
