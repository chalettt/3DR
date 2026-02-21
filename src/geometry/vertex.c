#include "geometry/vertex.h"
#include "rendering/sdl_manager.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>

static Links *create_links(Vertex *vertex)
{
    Links *links = calloc(1, sizeof(Links));
    if (!links)
        return ERROR("Could not allocate a link."), NULL;

    links->vertex = vertex;
    return links;
}

static Links *prepend(Links *links, Links *elt)
{
    if (!elt)
        return ERROR("The element to prepend was NULL."), links;

    elt->next = links;
    links = elt;
    return links;
}

static void destroy_links(Links *links)
{
    if (links)
    {
        destroy_links(links->next);
        free(links);
    }
}

void destroy_vertex(Vertex *vertex)
{
    destroy_links(vertex->links);
    free(vertex->position);
    free(vertex);
}

Vertex *create_vertex(double x, double y, double z)
{
    Vertex *vertex = calloc(1, sizeof(Vertex));
    if (!vertex)
        return ERROR("Could not allocate a vertex."), NULL;

    vertex->position = create_point(x, y, z);
    return vertex;
}

static void link(Vertex *a, Vertex *b)
{
    if (!a || !b)
    {
        ERROR("NULL vertex when trying to link.");
        return;
    }
    a->links = prepend(a->links, create_links(b));
}

void connect_vertex(Vertex *a, Vertex *b)
{
    link(a, b);
    link(b, a);
}
