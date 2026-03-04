#include <math.h>

#include "geometry/point.h"

Point vector_normalize(Point *p)
{
    double length = sqrtf(p->x * p->x + p->y * p->y + p->z * p->z);

    double normalized_x = p->x / length;
    double normalized_y = p->y / length;
    double normalized_z = p->z / length;

    Point normalized_vector = { normalized_x, normalized_y, normalized_z };
    return normalized_vector;
}

Point vector_cross(Point *a, Point *b)
{
    double cross_x = a->y * b->z - a->z * b->y;
    double cross_y = a->z * b->x - a->x * b->z;
    double cross_z = a->x * b->y - a->y * b->x;

    Point cross_product = { cross_x, cross_y, cross_z };
    return cross_product;
}

double dot_product(Point *a, Point *b)
{
    return a->x * b->x + a->y * b->y + a->z * b->z;
}

double determinant(Point *a, Point *b, Point *p)
{
    double w = b->x - a->x;
    double x = p->x - a->x;
    double y = b->y - a->y;
    double z = p->y - a->y;
    return w * z - y * x;
}
