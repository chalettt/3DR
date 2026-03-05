#include "geometry/point.h"

typedef struct vertex
{
    Point *position;
    Point *normal;
} Vertex;

Vertex *create_vertex(Point *position, Point *normal);
void destroy_vertex(Vertex *vertex);
