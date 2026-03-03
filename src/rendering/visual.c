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

    size_t face_vertex_count = 0;
    while (face->points[face_vertex_count])
        face_vertex_count++;

    SDL_Vertex *vertices = malloc(face_vertex_count * sizeof(SDL_Vertex));
    for (size_t i = 0; i < face_vertex_count; i++)
    {
        Point *projection = project(face->points[i]);
        if (!projection)
        {
            free(vertices);
            return;
        }

        SDL_Vertex vertex = { { projection->x, projection->y },
                              color,
                              { 0.0f, 0.0f } };
        vertices[i] = vertex;
        free(projection);
    }

    size_t index_count = (face_vertex_count - 2) * 3;
    int *indices = malloc(index_count * sizeof(int));
    int offset = 0;
    for (size_t i = 0; i < index_count; i += 3)
    {
        indices[i] = 0;
        indices[i + 1] = offset + 1;
        indices[i + 2] = offset + 2;
        offset++;
    }
    SDL_RenderGeometry(renderer, NULL, vertices, face_vertex_count, indices,
                       index_count);

    free(indices);
    free(vertices);
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
