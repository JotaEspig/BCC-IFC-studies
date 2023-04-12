#pragma once

#include <cstdint>

namespace chess
{
    class Piece
    {
    protected:
        bool isWhite;

    public:
        Piece(bool isWhite);
        ~Piece();
        bool isMovePossible(uint8_t rank, uint8_t file,
                            uint8_t rankTarget, uint8_t fileTarget);
    };
} // namespace chess
