#pragma once

#include <vector>

#include "../pieces/piece.hpp"
#include "../pieces/pieces.hpp"
#include "move.hpp"

namespace chess
{
    class Board
    {
    private:
        Position pos;
        std::vector<Move> *moves;

        Piece *getPieceByEnum(Pieces pieceEnum);
        bool checkEnPassant(Move, Piece *piece);

    public:
        Board();
        ~Board();

        bool doMove(Move move);
    };
} // namespace chess
