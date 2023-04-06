#pragma once

#include <vector>

#include "../pieces/pieces.hpp"
#include "move.hpp"

namespace chess
{
    class Board
    {
    private:
        Position pos;
        std::vector<chess::Move> *moves;

    public:
        Board();
        ~Board();
        bool doMove(chess::Move move);
    };
} // namespace chess
