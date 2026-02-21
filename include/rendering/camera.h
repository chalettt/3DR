#ifndef CAMERA_H
#define CAMERA_H

#include "geometry/point.h"

typedef struct camera
{
    Point *position;
    Point *look_ahead;
    double yaw;
    double pitch;
} Camera;

extern Camera *camera;

/**
 * @brief Initializes the camera to be at position {x, y, z}.
 *
 * @param x X coordinate of the camera.
 * @param y Y coordinate of the camera.
 * @param z Z coordinate of the camera.
 * @return The initialized camera.
 */
Camera *init_camera(double x, double y, double z);

/**
 * @brief Move camera to a direction by taking its rotation into account.
 *
 * @param d The direction to move to.
 * @param delta The amount to translate by.
 * @return The camera's new position.
 */
Point *move_camera(Direction d, double delta);

/**
 * @brief Rotates camera according to the X axis.
 *
 * @param alpha The angle of the rotation.
 * @param delta The amount of rotations to be done.
 * @return The look ahead's new position.
 */
Point *rotate_camera_x(double alpha, double delta);

/**
 * @brief Rotates camera according to the Y axis.
 *
 * @param alpha The angle of the rotation.
 * @param delta The amount of rotations to be done.
 * @return The look ahead's new position.
 */
Point *rotate_camera_y(double alpha, double delta);

#endif /* CAMERA_H */
