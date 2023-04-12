#pragma once

#include <cstdint>

#include "../piece.hpp"

namespace chess
{
    class Pawn : public Piece
    {
    private:
    public:
        Pawn(bool isWhite);
        ~Pawn();
        bool isMovePossible(uint8_t rank, uint8_t file,
                            uint8_t rankTarget, uint8_t fileTarget);
    };
} // namespace chess
