#ifndef CUBE_H
#define CUBE_H

#include "vertex.h"

typedef struct cube
{
    Vertex **vertices;
    Point *position;
} Cube;

Cube *create_cube(int size, Point *origin);
void rot_cube_y(Cube *cube, Point *origin, double alpha);
void destroy_cube(Cube *cube);

#endif /* ! CUBE_H */
