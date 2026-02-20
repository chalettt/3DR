#include "visual.h"

// Draws each links of a vertex onto a renderer.
void draw_links(SDL_Renderer *renderer, Vertex *vertex_a)
{
  Links *links = vertex_a->links;
  Point *projection_a = project(vertex_a->position);
  while (links)
  {
    Vertex *vertex_b = links->vertex;
    Point *projection_b = project(vertex_b->position);
    SDL_RenderDrawLine(renderer, projection_a->x, projection_a->y, projection_b->x, projection_b->y);

    free(projection_b);
    links = links->next;
  }
  free(projection_a);
}

// Draws each links of an array of vertices onto a renderer.
void draw_cube(SDL_Renderer *renderer, Cube *cube)
{
  for (int i = 0; i < 8; i++)
  {
    draw_links(renderer, cube->vertices[i]);
  }
}
