#ifndef TRIANGE_H
#define TRIANGE_H

#include "geometry/point.h"

typedef struct face
{
    Point **points;
    Point *normal;
} Face;

Face *create_face(Point **points);
void destroy_face(Face *face);
Point *get_face_normal(Face *face);

#endif /* TRIANGE_H */
