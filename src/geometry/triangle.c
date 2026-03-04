#include "geometry/triangle.h"

#include <stdlib.h>

#include "geometry/model.h"
#include "geometry/point.h"
#include "geometry/vector.h"

Point *get_triangle_normal(Triangle *triangle)
{
    Point a = *(model->vertices[triangle->indices[1]]);
    Point b = *(model->vertices[triangle->indices[2]]);
    sub_point(&a, model->vertices[triangle->indices[0]]);
    sub_point(&b, model->vertices[triangle->indices[0]]);

    Point normal = vector_cross(&a, &b);
    normal = vector_normalize(&normal);
    return create_point(normal.x, normal.y, normal.z);
}

Triangle *create_triangle(size_t indices[3])
{
    Triangle *triangle = malloc(sizeof(Triangle));

    if (!triangle)
        return NULL;

    for (size_t i = 0; i < 3; i++)
        triangle->indices[i] = indices[i];
    triangle->normal = get_triangle_normal(triangle);

    return triangle;
}

void destroy_triangle(Triangle *triangle)
{
    if (!triangle)
        return;

    free(triangle->normal);
    free(triangle);
}
