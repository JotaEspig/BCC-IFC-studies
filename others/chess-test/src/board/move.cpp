#include "move.hpp"

using namespace chess;

Move::Move(Pieces piece, uint8_t rank, uint8_t file, uint8_t rankTarget, uint8_t fileTarget)
{
    this->piece = piece;
    this->rank = rank;
    this->file = file;
    this->rankTarget = rankTarget;
    this->fileTarget = fileTarget;
}

Move::~Move()
{
}
