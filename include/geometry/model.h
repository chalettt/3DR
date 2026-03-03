#ifndef MODEL_H
#define MODEL_H

#include "geometry/face.h"

/**
 * @brief Default buffer size for retrieving data from wavefront files.
 */
#define BUFFER_SIZE 1024

/**
 * @brief Structure to hold data relative to the loaded model.
 */
typedef struct model
{
    Face **faces;
    Point *origin;
} Model;

/**
 * @brief Loads a model.
 *
 * @param path The path to the wavefront file.
 * @param origin The origin of the model.
 * @return The loaded model.
 */
Model *load_model(char *path, Point *origin);

/**
 * @brief Destroys (frees) a model.
 *
 * @param model The model to destroy.
 */
void destroy_model(Model *model);

/**
 * @brief Rotates a model.
 *
 * @param model The model to rotate.
 * @param alpha The angle to rotate the model by.
 */
void rotate_model(Model *model, double alpha);

#endif /* MODEL_H*/
