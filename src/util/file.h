#ifndef UTIL_FILE_H
#define UTIL_FILE_H

#include "../master.h"

#include "string.h"

/**
 * @brief Fully read a file into memory.
 *
 * Opens the file specified by the given @p fileName read-only and fully reads it into memory.
 *
 * Necessary memory is allocated and must be free'd using the @c FREESTR macro.
 *
 * Reading an empty file will result in a string with @c (len == 0),
 * but a valid non-null @c str pointer (pointing directly to '\0').
 */
string readFile(string fileName);

/**
 * Represents a read-only memory mapping. See @c mapFile and @c unmapFile.
 */
typedef struct mapping {
    size_t len;
    const void *addr;
} mapping;

/**
 * @brief Map a file into memory.
 *
 * Opens the file specified by the given @p fileName read-only and maps it into memory.
 *
 * The returned memory region is read-only.
 *
 * The allocated memory region should be free'd using @c unmapFile.
 */
mapping mapFile(string fileName);

/**
 * @brief Unmap a previously memory-mapped file.
 *
 * Unmaps a mapping created from @c mapFile.
 */
void unmapFile(mapping map);

#endif /* UTIL_FILE_H */
