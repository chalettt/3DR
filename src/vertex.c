#include "../include/vertex.h"

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>

// Creates a link and initializes each component.
Links* create_links(Vertex* vertex)
{
    Links* links = calloc(1, sizeof(Links));
    if (!links)
        return ERROR("Could not allocate a link."), NULL;

    links->vertex = vertex;
    return links;
}

// Prepends a link to a list of links.
static Links* prepend(Links* links, Links* elt)
{
    if (!elt)
        return ERROR("The element to prepend was NULL."), links;
    
    elt->next = links;
    links = elt;
    return links;
}

// Destroys a list of links.
static void destroy_links(Links* links)
{
    if (links)
    {
        destroy_links(links->next);
        free(links);
    }
}

// Destroys a vertex and its links.
void destroy_vertex(Vertex* vertex)
{
    destroy_links(vertex->links);
    free(vertex);
}

// Creates a vertex and initializes each component.
Vertex* create_vertex(double x, double y, double z)
{
    Vertex* vertex = calloc(1, sizeof(Vertex));
    if (!vertex)
        return ERROR("Could not allocate a vertex."), NULL;

    vertex->x = x;
    vertex->y = y;
    vertex->z = z;
    return vertex;
}

// Creates a link in one way between to vertices.
static void link(Vertex* a, Vertex* b)
{
    if (!a || !b)
    {
        ERROR("NULL vertex when trying to link.");
        return;
    }
    a->links = prepend(a->links, create_links(b));
}

// Creates a link in both ways between to vertices.
void connect_vertex(Vertex* a, Vertex* b)
{
    link(a, b);
    link(b, a);
}

// Rotates a vertex by an angle alpha along the Y axis according to the center of the space.
void rot_x(Vertex* vertex, double alpha)
{
    double x = vertex->x;
    double z = vertex->z;
    vertex->x = x*cos(alpha) + z*sin(alpha);
    vertex->z = -x*sin(alpha) + z*cos(alpha);
}
