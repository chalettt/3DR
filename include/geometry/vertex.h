#ifndef VERTEX_H
#define VERTEX_H

#include "geometry/point.h"
#include "rendering/sdl_manager.h"

/**
 * @brief Default cube size.
 */
#define CUBE_SIZE 75

/**
 * @brief Linked list for each links a vertex might have to other vertices.
 */
typedef struct links
{
    struct vertex *vertex;
    struct links *next;
} Links;

/**
 * @brief Vertex structure to store its position and links to other vertices.
 */
typedef struct vertex
{
    Point *position;
    Links *links;
} Vertex;

/**
 * @brief Destroys a vertex.
 *
 * @param vertex the vertex to destroy.
 */
void destroy_vertex(Vertex *vertex);

/**
 * @brief Creates a vertex at positin {x, y, z}.
 *
 * @param x X coordinate of the vertex.
 * @param y Y coordinate of the vertex.
 * @param z Z coordinate of the vertex.
 * @return The created vertex.
 */
Vertex *create_vertex(double x, double y, double z);

/**
 * @brief Connects two vertices together.
 *
 * @param a The first vertex.
 * @param b The second vertex.
 */
void connect_vertex(Vertex *a, Vertex *b);

#endif /* ! VERTEX_H */
