#include "rendering/visual.h"

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <stdlib.h>

#include "geometry/face.h"
#include "geometry/model.h"
#include "geometry/point.h"
#include "geometry/vector.h"
#include "rendering/camera.h"
#include "rendering/sdl_manager.h"

void draw_face(SDL_Renderer *renderer, Face *face)
{
    Point *projection_a = project(face->points[0]);
    Point *projection_b = project(face->points[1]);
    Point *projection_c = project(face->points[2]);
    Point *projection_d = NULL;
    if (face->points[3])
        projection_d = project(face->points[3]);

    if (!projection_a || !projection_b || !projection_c
        || (face->points[3] && !projection_d))
        goto exit;

    Point world_light = { 0, -1, 1 };
    world_light = vector_normalize(&world_light);
    world_light = *scalar_product(&world_light, -1);

    double intensity = dot_product(face->normal, &world_light);
    intensity = intensity < 0 ? 0 : intensity;

    double ambient = 0.1;
    intensity += ambient;

    intensity = intensity > 1 ? 1 : intensity;

    SDL_Color color = { WHITE, 255 };
    color.r *= intensity;
    color.g *= intensity;
    color.b *= intensity;

    if (!projection_d)
    {
        SDL_Vertex vertices[3] = {
            { { projection_a->x, projection_a->y }, color, { 0.0f, 0.0f } },
            { { projection_b->x, projection_b->y }, color, { 0.0f, 0.0f } },
            { { projection_c->x, projection_c->y }, color, { 0.0f, 0.0f } },
        };

        SDL_RenderGeometry(renderer, NULL, vertices, 3, NULL, 0);
    }
    else
    {
        SDL_Vertex vertices[4] = {
            { { projection_a->x, projection_a->y }, color, { 0.0f, 0.0f } },
            { { projection_b->x, projection_b->y }, color, { 0.0f, 0.0f } },
            { { projection_c->x, projection_c->y }, color, { 0.0f, 0.0f } },
            { { projection_d->x, projection_d->y }, color, { 0.0f, 0.0f } },
        };
        const int indices[] = { 0, 1, 2, 2, 3, 0 };

        SDL_RenderGeometry(renderer, NULL, vertices, 4, indices, 6);
    }

exit:
    free(projection_a);
    free(projection_b);
    free(projection_c);
    free(projection_d);
}

void draw_model(SDL_Renderer *renderer, Model *model)
{
    // Point *origin = model->origin;
    Face **faces = model->faces;

    for (size_t i = 0; faces[i]; i++)
    {
        Face *face = faces[i];
        Point rel = *(faces[i]->points[0]);
        sub_point(&rel, camera->position);
        if (dot_product(face->normal, &rel) < 0)
            draw_face(renderer, face);
    }
}
