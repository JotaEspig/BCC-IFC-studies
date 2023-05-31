#include <iostream>

#include "application/application.hpp"

int main(int argc, char *argv[])
{
    std::cout << "Tic Tac Toe\n";

    Application app = Application();
    app.run();
    return 0;
}
