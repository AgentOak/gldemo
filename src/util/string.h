#ifndef UTIL_STRING_H
#define UTIL_STRING_H

#include "../master.h"

#include "alloc.h"

/**
 * Poor man's immutable string library. See util/string.h for utility string functions.
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
typedef struct string {
    size_t len;
    const char *str;
} string;

#define STR(x) ((string) { .len = sizeof(x) - 1, .str = (x) })
#define NULLSTR ((string) { .len = 0, .str = NULL })
#define FREESTR(x) safe_free((void *) (x).str);

/**
 * @brief Construct a string from the given NULL-terminated character array.
 *
 * Given character data is NOT copied and should not be modified afterwards or free'd.
 * The string should be free'd using the @c FREESTR macro, which will free the character data.
 *
 * If a null pointer is passed for @c str, the @c NULLSTR will be returned.
 */
string wrapString(const char *str);

/**
 * @brief Construct a string from the given character array and length.
 *
 * Given character data is copied and can safely be modified afterwards or free'd.
 * The string should be free'd using the @c FREESTR macro.
 *
 * If a null pointer is passed for @c str, the @c NULLSTR will be returned.
 */
string copyString(size_t length, const char *str);

/**
 * @brief sprintf for strings.
 *
 * Takes a format string and any number of the same arguments @c sprintf takes.
 *
 * Necessary memory is allocated and must be free'd using the @c FREESTR macro.
 *
 * Does not take @c string as arguments! string must be unwrapped by accessing the @c str member.
 */
string printfString(const char *format, ...) ATTR_FORMAT(1, 2) ATTR_NONNULL(1);

#endif /* UTIL_STRING_H */
