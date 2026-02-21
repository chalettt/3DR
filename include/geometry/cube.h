#ifndef CUBE_H
#define CUBE_H

#include "geometry/vertex.h"

/**
 * @brief Cube structure to store each vertices and its position.
 */
typedef struct cube
{
    Vertex **vertices;
    Point *position;
} Cube;

/**
 * @brief Creates a cube.
 *
 * @param size The size for each sides.
 * @param origin The center of the cube.
 * @return The created cube.
 */
Cube *create_cube(int size, Point *origin);

/**
 * @brief Rotates a cube on the Y axis.
 *
 * @param cube The cube to rotate.
 * @param origin The point to rotate the cube around of.
 * @param alpha The angle of the rotation.
 */
void rot_cube_y(Cube *cube, Point *origin, double alpha);

/**
 * @brief Rotates a cube on the X axis.
 *
 * @param cube The cube to rotate.
 * @param origin The point to rotate the cube around of.
 * @param alpha The angle of the rotation.
 */
void rot_cube_x(Cube *cube, Point *origin, double alpha);

/**
 * @brief Destroys a cube.
 *
 * @param cube The cube to destroy.
 */
void destroy_cube(Cube *cube);

#endif /* ! CUBE_H */
