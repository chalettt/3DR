#include "rendering/visual.h"

#include <SDL2/SDL_image.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#include "geometry/model.h"
#include "geometry/point.h"
#include "geometry/triangle.h"
#include "geometry/vector.h"
#include "rendering/camera.h"

static double get_light_intensity(Point *face_normal)
{
    Point world_light = { 0, -1, 1 };
    world_light = vector_normalize(&world_light);
    world_light = *scalar_product(&world_light, -1);

    double intensity = dot_product(face_normal, &world_light);
    intensity = intensity < 0 ? 0 : intensity;

    double ambient = 0.1;
    intensity += ambient;

    intensity = intensity > 1 ? 1 : intensity;

    return intensity;
}

void draw_triangle(SDL_Renderer *renderer, Triangle *triangle)
{
    double intensity = get_light_intensity(triangle->normal);
    Uint32 color = 255.0 * intensity;

    Point **mesh_triangle = malloc(3 * sizeof(Point *));
    for (size_t i = 0; i < 3; i++)
    {
        mesh_triangle[i] = project(model->vertices[triangle->indices[i]]);
        if (!mesh_triangle[i])
        {
            for (size_t j = 0; j < i; j++)
                free(mesh_triangle[j]);
            free(mesh_triangle);
            return;
        }
    }

    SDL_Vertex vertices[3] = {
        { { mesh_triangle[0]->x, mesh_triangle[0]->y },
          { color, color, color, 255 },
          { 0.0, 0.0 } },
        { { mesh_triangle[1]->x, mesh_triangle[1]->y },
          { color, color, color, 255 },
          { 0.0, 0.0 } },
        { { mesh_triangle[2]->x, mesh_triangle[2]->y },
          { color, color, color, 255 },
          { 0.0, 0.0 } },
    };

    SDL_RenderGeometry(renderer, NULL, vertices, 3, NULL, 0);

    for (size_t i = 0; i < 3; i++)
        free(mesh_triangle[i]);
    free(mesh_triangle);
}

static double get_triangle_depth(Triangle *triangle)
{
    Point a = *(model->vertices[triangle->indices[0]]);
    Point b = *(model->vertices[triangle->indices[1]]);
    Point c = *(model->vertices[triangle->indices[2]]);

    Point *cp = camera->position;

    double a_depth = sub_point(&a, cp)->z;
    double b_depth = sub_point(&b, cp)->z;
    double c_depth = sub_point(&c, cp)->z;

    return (a_depth + b_depth + c_depth) / 3.0;
}

void draw_model(SDL_Renderer *renderer, Model *model)
{
    Triangle **triangles = model->triangles;
    size_t triangle_count = 0;
    while (triangles[triangle_count])
        triangle_count++;

    for (size_t i = 0; i < triangle_count; i++)
    {
        for (size_t j = i; j > 0
             && get_triangle_depth(triangles[j - 1])
                 < get_triangle_depth(triangles[j]);
             j--)
        {
            Triangle *tmp = triangles[j];
            triangles[j] = triangles[j - 1];
            triangles[j - 1] = tmp;
        }
    }

    for (size_t i = 0; triangles[i]; i++)
    {
        Triangle *triangle = triangles[i];
        Point rel = *(model->vertices[triangle->indices[0]]);
        sub_point(&rel, camera->position);
        if (dot_product(triangle->normal, &rel) < 0)
            draw_triangle(renderer, triangle);
    }
}
