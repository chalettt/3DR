#ifndef VERTEX_H
#define VERTEX_H

#include "../include/sdl_manager.h"

// Macro for the default cube size.
#define CUBE_SIZE 75

// Macros for projecting each point.
#define PROJECT_X(x, z) (x / (1.0 + z / (CUBE_SIZE*2.0)))
#define PROJECT_Y(y, z) (y / (1.0 + z / (CUBE_SIZE*2.0)))

typedef struct links
{
    struct vertex* vertex;
    struct links* next;
} Links;

typedef struct vertex
{
    double x, y, z;
    struct links* links;
} Vertex;

Links* create_links(Vertex* vertex);
void destroy_vertex(Vertex* vertex);
Vertex* create_vertex(double x, double y, double z);
void connect_vertex(Vertex* a, Vertex* b);
void rot_x(Vertex* vertex, double alpha);

#endif /* ! VERTEX_H */
