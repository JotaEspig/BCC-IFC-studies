#include "move.hpp"

using namespace chess;

Move::Move(Pieces piece, uint8_t file, uint8_t rank,
           uint8_t fileTarget, uint8_t rankTarget)
{
    this->piece = piece;
    this->file = file;
    this->rank = rank;
    this->fileTarget = fileTarget;
    this->rankTarget = rankTarget;
}

Move::~Move()
{
}
