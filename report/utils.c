#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <math.h>
#include "utils.h"

void trimString(char *s)
{
    size_t len = strlen(s);
    size_t start = 0;

    while (len > 0 && isspace((unsigned char)s[len - 1])) {
        s[--len] = '\0';
    }
    while (s[start] != '\0' && isspace((unsigned char)s[start])) {
        start++;
    }
    if (start > 0) {
        memmove(s, s + start, strlen(s + start) + 1);
    }
}



void readLine(const char *prompt, char *buf, size_t size)
{
    printf("%s", prompt);
    fflush(stdout);

    if (fgets(buf, (int)size, stdin) == NULL) {
        printf("\nInput closed. Exiting.\n");
        exit(0);
    }
    if (strchr(buf, '\n') == NULL) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
            /* discard */
        }
    }
    buf[strcspn(buf, "\n")] = '\0';
    trimString(buf);
}

void readNonEmpty(const char *prompt, char *buf, size_t size)
{
    for (;;) {
        readLine(prompt, buf, size);
        if (strlen(buf) > 0) {
            return;
        }
        printf("  [!] This field cannot be empty. Please try again.\n");
    }
}

int readInt(const char *prompt, int min, int max)
{
    char buf[64];
    char *end;
    long value;

    for (;;) {
        readLine(prompt, buf, sizeof(buf));
        if (strlen(buf) == 0) {
            printf("  [!] Input cannot be empty.\n");
            continue;
        }
        errno = 0;
        value = strtol(buf, &end, 10);
        if (*end != '\0' || errno == ERANGE) {
            printf("  [!] Invalid number. Please enter a whole number.\n");
            continue;
        }
        if (value < min || value > max) {
            if (min == -2147483647 - 1 && max == 2147483647) {
                return (int)value;
            }
            printf("  [!] Value must be between %d and %d.\n", min, max);
            continue;
        }
        return (int)value;
    }
}

double readDouble(const char *prompt, double min, double max)
{
    char buf[64];
    char *end;
    double value;

    for (;;) {
        readLine(prompt, buf, sizeof(buf));
        if (strlen(buf) == 0) {
            printf("  [!] Input cannot be empty.\n");
            continue;
        }
        errno = 0;
        value = strtod(buf, &end);
        if (*end != '\0' || errno == ERANGE || !isfinite(value)) {
            printf("  [!] Invalid number. Please enter a numeric value.\n");
            continue;
        }
        if (value < min || value > max) {
            printf("  [!] Value must be between %.2f and %.2f.\n", min, max);
            continue;
        }
        return value;
    }
}

void toLowerString(char *dst, const char *src, size_t size)
{
    size_t i;
    for (i = 0; i + 1 < size && src[i] != '\0'; i++) {
        dst[i] = (char)tolower((unsigned char)src[i]);
    }
    dst[i] = '\0';
}

void toUpperString(char *s)
{
    size_t i;
    for (i = 0; s[i] != '\0'; i++) {
        s[i] = (char)toupper((unsigned char)s[i]);
    }
}

int equalsIgnoreCase(const char *a, const char *b)
{
    char la[256], lb[256];
    toLowerString(la, a, sizeof(la));
    toLowerString(lb, b, sizeof(lb));
    return strcmp(la, lb) == 0;
}

int containsIgnoreCase(const char *haystack, const char *needle)
{
    char lh[256], ln[256];
    toLowerString(lh, haystack, sizeof(lh));
    toLowerString(ln, needle, sizeof(ln));
    return strstr(lh, ln) != NULL;
}

void printLine(char c, int n)
{
    int i;
    for (i = 0; i < n; i++) {
        putchar(c);
    }
    putchar('\n');
}

void printHeading(const char *title)
{
    printf("\n");
    printLine('=', 60);
    printf("%s\n", title);
    printLine('=', 60);
}

void pauseScreen(void)
{
    char tmp[8];
    readLine("\nPress ENTER to continue...", tmp, sizeof(tmp));
}