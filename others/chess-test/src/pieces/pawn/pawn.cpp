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

ResultCode Pawn::isMovePossible(uint8_t file, uint8_t rank,
                                uint8_t fileTarget, uint8_t rankTarget)
{
    ResultCode resultCode =
        Piece::isMovePossible(file, rank, fileTarget, rankTarget);
    if (resultCode == ResultCode::Invalid)
        return resultCode;

    uint8_t fileDiff = abs(fileTarget - file);
    uint8_t rankDiff = abs(rankTarget - rank);
    // decider defines whether pawn should go
    // rankTarget > rank if white (*1)
    // rankTarget < rank if black (*-1)
    // if calculation is < 0, something is off
    int8_t decider = isWhite ? 1 : -1;
    if ((rankTarget - rank) * decider < 0)
        return ResultCode::Invalid;

    if (rankDiff == 2)
        return (rank == 2 || rank == 7) && fileDiff == 0
                   ? ResultCode::Normal
                   : ResultCode::Invalid;

    if (rankDiff != 1)
        return ResultCode::Invalid;

    if (fileDiff == 1)
        return ResultCode::Capture;

    return ResultCode::Normal;
}
