#ifndef VECTOR_H
#define VECTOR_H

#include "point.h"

Point *vector_normalize(Point *p);
Point *vector_cross(Point *a, Point *b);
double dot_product(Point *a, Point *b);

#endif /* VECTOR_H */
