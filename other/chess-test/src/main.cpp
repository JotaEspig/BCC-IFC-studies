#include <iostream>

#include "board/board.hpp"

int main()
{
    auto b = new chess::Board();
    int a = sizeof(chess::Pieces::BlackBishop);
    std::cout << b << "\n";
    return 0;
}
