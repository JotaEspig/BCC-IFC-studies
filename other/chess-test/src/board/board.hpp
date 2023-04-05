#pragma once

#include "../pieces/pieces.hpp"

namespace chess
{
    class Board
    {
    private:
        Position pos;

    public:
        Board();
        ~Board();
    };
} // namespace chess
