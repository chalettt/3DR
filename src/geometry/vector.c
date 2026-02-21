#include <math.h>

#include "geometry/point.h"

Point *vector_normalize(Point *p)
{
    double length = sqrtf(p->x * p->x + p->y * p->y + p->z * p->z);

    double normalized_x = p->x / length;
    double normalized_y = p->y / length;
    double normalized_z = p->z / length;

    return create_point(normalized_x, normalized_y, normalized_z);
}

Point *vector_cross(Point *a, Point *b)
{
    double cross_x = a->y * b->z - a->z * b->y;
    double cross_y = a->z * b->x - a->x * b->z;
    double cross_z = a->x * b->y - a->y * b->x;

    return create_point(cross_x, cross_y, cross_z);
}

double dot_product(Point *a, Point *b)
{
    return a->x * b->x + a->y * b->y + a->z * b->z;
}
