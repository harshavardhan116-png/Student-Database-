#include "student_db.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void read_line(const char *prompt, char *buffer, size_t size)
{
    int ch;
    size_t len;

    if (prompt != NULL) {
        printf("%s", prompt);
        fflush(stdout);
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }

    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else {
        while ((ch = getchar()) != '\n' && ch != EOF) {
            /* Discard remaining characters from an overlong input line. */
        }
    }
}

int read_int(const char *prompt, int min, int max)
{
    char line[64], *end;
    long value;

    for (;;) {
        read_line(prompt, line, sizeof line);
        value = strtol(line, &end, 10);
        while (isspace((unsigned char)*end)) {
            ++end;
        }
        if (line[0] != '\0' && *end == '\0' && value >= min && value <= max) {
            return (int)value;
        }
        printf("Invalid choice. Enter a number from %d to %d.\n", min, max);
    }
}

float read_percentage(const char *prompt)
{
    char line[64], *end;
    float value;

    for (;;) {
        read_line(prompt, line, sizeof line);
        value = strtof(line, &end);
        while (isspace((unsigned char)*end)) {
            ++end;
        }
        if (line[0] != '\0' && *end == '\0' && value >= 0.0f && value <= 100.0f) {
            return value;
        }
        puts("Invalid percentage. Enter a value from 0 to 100.");
    }
}
