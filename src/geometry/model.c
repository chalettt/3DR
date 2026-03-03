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
    double *vertex = calloc(4, sizeof(double));

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
    int *face = calloc(5, sizeof(int));

    size_t token_index = 0;
    char *token = strtok(line + 2, " ");
    while (token && token_index < 4)
    {
        if (is_normal)
            for (size_t i = 0; i < 2; i++)
                token = strchr(token, '/') + 1;

        face[token_index] = strtol(token, NULL, 10) - 1;
        token_index++;
        token = strtok(NULL, " ");
    }

    return face;
}

Model *load_model(char *path)
{
    FILE *obj = fopen(path, "r");
    if (!obj)
    {
        ERROR("Could not open file: %s", path);
        return NULL;
    }

    LOG("File opened, parsing commencing with file: %s", path);

    int **faces = calloc(FACE_COUNT, sizeof(int *));
    double **vertices = calloc(VERTEX_COUNT, sizeof(double *));
    // double **normals = calloc(VERTEX_COUNT, sizeof(double *));
    // int **face_normals = calloc(FACE_COUNT, sizeof(int *));

    char *line = NULL;
    size_t size = 0;

    size_t vertex_count = 0;
    size_t face_count = 0;
    // size_t face_normal_count = 0;
    // size_t normal_count = 0;
    ssize_t nread;
    while ((nread = getline(&line, &size, obj)) != -1)
    {
        if (line[0] == 'v')
        {
            if (line[1] == 'n')
            {
                // normals[normal_count++] = get_vertex(line, true);
            }
            else if (line[1] == ' ')
                vertices[vertex_count++] = get_vertex(line, false);
        }
        else if (line[0] == 'f')
        {
            faces[face_count++] = get_face(line, false);
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

    model->faces = calloc(FACE_COUNT, sizeof(Face *));
    for (size_t i = 0; faces[i]; i++)
    {
        Point **points = calloc(5, sizeof(Point *));
        points[0] =
            create_point(vertices[faces[i][0]][0], vertices[faces[i][0]][1],
                         vertices[faces[i][0]][2]);
        points[1] =
            create_point(vertices[faces[i][1]][0], vertices[faces[i][1]][1],
                         vertices[faces[i][1]][2]);
        points[2] =
            create_point(vertices[faces[i][2]][0], vertices[faces[i][2]][1],
                         vertices[faces[i][2]][2]);
        if (faces[i][3])
            points[3] =
                create_point(vertices[faces[i][3]][0], vertices[faces[i][3]][1],
                             vertices[faces[i][3]][2]);

        model->faces[i] = create_face(points);
    }
    model->origin = create_point(0, 0, 0);

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
