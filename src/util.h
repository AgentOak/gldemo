#ifndef UTIL_H
#define UTIL_H

/**
 * @brief Fully read a file into memory.
 *
 * Opens the file specified by the given @p fileName read-only and fully reads it into memory.
 * Returns a pointer to the first byte of the file. Memory must be freed manually.
 *
 * @return @c NULL if the file could not be read for any reason
 */
extern char *readFile(char *fileName);

// TODO: Texture loading

// TODO: Model loading

#endif /* UTIL_H */
