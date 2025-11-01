#ifndef SDL_MANAGER_H
#define SDL_MANAGER_H

#include "../include/debug.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Macros for default width, height and depth.
#define WIDTH 500
#define HEIGHT 500
#define DEPTH 500

// Macros for colors.
#define WHITE 255, 255, 255
#define BLACK 0, 0, 0
#define RED 255, 0, 0
#define GREEN 0, 255, 0
#define BLUE 0, 0, 255

int sdl_init();
void sdl_quit(SDL_Renderer* renderer, SDL_Window* window);
SDL_Window* create_window(int w, int h);
SDL_Renderer* create_renderer(SDL_Window* window);

#endif /* ! SDL_MANAGER_H */
