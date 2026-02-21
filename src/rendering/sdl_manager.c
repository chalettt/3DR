#include "rendering/sdl_manager.h"
#include "utils/debug.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int sdl_init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        ERROR("Could not initialize SDL.\n %s\n", SDL_GetError());
        return 1;
    }

    LOG("SDL initialized.\n");
    return 0;
}

void sdl_quit(SDL_Renderer *renderer, SDL_Window *window)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

SDL_Window *create_window(int w, int h)
{
    SDL_Window *window = SDL_CreateWindow("Cube", SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED, w, h, 0);

    return window;
}

SDL_Renderer *create_renderer(SDL_Window *window)
{
    SDL_Renderer *renderer =
        SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, BLACK, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    return renderer;
}
