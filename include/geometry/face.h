#ifndef TRIANGE_H
#define TRIANGE_H

#include "geometry/point.h"

/**
 * @brief Structure to hold data of faces.
 */
typedef struct face
{
    Point **points;
    Point *normal;
} Face;

/**
 * @brief Creates a face.
 *
 * @param points The array of points which defines a face.
 * @return The created face.
 */
Face *create_face(Point **points);

/**
 * @brief Destroys (frees) a face.
 *
 * @param face The face to destroy.
 */
void destroy_face(Face *face);

/**
 * @brief Calculates the normal of a face.
 *
 * @param face The face to calculate the normal of.
 * @return The face normal.
 */
Point *get_face_normal(Face *face);

#endif /* TRIANGE_H */
