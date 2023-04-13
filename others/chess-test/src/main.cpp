#include <iostream>

#include "board/board.hpp"
#include "board/move.hpp"
#include "pieces/pieces.hpp"
#include "pieces/piece.hpp"
#include "pieces/pawn/pawn.hpp"

int main()
{
    auto b = new chess::Board();
    auto move = chess::Move(chess::Pieces::WhitePawn, 7, 4, 5, 4);
    b->doMove(move);
    std::cout << b << "\n";
    //chess::Piece *piece;
    //chess::Pawn pawn = chess::Pawn(true);
    //piece = &pawn;

    //std::cout << piece->isMovePossible(2, 4, 4, 4);

    return 0;
}
