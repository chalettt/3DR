#ifndef VERTEX_H
#define VERTEX_H

#include "geometry/point.h"
#include "rendering/sdl_manager.h"

// Macro for the default cube size.
#define CUBE_SIZE 75

typedef struct links
{
    struct vertex *vertex;
    struct links *next;
} Links;

typedef struct vertex
{
    Point *position;
    Links *links;
} Vertex;

Point *init_camera(double x, double y, double z);
Links *create_links(Vertex *vertex);
void destroy_vertex(Vertex *vertex);
Vertex *create_vertex(double x, double y, double z);
void connect_vertex(Vertex *a, Vertex *b);

#endif /* ! VERTEX_H */
