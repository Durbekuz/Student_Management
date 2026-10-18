#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "utils.h"

void clearInputLine(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {}
}

int readInt(const char *prompt) {
    char line[128];
    char *end;
    long value;

    for (;;) {
        printf("%s", prompt);
        if (!fgets(line, sizeof line, stdin)) return 0;
        if (!strchr(line, '\n') && !feof(stdin)) clearInputLine();

        errno = 0;
        value = strtol(line, &end, 10);
        while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n') end++;

        if (end != line && *end == '\0' && errno == 0 &&
            value >= -2147483647L - 1 && value <= 2147483647L) {
            return (int)value;
        }
        puts("Xato: butun son kiriting.");
    }
}

float readFloat(const char *prompt) {
    char line[128];
    char *end;
    float value;

    for (;;) {
        printf("%s", prompt);
        if (!fgets(line, sizeof line, stdin)) return 0.0f;
        if (!strchr(line, '\n') && !feof(stdin)) clearInputLine();

        errno = 0;
        value = strtof(line, &end);
        while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n') end++;

        if (end != line && *end == '\0' && errno == 0) return value;
        puts("Xato: son kiriting (masalan, 85.5).");
    }
}

void readText(const char *prompt, char *buffer, int size) {
    size_t len;
    for (;;) {
        printf("%s", prompt);
        if (!fgets(buffer, size, stdin)) {
            buffer[0] = '\0';
            return;
        }
        len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        } else if (!feof(stdin)) {
            clearInputLine();
        }

        /* File format uses | as a separator; reject it in text fields. */
        if (strchr(buffer, '|') != NULL) {
            puts("'|' belgisidan foydalanmang.");
            continue;
        }
        if (buffer[0] == '\0') {
            puts("Bu maydon bo'sh bo'lmasligi kerak.");
            continue;
        }
        return;
    }
}
