#ifndef MODEL_H
#define MODEL_H

#include "geometry/face.h"

#define FACE_COUNT 32768
#define VERTEX_COUNT 32768

typedef struct model
{
    Face **faces;
    Point *origin;
} Model;

Model *load_model(char *path);
void destroy_model(Model *model);
void rotate_model(Model *model, double alpha);

#endif /* MODEL_H*/
