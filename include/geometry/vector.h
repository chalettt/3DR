#ifndef VECTOR_H
#define VECTOR_H

#include "geometry/point.h"

/**
 * @brief Normalizes a vector.
 *
 * @param p The vector to normalize.
 * @return The normalized vector.
 */
Point *vector_normalize(Point *p);

/**
 * @brief Computes the cross product of two vectors.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @return The cross product.
 */
Point *vector_cross(Point *a, Point *b);

/**
 * @brief Computes the dot product of two vectors.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @return The dot product.
 */
double dot_product(Point *a, Point *b);

#endif /* VECTOR_H */
