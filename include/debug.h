#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>

// Macros for logs and errors output.
#define ERROR(FORMAT, ...) fprintf(stderr, "cube: *** " FORMAT, ##__VA_ARGS__)
#define LOG(FORMAT, ...) fprintf(stdout, "cube: " FORMAT, ##__VA_ARGS__)

#endif /* ! DEBUG_H */
