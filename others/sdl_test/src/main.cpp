#include <iostream>

#include <SDL2/SDL.h>

SDL_Window *window = NULL;
SDL_Surface *screen_surface = NULL;
SDL_Surface *hello_world = NULL;

bool init();
bool load_media();
void close();

int main(int argc, char *argv[])
{
    std::cout << "Hello\n";

    if (!init())
        exit(-1);

    if (!load_media())
        exit(-1);

    SDL_Rect rect;
    rect.x = 190;
    rect.y = 50;
    SDL_BlitSurface(hello_world, NULL, screen_surface, &rect);
    SDL_UpdateWindowSurface(window);

    // Waits for sdl_quit
    SDL_Event e;
    bool quit = false;
    while (quit == false)
        while (SDL_PollEvent(&e))
            if (e.type == SDL_QUIT)
                quit = true;

    close();

    return 0;
}

bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    window = SDL_CreateWindow("SDL Brabo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        std::cout << "Window could not be created: " << SDL_GetError() << "\n";
        return false;
    }

    screen_surface = SDL_GetWindowSurface(window);
    SDL_FillRect(screen_surface, NULL, SDL_MapRGB(screen_surface->format, 0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface(window);

    return true;
}

bool load_media()
{
    hello_world = SDL_LoadBMP("assets/mario.bmp");
    if (hello_world == NULL)
    {
        std::cout << "Error when loading bitmap. SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    return true;
}

void close()
{
    SDL_FreeSurface(hello_world);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
