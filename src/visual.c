#include "../include/visual.h"

// Draws each links of a vertex onto a renderer.
void draw_links(SDL_Renderer* renderer, Vertex* vertex_a)
{
    double xc = (double)WIDTH/2.0;
    double yc = (double)HEIGHT/2.0;
    Links* links = vertex_a->links;
    while (links)
    {
        Vertex* vertex_b = links->vertex;
        double x1 = PROJECT_X(vertex_a->x, vertex_a->z)+xc;
        double y1 = PROJECT_Y(vertex_a->y, vertex_a->z)+yc;
        double x2 = PROJECT_X(vertex_b->x, vertex_b->z)+xc;
        double y2 = PROJECT_Y(vertex_b->y, vertex_b->z)+yc;
        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
        links = links->next;
    }
}

// Draws each links of an array of vertices onto a renderer.
void draw_cube(SDL_Renderer* renderer, Vertex** cube)
{
    for (int i = 0; i < 8; i++)
    {
        draw_links(renderer, cube[i]);
    }
}
