#include <iostream>

#include "board/board.hpp"
#include "board/move.hpp"
#include "pieces/pieces.hpp"
#include "pieces/piece.hpp"
#include "pieces/pawn/pawn.hpp"

int main()
{
    auto b = new chess::Board();
    // setup for test en passant
    auto move = chess::Move(chess::Pieces::WhitePawn, 5, 2, 5, 4);
    auto result = b->doMove(move); // true
    move = chess::Move(chess::Pieces::BlackPawn, 5, 7, 5, 6);
    result = b->doMove(move);
    move = chess::Move(chess::Pieces::WhitePawn, 5, 4, 5, 5);
    result = b->doMove(move);
    move = chess::Move(chess::Pieces::BlackPawn, 4, 7, 4, 5);
    result = b->doMove(move);

    move = chess::Move(chess::Pieces::WhitePawn, 5, 5, 4, 6);
    result = b->doMove(move);

    std::cout << b << "\n";
    // chess::Piece *piece;
    // chess::Pawn pawn = chess::Pawn(true);
    // piece = &pawn;

    // std::cout << piece->isMovePossible(2, 4, 4, 4);

    return 0;
}
