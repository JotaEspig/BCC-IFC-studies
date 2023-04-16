#include "piece.hpp"

using namespace chess;

Piece::Piece(bool isWhite)
{
    this->isWhite = isWhite;
}

Piece::~Piece()
{
}

bool Piece::getIsWhite()
{
    return this->isWhite;
}

ResultCode Piece::isMovePossible(uint8_t rank, uint8_t file,
                                 uint8_t rankTarget, uint8_t fileTarget)
{
    if (rank < 1 || rank > 8 || file < 1 || file > 8)
    {
        return ResultCode::Invalid;
    }
    if (rankTarget < 1 || rankTarget > 8 || fileTarget < 1 || fileTarget > 8)
    {
        return ResultCode::Invalid;
    }
    return ResultCode::Normal;
}