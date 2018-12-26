#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>
#include <string.h>

/**
 * Poor man's immutable string library.
 *
 * Character arrays pointed to by str are still NULL-terminated, allowing easy use in standard library.
 *
 * Example usage:
 * @code
 * string fileName = strprintf("foo/%s", argv[0]);
 * string contents = readFile(fileName);
 * if (contents.str) {
 *     printf(contents.str);
 * }
 * FREESTR(contents);
 * FREESTR(fileName);
 * @endcode
 *
 * The @c STR macro can be used to create a string at compile-time,
 * the @c str function to wrap a @c char* into a string at runtime.
 *
 * A null string is represented by @c (.str == NULL), in which case the length has no meaning (but should be @c 0).
 * The @c NULLSTR macro can be used to obtain such a string.
 */
typedef struct {
    const size_t len;
    const char *const str;
} string;

#define STR(x) ((string) { .len = sizeof(x) - 1, .str = (x) })
#define NULLSTR ((string) { .len = 0, .str = NULL })
#define FREESTR(x) free((void*) (x).str);

/**
 * @brief Construct a string from the given NULL-terminated character array.
 *
 * No copy of character data is performed. Characters should not be modified afterwards.
 * If a null pointer is passed, the @c NULLSTR will be returned.
 */
static inline string str(const char *str) {
    size_t length = 0;
    if (str) {
        length = strlen(str);
    }

    return (string) { .len = length, .str = str };
}

/**
 * @brief sprintf for strings.
 *
 * Takes a format string and any number of the same arguments @c sprintf takes.
 *
 * Necessary memory is allocated and must be free'd using the @c FREESTR macro.
 *
 * Does not tage @c string as arguments! string must be unwrapped by accessing the @c str member.
 */
string strprintf(const char *format, ...);

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
