// (Santa's) helpers

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers.h"

#define MSG_BUF_SIZE 256

void check_example_int(Solver *solver, char **lines, int expected) {
    Result result;

    printf("Checking example input...\n");
    solver(&result, lines);

    if (result.integer != expected) {
        fprintf(stderr, "Expected %d, but got %d\n", expected, result.integer);
        exit(1);
    }

    printf("Example input passed!\n\n");
}

void check_example_str(Solver *solver, char **lines, char *expected) {
    Result result;

    printf("Checking example input...\n");
    solver(&result, lines);

    if (strcmp(result.string, expected)) {
        fprintf(stderr, "Expected '%s', but got '%s\n'", expected, result.string);
    }

    printf("Example input passed!\n\n");
}

char* read_entire_file(char *filename) {
    FILE *f = fopen(filename, "r");
    char msg_buf[MSG_BUF_SIZE];
    char *data;
    long size;

    if (!f) {
        snprintf(msg_buf, MSG_BUF_SIZE, "Unable to open %s", filename);
        perror(msg_buf);
        exit(1);
    }

    fseek(f, 0, SEEK_END);
    size = ftell(f);
    assert(size > 0);
    fseek(f, 0, SEEK_SET);

    if ((data = malloc(size + 1)) == NULL) {
        perror("Could not allocate memory for input data");
        exit(1);
    }

    if (fread(data, 1, size, f) != size) {
        snprintf(msg_buf, MSG_BUF_SIZE, "Error reading %s", filename);
        perror(msg_buf);
        exit(1);
    }

    data[size] = '\0';

    return data;
}

char** read_lines_from_file(char *filename) {
    char *data;
    char *buf;
    int count = 0;
    int capacity = 256;
    char **lines = malloc(capacity * sizeof(*lines));

    if (lines == NULL) {
        perror("Could not allocate memory for input lines");
        exit(1);
    }

    data = read_entire_file(filename);

    lines[count++] = data;
    for (buf = data; *buf; ++buf) {
        if (*buf == '\n') {
            *buf = '\0'; // Yep. Modify in place

            if (count >= capacity) {
                capacity *= 2;
                lines = realloc(lines, capacity * sizeof(*lines));
            }
            lines[count++] = buf + 1;
        }
    }

    if (count >= capacity) {
        ++capacity;
        lines = realloc(lines, capacity * sizeof(*lines));
    }
    lines[count++] = NULL; // Terminate with NULL pointer

    return lines;
}

