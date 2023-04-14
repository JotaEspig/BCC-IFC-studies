#include "pawn.hpp"

#include <cstdint>

#include "../piece.hpp"

using namespace chess;

Pawn::Pawn(bool isWhite) : Piece(isWhite)
{
}

Pawn::~Pawn()
{
}

uint8_t Pawn::isMovePossible(uint8_t file, uint8_t rank,
                             uint8_t fileTarget, uint8_t rankTarget)
{
    if (!Piece::isMovePossible(rank, file, rankTarget, fileTarget))
        return false;

    // The code between line 24 and 29 checks if the pawn movement is correct
    // according to its color. The decider variables means that if the pawn is
    // white, it should increment the rank value, if it's black, it should
    // decrement.
    // e.g. 1.e4 - White pawn go from 2nd rank for 4th rank, so its
    // rank value increased: So, (4 - 2) * 1 > 0
    // And if it was 1... e5: go from 7th rank to
    // 5th rank, so it decremented. So, (5 - 7) * -1 > 0 as well.
    // If the calculation results in a value < 0 it's wrong, so it return false
    int8_t decider = isWhite ? 1 : -1;
    if ((rankTarget - rank) * decider < 0)
    {
        return false;
    }

    return true;
}
