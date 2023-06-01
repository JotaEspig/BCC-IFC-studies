#include "application.hpp"

#include <iostream>
#include <string>
#include <stdexcept>

#include <SDL2/SDL.h>

#include "moves.hpp"

Application::Application(int _width, int _height, std::string _title)
{
    width = _width;
    height = _height;
    title = _title;
    for (int i = 0; i < 9; i++)
        board[i] = Moves::None;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        throw SDL_GetError();

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, width, height,
                              SDL_WINDOW_SHOWN);
    if (window == NULL)
        throw SDL_GetError();

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
        throw SDL_GetError();

    screen_surface = SDL_GetWindowSurface(window);
    SDL_FillRect(screen_surface, NULL,
                 SDL_MapRGB(screen_surface->format, 0xFF, 0xFF, 0xFF));

    SDL_UpdateWindowSurface(window);
}

Application::~Application()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Application::handle_mouse_click(SDL_MouseButtonEvent mouse)
{
    std::cout << "mouse clicked (" << mouse.x << "," << mouse.y << ")\n";
    int quocient = mouse.y * 3 / height;
    int remaining = mouse.x * 3 / width;
    int idx = quocient * 3 + remaining;
    int moves_amount = 0;
    for (int i = 0; i < 9; i++)
        if (board[i] != Moves::None)
            moves_amount++;

    moves_amount % 2 == 0 ? board[idx] = Moves::X : board[idx] = Moves::O;
}

void Application::draw()
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
    // Draw tic tac toe default lines
    SDL_RenderDrawLine(renderer, width / 3, 0, width / 3, height);
    SDL_RenderDrawLine(renderer, 2 * width / 3, 0, 2 * width / 3, height);
    SDL_RenderDrawLine(renderer, 0, height / 3, width, height / 3);
    SDL_RenderDrawLine(renderer, 0, 2 * height / 3, width, 2 * height / 3);
    // Draw moves
    for (int i = 0; i < 9; i++)
    {
        if (board[i] == Moves::X)
            draw_X(i);
        else if (board[i] == Moves::O)
            draw_O(i);
    }

    SDL_RenderPresent(renderer);
}

void Application::draw_X(int idx)
{
    int initial_x = (width / 3) * (idx % 3);
    int initial_y = (height / 3) * (idx / 3);
    int final_x = (width / 3) * (idx % 3 + 1);
    int final_y = (height / 3) * (idx / 3 + 1);
    SDL_RenderDrawLine(renderer, initial_x, initial_y, final_x, final_y); 
    int aux = initial_x;
    initial_x = final_x;
    final_x = aux;
    SDL_RenderDrawLine(renderer, initial_x, initial_y, final_x, final_y); 
}

void Application::draw_O(int idx)
{
}

Moves Application::check_win()
{
    for (int i = 0; i < 7; i += 3)
        if (board[i] == board[i + 1] && board[i] == board[i + 2])
            return board[i];
    for (int i = 0; i < 3; i++)
        if (board[i] == board[i + 3] && board[i] == board[i + 6])
            return board[i];

    if (board[0] == board[4] && board[0] == board[8])
        return board[0];
    else if (board[2] == board[4] && board[2] == board[6])
        return board[2];

    return Moves::None;
}

void Application::run()
{
    SDL_Event e;
    bool quit = false;
    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_QUIT:
                quit = true;
                break;

            case SDL_MOUSEBUTTONDOWN:
                handle_mouse_click(e.button);
                break;
                
            default:
                break;
            }
        }

        draw();

        if (check_win() != Moves::None)
            break;
    }
}
