#include "board.hpp"

#include <algorithm>

#include "../pieces/pieces.hpp"
#include "../pieces/pawn/pawn.hpp"

using namespace chess;

Position initialPosition = {
    // 1st rank
    {Pieces::WhiteRook, Pieces::WhiteKnight, Pieces::WhiteBishop, Pieces::WhiteQueen,
     Pieces::WhiteKing, Pieces::WhiteBishop, Pieces::WhiteKnight, Pieces::WhiteRook},
    // 2nd rank
    {Pieces::WhitePawn, Pieces::WhitePawn, Pieces::WhitePawn, Pieces::WhitePawn,
     Pieces::WhitePawn, Pieces::WhitePawn, Pieces::WhitePawn, Pieces::WhitePawn},
    // 3th rank
    {Pieces::Blank, Pieces::Blank, Pieces::Blank, Pieces::Blank, Pieces::Blank,
     Pieces::Blank, Pieces::Blank, Pieces::Blank},
    // 4th rank
    {Pieces::Blank, Pieces::Blank, Pieces::Blank, Pieces::Blank, Pieces::Blank,
     Pieces::Blank, Pieces::Blank, Pieces::Blank},
    // 5th rank
    {Pieces::Blank, Pieces::Blank, Pieces::Blank, Pieces::Blank, Pieces::Blank,
     Pieces::Blank, Pieces::Blank, Pieces::Blank},
    // 6th rank
    {Pieces::Blank, Pieces::Blank, Pieces::Blank, Pieces::Blank, Pieces::Blank,
     Pieces::Blank, Pieces::Blank, Pieces::Blank},
    // 7th rank
    {Pieces::BlackPawn, Pieces::BlackPawn, Pieces::BlackPawn, Pieces::BlackPawn,
     Pieces::BlackPawn, Pieces::BlackPawn, Pieces::BlackPawn, Pieces::BlackPawn},
    // 8th rank
    {Pieces::BlackRook, Pieces::BlackKnight, Pieces::BlackBishop, Pieces::BlackQueen,
     Pieces::BlackKing, Pieces::BlackBishop, Pieces::BlackKnight, Pieces::BlackRook}};

Board::Board()
{
    std::copy(&initialPosition[0][0], &initialPosition[0][0] + 8 * 8, &pos[0][0]);
    moves = new std::vector<Move>();
}

Board::~Board()
{
    moves->clear();
    delete moves;
}

bool Board::doMove(Move move)
{
    uint8_t rank = move.rank;
    uint8_t file = move.file;
    uint8_t rankT = move.rankTarget;
    uint8_t fileT = move.fileTarget;

    Piece *piece;
    // TODO Resolve bug where switch case calls destructor of pawn
    switch (move.piece)
    {
    case Pieces::BlackPawn:
    {
        auto pawn = Pawn(false);
        piece = &pawn;
        break;
    }
    case Pieces::WhitePawn:
    {
        auto pawn = Pawn(true);
        piece = &pawn;
        break;
    }
    default:
        break;
    }

    if (!piece->isMovePossible(rank, file, rankT, fileT))
        return false;

    // It must decrement to be compatible with the array.
    // since the array go from 0 to 7 and a real board
    // go from 1 to 8 in both rank and file (rows and columns at array [r][c])
    rank--;
    file--;
    rankT--;
    fileT--;
    std::swap(pos[rank][file],
              pos[rankT][fileT]);
    moves->push_back(move);

    return true;
}
