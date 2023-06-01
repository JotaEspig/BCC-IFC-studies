#pragma once

#include <string>

#include <SDL2/SDL.h>

#include "moves.hpp"

class Application
{
    std::string title;
    int width;
    int height;
    Moves board[9];
    SDL_Window *window;
    SDL_Surface *screen_surface;
    SDL_Renderer *renderer;

    void handle_mouse_click(SDL_MouseButtonEvent mouse);
    void draw();
    void draw_X(int idx);
    void draw_O(int idx);
    Moves check_win();

public:
    Application(int _width = 480, int _height = 480, std::string _title = "Tic Tac Toe");
    ~Application();
    void run();
};
