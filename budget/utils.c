#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

void printHeading(const char *heading) {
    printf("\n--- %s ---\n", heading);
}

void pauseScreen(void) {
    printf("\nPress Enter to continue...");
    getchar();
}

int equalsIgnoreCase(const char *str1, const char *str2) {
    while (*str1 && *str2) {
        if (tolower((unsigned char)*str1) != tolower((unsigned char)*str2)) return 0;
        str1++; str2++;
    }
    return *str1 == *str2;
}

static void readLine(char *buf, size_t size)
{
    size_t len;

    if (fgets(buf, (int)size, stdin) == NULL) {
        printf("\nInput closed. Exiting.\n");
        exit(0);
    }
    len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n') {
        buf[len - 1] = '\0';
    } else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    }
}

void readNonEmpty(const char *prompt, char *buffer, size_t bufferSize)
{
    size_t i;

    for (;;) {
        printf("%s", prompt);
        readLine(buffer, bufferSize);
        for (i = 0; buffer[i] != '\0'; i++) {
            if (!isspace((unsigned char)buffer[i]))
                return;
        }
        printf("  [!] This field cannot be empty.\n");
    }
}

int readInt(const char *prompt, int min, int max)
{
    char line[64];
    char *end;
    long v;

    for (;;) {
        printf("%s", prompt);
        readLine(line, sizeof line);
        errno = 0;
        v = strtol(line, &end, 10);
        if (end == line) {
            printf("  [!] Invalid input. Enter a whole number.\n");
            continue;
        }
        while (isspace((unsigned char)*end))
            end++;
        if (*end != '\0') {
            printf("  [!] Invalid input. Enter a number only.\n");
            continue;
        }
        if (errno == ERANGE || v < min || v > max) {
            printf("  [!] Number must be between %d and %d.\n", min, max);
            continue;
        }
        return (int)v;
    }
}

double readDouble(const char *prompt, double min, double max)
{
    char line[64];
    char *end;
    double v;

    for (;;) {
        printf("%s", prompt);
        readLine(line, sizeof line);
        errno = 0;
        v = strtod(line, &end);
        if (end == line) {
            printf("  [!] Invalid input. Enter a number.\n");
            continue;
        }
        while (isspace((unsigned char)*end))
            end++;
        if (*end != '\0' || !isfinite(v)) {
            printf("  [!] Invalid input. Enter a number only.\n");
            continue;
        }
        if (errno == ERANGE || v < min || v > max) {
            printf("  [!] Amount must be between %.2f and %.2f.\n", min, max);
            continue;
        }
        return v;
    }
}
