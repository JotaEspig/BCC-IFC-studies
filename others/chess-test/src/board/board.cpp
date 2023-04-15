#include "board.hpp"

#include <algorithm>

#include "../pieces/piece.hpp"
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
    uint8_t file = move.file;
    uint8_t rank = move.rank;
    uint8_t fileT = move.fileTarget;
    uint8_t rankT = move.rankTarget;

    Piece *piece = getPieceByEnum(move.piece);
    if (piece == nullptr)
        return false;

    ResultCode resultCode = piece->isMovePossible(file, rank, fileT, rankT);
    if (resultCode == ResultCode::Invalid)
        return false;
    if (resultCode == ResultCode::PawnCapture)
    {
        if (pos[rankT - 1][fileT - 1] == Pieces::Blank)
            return false;
    }

    // It must decrement to be compatible with the array.
    // since the array go from 0 to 7 and a real board
    // go from 1 to 8 in both rank and file (rows and columns at array [r][c])
    file--;
    rank--;
    fileT--;
    rankT--;
    std::swap(pos[rank][file],
              pos[rankT][fileT]);
    moves->push_back(move);

    delete piece;
    return true;
}

Piece *Board::getPieceByEnum(Pieces pieceEnum)
{
    switch (pieceEnum)
    {
    case Pieces::BlackPawn:
        return new Pawn(false);
    case Pieces::WhitePawn:
        return new Pawn(true);
    }

    return nullptr;
}
