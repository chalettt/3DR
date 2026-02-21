#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>

/**
 * @brief Red logging color.
 */
#define LOG_RED "\x1B[31m"

/**
 * @brief Yellow logging color.
 */
#define LOG_YELLOW "\x1B[33m"

/**
 * @brief Green logging color.
 */
#define LOG_GREEN "\x1B[32m"

/**
 * @brief Logs an error in red on stderr.
 */
#define ERROR(FORMAT, ...)                                                     \
    fprintf(stderr, LOG_RED "cube: *** " FORMAT "\n", ##__VA_ARGS__)

/**
 * @brief Logs a warning in yellow on stdout.
 */
#define WARN(FORMAT, ...)                                                      \
    fprintf(stdout, LOG_YELLOW "cube: " FORMAT "\n", ##__VA_ARGS__)

/**
 * @brief Logs a message in blue on stdout.
 */
#define LOG(FORMAT, ...)                                                       \
    fprintf(stdout, LOG_GREEN "cube: " FORMAT "\n", ##__VA_ARGS__)

#endif /* ! DEBUG_H */
