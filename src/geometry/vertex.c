#include "geometry/vertex.h"

#include <stdlib.h>

Vertex *create_vertex(Point *position, Point *normal)
{
    Vertex *vertex = malloc(sizeof(Vertex));

    vertex->position = position;
    vertex->normal = normal;

    return vertex;
}

void destroy_vertex(Vertex *vertex)
{
    free(vertex->position);
    free(vertex->normal);
    free(vertex);
}
