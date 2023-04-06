#include <iostream>

#include "board/board.hpp"
#include "board/move.hpp"
#include "pieces/pieces.hpp"

int main()
{
    auto b = new chess::Board();
    auto move = chess::Move(chess::Pieces::WhitePawn, 1, 4, 4, 4);
    b->doMove(move);
    std::cout << b << "\n";

    return 0;
}
