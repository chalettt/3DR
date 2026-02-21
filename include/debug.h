#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>

#define LOG_RED "\x1B[31m"
#define LOG_YELLOW "\x1B[33m"
#define LOG_GREEN "\x1B[32m"

// Macros for logs and errors output.
#define ERROR(FORMAT, ...) fprintf(stderr, LOG_RED "cube: *** " FORMAT "\n", ##__VA_ARGS__)
#define WARN(FORMAT, ...) fprintf(stdout, LOG_YELLOW "cube: " FORMAT "\n", ##__VA_ARGS__)
#define LOG(FORMAT, ...) fprintf(stdout, LOG_GREEN "cube: " FORMAT "\n", ##__VA_ARGS__)

#endif /* ! DEBUG_H */
