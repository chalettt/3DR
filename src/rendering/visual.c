#include "rendering/visual.h"

#include <stdbool.h>
#include <stdint.h>

#include "geometry/mesh.h"
#include "geometry/point.h"
#include "geometry/vector.h"
#include "rendering/camera.h"
#include "rendering/sdl_manager.h"

static uint32_t framebuffer[WIDTH * HEIGHT];
static float zbuffer[WIDTH * HEIGHT];
static Point world_light = { 0, 0.7, -0.7 };
static Point *projected_vertices = NULL;

static void clear_buffers(void)
{
    for (int i = 0; i < WIDTH * HEIGHT; i++)
    {
        framebuffer[i] = 0;
        zbuffer[i] = FLT_MAX;
    }
}

static double get_light_intensity(Point *face_normal)
{
    double intensity = dot_product(face_normal, &world_light);
    intensity = intensity < 0 ? 0 : intensity;

    double ambient = 0.1;
    intensity += ambient;

    intensity = intensity > 1 ? 1 : intensity;

    return intensity;
}

static bool is_valid(Point p)
{
    return p.z > 0.01;
}

static void project_vertices(Point **vertices)
{
    for (size_t i = 0; vertices[i]; i++)
        projected_vertices[i] = project(vertices[i]);
}

static void rasterize_triangle(Triangle *triangle)
{
    uint8_t value = (uint8_t)(get_light_intensity(triangle->normal) * 255);
    uint32_t color = (255 << 24) | (value << 16) | (value << 8) | value;

    Point a = projected_vertices[triangle->indices[0]];
    Point b = projected_vertices[triangle->indices[1]];
    Point c = projected_vertices[triangle->indices[2]];
    if (!is_valid(a) || !is_valid(b) || !is_valid(c))
        return;

    double area = determinant(&a, &b, &c);

    size_t min_x = floor(fmin(a.x, fmin(b.x, c.x)));
    size_t max_x = ceil(fmax(a.x, fmax(b.x, c.x)));
    size_t min_y = floor(fmin(a.y, fmin(b.y, c.y)));
    size_t max_y = ceil(fmax(a.y, fmax(b.y, c.y)));

    for (size_t y = min_y; y < max_y; y++)
    {
        for (size_t x = min_x; x < max_x; x++)
        {
            Point p = { x + 0.5, y + 0.5, 0 };

            double w0 = determinant(&b, &c, &p);
            double w1 = determinant(&c, &a, &p);
            double w2 = determinant(&a, &b, &p);

            if ((w0 >= 0 && w1 >= 0 && w2 >= 0)
                || (w0 <= 0 && w1 <= 0 && w2 <= 0))
            {
                w0 /= area;
                w1 /= area;
                w2 /= area;

                float depth = w0 * a.z + w1 * b.z + w2 * c.z;

                int idx = y * WIDTH + x;

                if (depth < zbuffer[idx])
                {
                    zbuffer[idx] = depth;
                    framebuffer[idx] = color;
                }
            }
        }
    }
}

void draw_mesh(SDL_Texture *texture, Mesh *mesh)
{
    clear_buffers();

    Triangle **triangles = mesh->triangles;
    if (!projected_vertices)
        projected_vertices = malloc(mesh->vertex_count * sizeof(Point));
    project_vertices(mesh->vertices);

    for (size_t i = 0; triangles[i]; i++)
    {
        Triangle *triangle = triangles[i];
        Point rel = *(mesh->vertices[triangle->indices[0]]);
        sub_point(&rel, camera->position);
        if (dot_product(triangle->normal, &rel) < 0)
            rasterize_triangle(triangle);
    }

    SDL_UpdateTexture(texture, NULL, framebuffer, WIDTH * sizeof(uint32_t));
}
