#pragma once

#include <cstdint>

namespace chess
{
    enum class ResultCode : uint8_t
    {
        Invalid,
        Normal,
        Capture,
        SpecialMove
    };

    class Piece
    {
    protected:
        bool isWhite;

    public:
        Piece(bool isWhite);
        virtual ~Piece();
        /**
         * @brief
            Checks if move is possible, but doesn't take the other pieces into
            consideration.
            e.g. it does not check if capture is really possible
         *
         * @param rank
         * @param file
         * @param rankTarget
         * @param fileTarget
         * @return uint8_t 1: (normal move) 2 (capture) 3 (especial move)
         */
        virtual ResultCode isMovePossible(uint8_t file, uint8_t rank,
                                          uint8_t fileTarget, uint8_t rankTarget);
    };
} // namespace chess
