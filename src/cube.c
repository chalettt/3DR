#include "../include/cube.h"

// Returns an array of vertices representing a cube.
Vertex** create_cube(int size)
{
    // Creates each point.
    Vertex* a = create_vertex(-size, -size,  size);
    Vertex* b = create_vertex( size, -size,  size);
    Vertex* c = create_vertex( size,  size,  size);
    Vertex* d = create_vertex(-size,  size,  size);

    Vertex* e = create_vertex(-size, -size, -size);
    Vertex* f = create_vertex( size, -size, -size);
    Vertex* g = create_vertex( size,  size, -size);
    Vertex* h = create_vertex(-size,  size, -size);

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

    Vertex** cube = calloc(8, sizeof(Vertex*));
    if (!cube)
        return ERROR("Could not allocate a cube."), NULL;

    cube[0] = a; 
    cube[1] = b; 
    cube[2] = c; 
    cube[3] = d;

    cube[4] = e; 
    cube[5] = f; 
    cube[6] = g;
    cube[7] = h;

    return cube;
}

// Rotates each vertex of the cube.
void rot_cube_x(Vertex** cube, double alpha)
{
    for (int i = 0; i < 8; i++)
    {
        rot_x(cube[i], alpha);
    }
}

// Destroys each vertex of a cube.
void destroy_cube(Vertex** cube)
{
    for (int i = 0; i < 8; i++)
    {
        destroy_vertex(cube[i]);
    }
    free(cube);
}

