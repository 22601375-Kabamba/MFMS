#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>


void   readLine(const char *prompt, char *buf, size_t size);
void   readNonEmpty(const char *prompt, char *buf, size_t size);
int    readInt(const char *prompt, int min, int max);
double readDouble(const char *prompt, double min, double max);

void trimString(char *s);
void toLowerString(char *dst, const char *src, size_t size);
void toUpperString(char *s);
int  equalsIgnoreCase(const char *a, const char *b);
int  containsIgnoreCase(const char *haystack, const char *needle);


void printLine(char c, int n);
void printHeading(const char *title);
void pauseScreen(void);

#endif