#ifndef POINT_H
#define POINT_H

typedef enum direction
{
    LEFT,
    RIGHT,
    UP,
    DOWN,
    FRONT,
    BACK,
} Direction;

typedef struct point
{
    double x, y, z;
} Point;

Point *create_point(double x, double y, double z);
Point *add_point(Point *a, Point *b);
Point *sub_point(Point *a, Point *b);
Point *scalar_product(Point *p, double scalar);
Point *dup_point(Point *p);
Point *add_dir(Point *p, Direction d, double delta);
Point *project(Point *point);
Point *rotate_point_z(Point *point, Point *origin, double alpha);
Point *rotate_point_y(Point *point, Point *origin, double alpha);
Point *rotate_point_x(Point *point, Point *origin, double alpha);
void dump_point(Point *point);

#endif /* POINT_H */
