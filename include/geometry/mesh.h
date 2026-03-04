#ifndef MESH_H
#define MESH_H

#include "geometry/triangle.h"

/**
 * @brief Default buffer size for retrieving data from wavefront files.
 */
#define BUFFER_SIZE 4096

/**
 * @brief Structure to hold data relative to the loaded mesh.
 */
typedef struct mesh
{
    Point **vertices;
    Triangle **triangles;
    Point *origin;
} Mesh;

extern Mesh *mesh;

/**
 * @brief Loads a mesh.
 *
 * @param path The path to the wavefront file.
 * @param origin The origin of the mesh.
 * @return The loaded mesh.
 */
Mesh *load_mesh(char *path, Point *origin);

/**
 * @brief Destroys (frees) a mesh.
 *
 * @param mesh The mesh to destroy.
 */
void destroy_mesh(Mesh *mesh);

/**
 * @brief Rotates a mesh.
 *
 * @param mesh The mesh to rotate.
 * @param alpha The angle to rotate the mesh by.
 */
void rotate_mesh(Mesh *mesh, double alpha);

#endif /* mesh_H*/
