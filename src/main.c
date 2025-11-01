#include "../include/visual.h"

int main(int argc, char** argv)
{
    if (argc < 1 || !argv || sdl_init())
        return 1;
    
    // Creating the window and renderer.
    SDL_Window* window = create_window(WIDTH, HEIGHT);
    SDL_Renderer* renderer = create_renderer(window);

    unsigned running = 1;
    SDL_Event event;

    // Creating the rotating cube.
    Vertex** cube = create_cube(CUBE_SIZE);

    // Rotating speed.
    double alpha = 0.025;

    // Window loop
    while (running) 
    {
        while (SDL_PollEvent(&event)) 
        {
            // If the window gets terminated.
            if (event.type == SDL_QUIT) 
            {
                // Exit the loop;
                running = 0;
            }
        }

        // Clears the window.
        SDL_SetRenderDrawColor(renderer, BLACK, 255);
        SDL_RenderClear(renderer);

        // Draws the rotated cube in red.
        SDL_SetRenderDrawColor(renderer, RED, 255);
        rot_cube_x(cube, alpha);
        draw_cube(renderer, cube);
        SDL_RenderPresent(renderer);

        // 60 frames a second.
        SDL_Delay(1000/60);
    }
    
    // Properly quits sdl.
    sdl_quit(renderer, window);

    // Frees everything
    destroy_cube(cube);

    return 0;
}
