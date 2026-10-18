#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

// These match the visual UI layouts your code calls
void printHeading(const char *heading);
void pauseScreen(void);

// This matches your string matching check
int equalsIgnoreCase(const char *str1, const char *str2);

// These match your safe-input validation functions
void readNonEmpty(const char *prompt, char *buffer, size_t bufferSize);
int readInt(const char *prompt, int min, int max);
double readDouble(const char *prompt, double min, double max);

#endif // UTILS_H