#include "pawn.hpp"

#include <cstdlib>
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
    if (!Piece::isMovePossible(file, rank, fileTarget, rankTarget))
        return 0;

    uint8_t fileDiff = abs(fileTarget - file);
    uint8_t rankDiff = abs(rankTarget - rank);
    // decider defines whether pawn should go
    // rankTarget > rank if white (*1)
    // rankTarget < rank if black (*-1)
    // if calculation is < 0, something is off
    int8_t decider = isWhite ? 1 : -1;
    if ((rankTarget - rank) * decider < 0)
        return 0;

    if (rankDiff == 2)
        return (rank == 2 || rank == 7) && fileDiff == 0;

    if (rankDiff != 1)
        return 0;

    if (fileDiff == 1)
        return 2;

    return 1;
}
