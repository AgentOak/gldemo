#ifndef UTIL_H
#define UTIL_H

#include <string.h>

/**
 * Character arrays pointed to by str are still NULL-terminated, allowing easy use in standard library.
 */
typedef struct {
    size_t len;
    char *str;
} string;

#define STR(x) ((string) { .len = sizeof(x) - 1, .str = x })

/**
 * @brief Construct a string from the given NULL-terminated character array.
 */
string str(char *str);

/**
 * @brief Fully read a file into memory.
 *
 * Opens the file specified by the given @p fileName read-only and fully reads it into memory.
 * Memory must be freed manually.
 *
 * @return if the file could not be read for any reason, an empty string is returned
 */
string readFile(char *fileName);

// TODO: Texture loading

// TODO: Model loading

#endif /* UTIL_H */
