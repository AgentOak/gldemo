#ifndef UTIL_H
#define UTIL_H

#include <string.h>

/**
 * Character arrays pointed to by str are still NULL-terminated, allowing easy use in standard library.
 *
 * A null string is represented by @c (.str == NULL).
 */
typedef struct {
    size_t len;
    char *str;
} string;

#define STR(x) ((string) { .len = sizeof(x) - 1, .str = x })
#define NULLSTR ((string) { .len = 0, .str = NULL })

/**
 * @brief Construct a string from the given NULL-terminated character array.
 *
 * No copy of character data is performed. If a null pointer is passed, the NULLSTR will be returned.
 */
string str(char *str);

/**
 * @brief Fully read a file into memory.
 *
 * Opens the file specified by the given @p fileName read-only and fully reads it into memory.
 * Memory allocated for @c str must be freed manually.
 *
 * @return if the file could not be read for any reason, an empty string is returned
 */
string readFile(char *fileName);

// TODO: Texture loading

// TODO: Model loading

#endif /* UTIL_H */
