#ifndef CUBE_H
#define CUBE_H

#include "../include/vertex.h"

Vertex** create_cube(int size);
void rot_cube_x(Vertex** cube, double alpha);
void destroy_cube(Vertex** cube);

#endif /* ! CUBE_H */
