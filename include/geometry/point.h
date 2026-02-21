#ifndef POINT_H
#define POINT_H

/**
 * @brief Direction enum to store each of the 6 directions of the world base.
 */
typedef enum direction
{
    LEFT,
    RIGHT,
    UP,
    DOWN,
    FRONT,
    BACK,
} Direction;

/**
 * @brief Point structure to store xyz coordinates of geometry.
 */
typedef struct point
{
    double x, y, z;
} Point;

/**
 * @brief Creates a point.
 *
 * @param x X coordinate of the point.
 * @param y Y coordinate of the point.
 * @param z Z coordinate of the point.
 * @return The created point.
 */
Point *create_point(double x, double y, double z);

/**
 * @brief Adds each coordinate of point b into point a.
 *
 * @param a Term a.
 * @param b Term b.
 * @return Point a.
 */
Point *add_point(Point *a, Point *b);

/**
 * @brief Substracts each coordinate of point b into point a.
 *
 * @param a Term a.
 * @param b Term b.
 * @return Point a.
 */
Point *sub_point(Point *a, Point *b);

/**
 * @brief Multiplies each coordinate of point p by a scalar.
 *
 * @param p The point to be multiplied.
 * @param scalar The scalar to multiply p by.
 * @return Point p.
 */
Point *scalar_product(Point *p, double scalar);

/**
 * @brief Duplicates a point by allocating it on the heap.
 *
 * @param p The point to duplicate.
 * #return The duplicated point.
 */
Point *dup_point(Point *p);

/**
 * @brief Move a point to direction d by delta.
 *
 * @param p The point to move.
 * @param d The direction of the translation.
 * @param delta The amount to translate by.
 * @return The point p.
 */
Point *add_dir(Point *p, Direction d, double delta);

/**
 * @brief Projects a point onto the screen.
 *
 * @param p The point to project.
 * @return The point p.
 */
Point *project(Point *p);

/**
 * @brief Rotates a point according to the Z axis around another point.
 *
 * @param p The point to rotate.
 * @param origin The point to rotate around of.
 * @param alpha The angle of the rotation.
 * @return The point p.
 */
Point *rotate_point_z(Point *p, Point *origin, double alpha);

/**
 * @brief Rotates a point according to the Y axis around another point.
 *
 * @param p The point to rotate.
 * @param origin The point to rotate around of.
 * @param alpha The angle of the rotation.
 * @return The point p.
 */
Point *rotate_point_y(Point *point, Point *origin, double alpha);

/**
 * @brief Rotates a point according to the X axis around another point.
 *
 * @param p The point to rotate.
 * @param origin The point to rotate around of.
 * @param alpha The angle of the rotation.
 * @return The point p.
 */
Point *rotate_point_x(Point *point, Point *origin, double alpha);

/**
 * @brief Logs the coordinates of a point.
 *
 * @param point The point to log.
 */
void dump_point(Point *point);

#endif /* POINT_H */
