// (Santa's) helpers

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers.h"

#define MSG_BUF_SIZE 256

void check_example_int(Solver *solver, char *input, int expected) {
    Result result;

    printf("Checking example input...\n");
    solver(&result, input);

    if (result.integer != expected) {
        fprintf(stderr, "Expected %d, but got %d\n", expected, result.integer);
        exit(1);
    }

    printf("Example input passed!\n\n");
}

void check_example_str(Solver *solver, char *input, char *expected) {
    Result result;

    printf("Checking example input...\n");
    solver(&result, input);

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

