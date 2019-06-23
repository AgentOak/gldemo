#ifndef UTIL_STRING_H
#define UTIL_STRING_H

#include "../master.h"

#include <stdarg.h>

/**
 * Poor man's immutable string library.
 *
 * Character arrays pointed to by str are still NULL-terminated, allowing easy use in standard library.
 *
 * Example usage:
 * @code
 * string name = printfString("foo://%s", argv[0]);
 * string contents = doSomething(name);
 * if (contents.str) {
 *     printf(contents.str);
 * }
 * FREESTRING(contents);
 * FREESTRING(name);
 * @endcode
 *
 * The @c STRING macro can be used to create a string at compile-time,
 * the @c wrapString function to wrap a @c char* into a string at runtime.
 *
 * A null string is represented by @c (.str == NULL), in which case the length has no meaning (but should be @c 0).
 * The @c NULLSTRING macro can be used to obtain such a string.
 */
typedef struct string {
    size_t len;
    const char *str;
} string;

#define STRING(x) ((string) { .len = sizeof(x) - 1, .str = (x) })
#define NULLSTRING ((string) { .len = 0, .str = NULL })
#define FREESTRING(x) safe_free((void *) (x).str);

/**
 * @brief Construct a string from the given NULL-terminated character array.
 *
 * Given character data is NOT copied and should not be modified afterwards or free'd.
 * The string should be free'd using the @c FREESTRING macro, which will free the character data.
 *
 * If a null pointer is passed for @c str, the @c NULLSTRING will be returned.
 */
string wrapString(const char *str);

/**
 * @brief Construct a string from the given character array and length.
 *
 * Given character data is copied and can safely be modified afterwards or free'd.
 * The string should be free'd using the @c FREESTR macro.
 *
 * If a null pointer is passed for @c str, the @c NULLSTRING will be returned.
 */
string copyString(size_t length, const char *str);

/**
 * @brief sprintf for strings.
 *
 * Takes a format string and any number of the same arguments @c sprintf takes.
 *
 * Necessary memory is allocated and must be free'd using the @c FREESTRING macro.
 *
 * Does not take @c string as arguments! string must be unwrapped by accessing the @c str member.
 */
string printfString(const char *format, ...) ATTR_FORMAT(1, 2) ATTR_NONNULL(1);

string vprintfString(const char *format, va_list args) ATTR_NONNULL(1);

#endif /* UTIL_STRING_H */
