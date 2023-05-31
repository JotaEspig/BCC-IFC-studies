#include "application.hpp"

#include <iostream>
#include <string>
#include <stdexcept>

#include <SDL2/SDL.h>

Application::Application(int _width, int _height, std::string _title)
{
    width = _width;
    height = _height;
    title = _title;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
        throw;
    }

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        std::cout << "Window could not be created: " << SDL_GetError() << "\n";
        throw;
    }

    screen_surface = SDL_GetWindowSurface(window);
    SDL_FillRect(screen_surface, NULL, SDL_MapRGB(screen_surface->format, 0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface(window);
}

Application::~Application()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Application::run()
{
    SDL_Event e;
    bool quit = false;
    while (!quit)
        while (SDL_PollEvent(&e))
            if (e.type == SDL_QUIT)
                quit = true;
}
