#include "geometry/model.h"

#include <asm-generic/errno-base.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "geometry/face.h"
#include "geometry/point.h"
#include "utils/debug.h"

static double *get_vertex(char *line, bool is_normal)
{
    double *vertex = malloc(4 * sizeof(double));
    vertex[3] = 0;

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

static int *get_face(char *line, bool is_normal)
{
    size_t vertex_count = 4;
    int *face = malloc((vertex_count + 1) * sizeof(int));

    size_t token_index = 0;
    char *token = strtok(line + 2, " ");
    while (token)
    {
        if (token_index >= vertex_count)
        {
            vertex_count *= 2;
            face = realloc(face, (vertex_count + 1) * sizeof(int));
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
    int **faces = malloc((buffer_size + 1) * sizeof(int *));
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

    Model *model = malloc(sizeof(Model));
    if (!model)
    {
        ERROR("Model allocation failed.");
        return NULL;
    }

    model->origin = origin;
    model->faces = malloc((face_count + 1) * sizeof(Face *));
    model->faces[face_count] = 0;
    for (size_t i = 0; faces[i]; i++)
    {
        size_t face_vertex_count = 0;
        while (faces[i][face_vertex_count])
            face_vertex_count++;

        Point **points = malloc((face_vertex_count + 1) * sizeof(Point *));
        points[face_vertex_count] = 0;
        for (size_t j = 0; j < face_vertex_count; j++)
        {
            points[j] = create_point(vertices[faces[i][j] - 1][0],
                                     vertices[faces[i][j] - 1][1],
                                     vertices[faces[i][j] - 1][2]);
            add_point(points[j], origin);
        }

        model->faces[i] = create_face(points);
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
    for (size_t i = 0; model->faces[i]; i++)
    {
        Face *face = model->faces[i];
        for (size_t j = 0; face->points[j]; j++)
        {
            Point *point = face->points[j];
            rotate_point_y(point, model->origin, alpha);
        }
        free(face->normal);
        face->normal = get_face_normal(face);
    }
}

void destroy_model(Model *model)
{
    for (size_t i = 0; model->faces[i]; i++)
    {
        destroy_face(model->faces[i]);
    }

    free(model->faces);
    free(model->origin);
    free(model);
}
