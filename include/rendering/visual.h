#ifndef VISUAL_H
#define VISUAL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>

#include "geometry/model.h"

/**
 * @brief Draws an obj on screen.
 *
 * @param texture The texture to draw on.
 * @param model The model to draw.
 */
void draw_model(SDL_Renderer *renderer, Model *model);

#endif /* ! VISUAL_H */
