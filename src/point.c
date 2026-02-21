#include "point.h"

#include <math.h>
#include <stdlib.h>

#include "camera.h"
#include "debug.h"
#include "sdl_manager.h"
#include "vector.h"

Point *create_point(double x, double y, double z)
{
    Point *point = malloc(sizeof(Point));
    if (!point)
        return ERROR("Could not create point->"), NULL;

    point->x = x;
    point->y = y;
    point->z = z;

    return point;
}

Point *add_point(Point *a, Point *b)
{
    a->x += b->x;
    a->y += b->y;
    a->z += b->z;

    return a;
}

Point *sub_point(Point *a, Point *b)
{
    a->x -= b->x;
    a->y -= b->y;
    a->z -= b->z;

    return a;
}

Point *scalar_product(Point *p, double scalar)
{
    p->x *= scalar;
    p->y *= scalar;
    p->z *= scalar;

    return p;
}

Point *dup_point(Point *p)
{
    return create_point(p->x, p->y, p->z);
}

Point *add_dir(Point *p, Direction d, double delta)
{
    switch (d)
    {
    case RIGHT:
        p->x += delta;
        break;
    case LEFT:
        p->x -= delta;
        break;
    case UP:
        p->y += delta;
        break;
    case DOWN:
        p->y -= delta;
        break;
    case FRONT:
        p->z += delta;
        break;
    case BACK:
        p->z -= delta;
        break;
    }

    return p;
}

Point *project(Point *point)
{
    double fov = 90.0;
    double d = WIDTH / 2 * tan(fov / 2);

    // HANK DO NOT ABREVIATE CAMERA POSITION TO CP!
    Point *cp = dup_point(camera->position);
    Point *cl = dup_point(camera->look_ahead);

    Point *forward = vector_normalize(sub_point(cl, cp));
    Point *word_up = create_point(0, 1, 0);
    Point *cross = vector_cross(word_up, forward);
    Point *right = vector_normalize(cross);
    Point *up = vector_cross(forward, right);

    Point *p = dup_point(point);
    Point *rel = sub_point(p, cp);

    double x = dot_product(rel, right);
    double y = dot_product(rel, up);
    double z = dot_product(rel, forward);

    free(cp);
    free(cl);
    free(forward);
    free(word_up);
    free(cross);
    free(right);
    free(up);
    free(p);

    if (z < 0.01)
        return NULL;

    double projection_x = d * x / z + WIDTH / 2;
    double projection_y = HEIGHT / 2 - d * y / z;

    return create_point(projection_x, projection_y, z);
}

// Rotates a point by an angle alpha along the Z axis according to the origin
// point.
Point *rotate_point_z(Point *point, Point *origin, double alpha)
{
    double x = point->x - origin->x;
    double y = point->y - origin->y;
    double z = point->z - origin->z;

    double new_x = x * cos(alpha) - y * sin(alpha);
    double new_y = x * sin(alpha) + y * cos(alpha);

    point->x = new_x + origin->x;
    point->y = new_y + origin->y;
    point->z = z + origin->z;

    return point;
}

// Rotates a point by an angle alpha along the Y axis according to the origin
// point.
Point *rotate_point_y(Point *point, Point *origin, double alpha)
{
    double x = point->x - origin->x;
    double y = point->y - origin->y;
    double z = point->z - origin->z;

    double new_x = x * cos(alpha) + z * sin(alpha);
    double new_z = -x * sin(alpha) + z * cos(alpha);

    point->x = new_x + origin->x;
    point->y = y + origin->y;
    point->z = new_z + origin->z;

    return point;
}

// Rotates a point by an angle alpha along the X axis according to the origin
// point.
Point *rotate_point_x(Point *point, Point *origin, double alpha)
{
    double x = point->x - origin->x;
    double y = point->y - origin->y;
    double z = point->z - origin->z;

    double new_y = y * cos(alpha) - z * sin(alpha);
    double new_z = y * sin(alpha) + z * cos(alpha);

    point->x = x + origin->x;
    point->y = new_y + origin->y;
    point->z = new_z + origin->z;

    return point;
}

void dump_point(Point *point)
{
    LOG("Point(x: %f; y: %f; z: %f)\n", point->x, point->y, point->z);
}
