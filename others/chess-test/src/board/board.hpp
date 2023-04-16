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
        std::vector<chess::Move> *moves;

        Piece *getPieceByEnum(Pieces pieceEnum);

    public:
        Board();
        ~Board();

        bool doMove(chess::Move move);
    };
} // namespace chess
