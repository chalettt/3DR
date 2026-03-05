#ifndef VISUAL_H
#define VISUAL_H

#include <SDL2/SDL.h>

#include "geometry/mesh.h"

/**
 * @brief Draws an obj on screen.
 *
 * @param renderer The renderer to draw on.
 * @param mesh The mesh to draw.
 */
void draw_mesh(SDL_Texture *texture, Mesh *mesh);

#endif /* ! VISUAL_H */
