#ifndef CAMERA_H
#define CAMERA_H

#include "point.h"

typedef struct camera
{
    Point *position;
    Point *look_ahead;
    double yaw;
    double pitch;
} Camera;

extern Camera *camera;

Point *move_camera(Direction d, double delta);
Point *rotate_camera_x(double alpha, double delta);
Point *rotate_camera_y(double alpha, double delta);

#endif /* CAMERA_H */
