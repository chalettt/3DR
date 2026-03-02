#include "geometry/face.h"

#include <stdlib.h>

#include "geometry/point.h"
#include "geometry/vector.h"

Point *get_face_normal(Face *face)
{
    Point a = *(face->points[1]);
    Point b = *(face->points[2]);
    sub_point(&a, face->points[0]);
    sub_point(&b, face->points[0]);

    Point normal = vector_cross(&a, &b);
    normal = vector_normalize(&normal);
    return create_point(normal.x, normal.y, normal.z);
}

Face *create_face(Point **points)
{
    Face *face = malloc(sizeof(Face));

    if (!face)
        return NULL;

    face->points = points;
    face->normal = get_face_normal(face);

    return face;
}

void destroy_face(Face *face)
{
    if (!face)
        return;

    for (size_t i = 0; face->points[i]; i++)
        free(face->points[i]);

    free(face->points);
    free(face->normal);
    free(face);
}
