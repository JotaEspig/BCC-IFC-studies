#pragma once

#include <string>

#include <SDL2/SDL.h>

class Application
{
    std::string title;
    int width;
    int height;
    SDL_Window *window;
    SDL_Surface *screen_surface;

public:
    Application(int _width = 680, int _height = 480, std::string _title = "Tic Tac Toe");
    ~Application();
    void run();
};