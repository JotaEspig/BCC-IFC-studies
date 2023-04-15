#include "piece.hpp"

using namespace chess;

Piece::Piece(bool isWhite)
{
    this->isWhite = isWhite;
}

Piece::~Piece()
{
}

uint8_t Piece::isMovePossible(uint8_t rank, uint8_t file,
                              uint8_t rankTarget, uint8_t fileTarget)
{
    if (rank < 1 || rank > 8 || file < 1 || file > 8)
    {
        return 0;
    }
    if (rankTarget < 1 || rankTarget > 8 || fileTarget < 1 || fileTarget > 8)
    {
        return 0;
    }
    return 1;
}