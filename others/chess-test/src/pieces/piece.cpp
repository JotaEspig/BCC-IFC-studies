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

ResultCode Piece::isMovePossible(uint8_t file, uint8_t rank,
                                 uint8_t fileTarget, uint8_t rankTarget)
{
    if (file == fileTarget && rank == rankTarget)
        return ResultCode::Invalid;
    if (file < 1 || file > 8 || rank < 1 || rank > 8)
        return ResultCode::Invalid;
    if (fileTarget < 1 || fileTarget > 8 || rankTarget < 1 || rankTarget > 8)
        return ResultCode::Invalid;

    return ResultCode::Normal;
}
