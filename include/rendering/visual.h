#ifndef VISUAL_H
#define VISUAL_H

#include "geometry/cube.h"

/**
 * @brief Draws each links of a vertex onto screen.
 *
 * @param renderer The renderer to draw on.
 * @param vertex The vertex from which links will be drawn.
 */
void draw_links(SDL_Renderer *renderer, Vertex *vertex);

/**
 * @brief Draws a cube on screen.
 *
 * @param renderer The renderer to draw on.
 * @param vertex The cube to be drawn.
 */
void draw_cube(SDL_Renderer *renderer, Cube *cube);

#endif /* ! VISUAL_H */
