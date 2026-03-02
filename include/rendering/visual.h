#ifndef VISUAL_H
#define VISUAL_H

#include <SDL2/SDL.h>

#include "geometry/model.h"

/**
 * @brief Draws an obj on screen.
 *
 * @param renderer The renderer to draw on.
 * @param vertices The vertices of the model.
 * @param faces The faces of the model with indices relative to the vertices.
 */
void draw_model(SDL_Renderer *renderer, Model *model);

#endif /* ! VISUAL_H */
