#include <iostream>

#include "board/board.hpp"
#include "board/move.hpp"
#include "pieces/pieces.hpp"
#include "pieces/piece.hpp"
#include "pieces/pawn/pawn.hpp"

int main()
{
    auto b = new chess::Board();
    auto move = chess::Move(chess::Pieces::WhitePawn, 4, 7, 4, 5);
    auto result = b->doMove(move); // 0

    move = chess::Move(chess::Pieces::WhitePawn, 4, 2, 4, 5);
    result = b->doMove(move); // 0

    move = chess::Move(chess::Pieces::WhitePawn, 4, 2, 3, 4);
    result = b->doMove(move); // 0

    move = chess::Move(chess::Pieces::WhitePawn, 4, 2, 5, 4);
    result = b->doMove(move); // 0

    move = chess::Move(chess::Pieces::WhitePawn, 4, 2, 4, 4);
    result = b->doMove(move); // 1

    move = chess::Move(chess::Pieces::WhitePawn, 4, 2, 5, 3);
    result = b->doMove(move); // 2

    std::cout << b << "\n";
    // chess::Piece *piece;
    // chess::Pawn pawn = chess::Pawn(true);
    // piece = &pawn;

    // std::cout << piece->isMovePossible(2, 4, 4, 4);

    return 0;
}
