#include "vertex.h"
#include "sdl_manager.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <stdlib.h>

static Point* camera = NULL;

Point* init_camera(double x, double y, double z)
{
  camera = malloc(sizeof(Point));
  if (!camera)
    return ERROR("Camera initialization failed."), NULL;

  camera->x = x;
  camera->y = y;
  camera->z = z;

  return camera;
}

Point *move_camera(Direction d, double delta)
{
  return add_dir(camera, d, delta);
}

// Creates a link and initializes each component.
Links *create_links(Vertex *vertex)
{
  Links *links = calloc(1, sizeof(Links));
  if (!links)
    return ERROR("Could not allocate a link."), NULL;

  links->vertex = vertex;
  return links;
}

// Prepends a link to a list of links.
static Links *prepend(Links *links, Links *elt)
{
  if (!elt)
    return ERROR("The element to prepend was NULL."), links;

  elt->next = links;
  links = elt;
  return links;
}

// Destroys a list of links.
static void destroy_links(Links *links)
{
  if (links)
  {
    destroy_links(links->next);
    free(links);
  }
}

// Destroys a vertex and its links.
void destroy_vertex(Vertex *vertex)
{
  destroy_links(vertex->links);
  free(vertex->position);
  free(vertex);
}

// Creates a vertex and initializes each component.
Vertex *create_vertex(double x, double y, double z)
{
  Vertex *vertex = calloc(1, sizeof(Vertex));
  if (!vertex)
    return ERROR("Could not allocate a vertex."), NULL;

  vertex->position = create_point(x, y, z);
  return vertex;
}

// Creates a link in one way between to vertices.
static void link(Vertex *a, Vertex *b)
{
  if (!a || !b)
  {
    ERROR("NULL vertex when trying to link.");
    return;
  }
  a->links = prepend(a->links, create_links(b));
}

// Creates a link in both ways between to vertices.
void connect_vertex(Vertex *a, Vertex *b)
{
  link(a, b);
  link(b, a);
}

// Rotates a vertex by an angle alpha along the Y axis according to the center
// of the space.
void rot_x(Vertex *vertex, Point *origin, double alpha)
{
  Point *p = vertex->position;
  double x = p->x - origin->x;
  double y = p->y - origin->y;
  double z = p->z - origin->z;

  double new_x = x * cos(alpha) - z * sin(alpha);
  double new_z = x * sin(alpha) + z * cos(alpha);

  p->x = new_x + origin->x;
  p->y = y + origin->y;
  p->z = new_z + origin->z;
}

Point* project(Point* point)
{
  double fov = 90.0;
  double d = WIDTH/2*tan(fov/2);

  double x = point->x - camera->x;
  double y = point->y - camera->y;
  double z = (point->z < camera->z + 1 ? camera->z + 1 : point->z) - camera->z;

  double x_projection = (d * x) / z + WIDTH / 2;
  double y_projection = HEIGHT / 2 - (d * y) / z;

  return create_point(x_projection, y_projection, 0.0);
}

