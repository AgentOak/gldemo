#ifndef UTIL_H
#define UTIL_H

#include "master.h"

/**
 * @brief sprintf for strings.
 *
 * Takes a format string and any number of the same arguments @c sprintf takes.
 *
 * Necessary memory is allocated and must be free'd using the @c FREESTR macro.
 *
 * Does not tage @c string as arguments! string must be unwrapped by accessing the @c str member.
 */
string strprintf(const char *format, ...) FORMAT(1, 2);

/**
 * @brief Fully read a file into memory.
 *
 * Opens the file specified by the given @p fileName read-only and fully reads it into memory.
 *
 * Necessary memory is allocated and must be free'd using the @c FREESTR macro.
 *
 * Reading an empty file will result in a string with @c (len == 0),
 * but a valid non-null @c str pointer (pointing directly to '\0').
 * If the file could not be read for any reason, @c NULLSTR is returned
 */
string readFile(string fileName);

#endif /* UTIL_H */
