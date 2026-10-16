#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
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

void readNonEmpty(const char *prompt, char *buffer, size_t bufferSize) {
    printf("%s", prompt);
    scanf("%s", buffer);
}

int readInt(const char *prompt, int min, int max) {
    int val;
    printf("%s", prompt);
    scanf("%d", &val);
    return val;
}

double readDouble(const char *prompt, double min, double max) {
    double val;
    printf("%s", prompt);
    scanf("%lf", &val);
    return val;
}