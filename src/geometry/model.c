#include "geometry/model.h"

#include <asm-generic/errno-base.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "geometry/point.h"
#include "geometry/triangle.h"
#include "utils/debug.h"

Model *model = NULL;

static double *get_vertex(char *line, bool is_normal)
{
    double *vertex = malloc(3 * sizeof(double));

    size_t token_index = 0;
    char *token = strtok(line + 2 + (is_normal ? 1 : 0), " ");
    while (token && token_index < 3)
    {
        vertex[token_index] = strtod(token, NULL);
        token_index++;
        token = strtok(NULL, " ");
    }

    return vertex;
}

static size_t *get_face(char *line, bool is_normal)
{
    size_t vertex_count = 4;
    size_t *face = malloc((vertex_count + 1) * sizeof(size_t));

    size_t token_index = 0;
    char *token = strtok(line + 2, " ");
    while (token)
    {
        if (token_index >= vertex_count)
        {
            vertex_count *= 2;
            face = realloc(face, (vertex_count + 1) * sizeof(size_t));
        }
        if (is_normal)
            for (size_t i = 0; i < 2; i++)
                token = strchr(token, '/') + 1;

        face[token_index] = strtol(token, NULL, 10);
        token_index++;
        face[token_index] = 0;
        token = strtok(NULL, " ");
    }

    return face;
}

static size_t **triangulize(size_t *points)
{
    size_t vertex_count = 0;
    while (points[vertex_count])
        vertex_count++;
    size_t triangle_count = vertex_count - 2;
    size_t **triangles = malloc((triangle_count + 1) * sizeof(size_t *));
    triangles[triangle_count] = 0;

    for (size_t i = 0; i < triangle_count; i++)
    {
        triangles[i] = malloc(3 * sizeof(size_t));
        triangles[i][0] = points[0] - 1;
        triangles[i][1] = points[i + 1] - 1;
        triangles[i][2] = points[i + 2] - 1;
    }

    return triangles;
}

Model *load_model(char *path, Point *origin)
{
    FILE *obj = fopen(path, "r");
    if (!obj)
    {
        ERROR("Could not open file: %s", path);
        return NULL;
    }

    LOG("File opened, parsing commencing with file: %s", path);

    size_t buffer_size = BUFFER_SIZE;
    size_t **faces = malloc((buffer_size + 1) * sizeof(size_t *));
    double **vertices = malloc((buffer_size + 1) * sizeof(double *));
    vertices[0] = 0;
    // double **normals = calloc(BUFFER_SIZE, sizeof(double *));
    // int **face_normals = calloc(BUFFER_SIZE, sizeof(int *));

    char *line = NULL;
    size_t size = 0;

    size_t vertex_count = 0;
    size_t face_count = 0;
    // size_t face_normal_count = 0;
    // size_t normal_count = 0;
    ssize_t nread;
    while ((nread = getline(&line, &size, obj)) != -1)
    {
        if (vertex_count >= buffer_size || face_count >= buffer_size)
        {
            buffer_size *= 2;
            faces = realloc(faces, (buffer_size + 1) * sizeof(int *));
            vertices = realloc(vertices, (buffer_size + 1) * sizeof(double *));
        }
        if (line[0] == 'v')
        {
            if (line[1] == 'n')
            {
                // normals[normal_count++] = get_vertex(line, true);
            }
            else if (line[1] == ' ')
            {
                vertices[vertex_count++] = get_vertex(line, false);
                vertices[vertex_count] = 0;
            }
        }
        else if (line[0] == 'f')
        {
            faces[face_count++] = get_face(line, false);
            faces[face_count] = 0;
            // face_normals[face_normal_count++] = get_face(line, true);
        }
        else
            continue;
    }

    fclose(obj);

    model = malloc(sizeof(Model));
    if (!model)
    {
        ERROR("Model allocation failed.");
        return NULL;
    }

    model->origin = origin;

    size_t triangle_count = face_count;
    size_t triangle_index = 0;
    model->triangles = malloc((triangle_count + 1) * sizeof(Triangle *));
    model->vertices = malloc((vertex_count + 1) * sizeof(Point *));
    model->vertices[vertex_count] = 0;
    for (size_t i = 0; vertices[i]; i++)
    {
        double *vertex = vertices[i];
        model->vertices[i] = create_point(vertex[0], vertex[1], vertex[2]);
    }
    for (size_t i = 0; faces[i]; i++)
    {
        size_t **triangles = triangulize(faces[i]);
        for (size_t j = 0; triangles[j]; j++)
        {
            if (triangle_index >= triangle_count)
            {
                triangle_count *= 2;
                model->triangles =
                    realloc(model->triangles,
                            (triangle_count + 1) * sizeof(Triangle *));
            }
            model->triangles[triangle_index++] = create_triangle(triangles[j]);
            free(triangles[j]);
            model->triangles[triangle_index] = 0;
        }
        free(triangles);
    }

    for (size_t i = 0; faces[i]; i++)
        free(faces[i]);
    for (size_t i = 0; vertices[i]; i++)
        free(vertices[i]);

    free(faces);
    free(vertices);
    return model;
}

void rotate_model(Model *model, double alpha)
{
    for (size_t i = 0; model->vertices[i]; i++)
    {
        Point *point = model->vertices[i];
        rotate_point_y(point, model->origin, alpha);
    }
    for (size_t i = 0; model->triangles[i]; i++)
    {
        Triangle *triangle = model->triangles[i];
        free(triangle->normal);
        triangle->normal = get_triangle_normal(triangle);
    }
}

void destroy_model(Model *model)
{
    for (size_t i = 0; model->triangles[i]; i++)
        destroy_triangle(model->triangles[i]);

    for (size_t i = 0; model->vertices[i]; i++)
        free(model->vertices[i]);

    free(model->triangles);
    free(model->vertices);
    free(model->origin);
    free(model);
}
