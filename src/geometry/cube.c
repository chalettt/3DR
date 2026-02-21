#include "geometry/cube.h"

// Returns an array of vertices representing a cube.
Cube *create_cube(int size, Point *origin)
{
    // Creates each point.
    Vertex *a =
        create_vertex(-size + origin->x, -size + origin->y, size + origin->z);
    Vertex *b =
        create_vertex(size + origin->x, -size + origin->y, size + origin->z);
    Vertex *c =
        create_vertex(size + origin->x, size + origin->y, size + origin->z);
    Vertex *d =
        create_vertex(-size + origin->x, size + origin->y, size + origin->z);

    Vertex *e =
        create_vertex(-size + origin->x, -size + origin->y, -size + origin->z);
    Vertex *f =
        create_vertex(size + origin->x, -size + origin->y, -size + origin->z);
    Vertex *g =
        create_vertex(size + origin->x, size + origin->y, -size + origin->z);
    Vertex *h =
        create_vertex(-size + origin->x, size + origin->y, -size + origin->z);

    // Creates all the edges
    connect_vertex(a, b);
    connect_vertex(b, c);
    connect_vertex(c, d);
    connect_vertex(d, a);
    connect_vertex(e, f);
    connect_vertex(f, g);

    connect_vertex(g, h);
    connect_vertex(h, e);
    connect_vertex(a, e);
    connect_vertex(b, f);
    connect_vertex(c, g);
    connect_vertex(d, h);

    Vertex **cube_vertices = malloc(8 * sizeof(Vertex *));
    Point *position = malloc(sizeof(Point));
    Cube *cube = malloc(sizeof(Cube));

    if (!cube_vertices || !cube)
        return ERROR("Could not allocate a cube."), NULL;

    cube_vertices[0] = a;
    cube_vertices[1] = b;
    cube_vertices[2] = c;
    cube_vertices[3] = d;

    cube_vertices[4] = e;
    cube_vertices[5] = f;
    cube_vertices[6] = g;
    cube_vertices[7] = h;

    position->x = (a->position->x + g->position->x) / 2;
    position->y = (a->position->y + g->position->y) / 2;
    position->z = (a->position->z + g->position->z) / 2;

    cube->vertices = cube_vertices;
    cube->position = position;

    return cube;
}

// Rotates each vertex of the cube.
void rot_cube_y(Cube *cube, Point *origin, double alpha)
{
    for (int i = 0; i < 8; i++)
    {
        rotate_point_y(cube->vertices[i]->position, origin, alpha);
    }
}

// Destroys each vertex of a cube.
void destroy_cube(Cube *cube)
{
    for (int i = 0; i < 8; i++)
    {
        destroy_vertex(cube->vertices[i]);
    }
    free(cube->vertices);
    free(cube->position);
    free(cube);
}
