#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers.h"

char* EXAMPLE_INPUT[] = {
    "Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green",
    "Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue",
    "Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red",
    "Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red",
    "Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green",
    NULL
};

#define EXAMPLE_RESULT 8

#define EXAMPLE_RESULT_2 2286

#define MAX_CUBES 16

typedef struct {
    int r;
    int g;
    int b;
} Cubes;

int read_game_cubes(char **line, Cubes cubes[MAX_CUBES]) {
    int count = 0;
    int n;

    while (**line) {
        n = strtol(*line, line, 10);
        assert(**line == ' ');
        ++(*line); // Skip space

        if (**line == 'r') {
            cubes[count].r = n;
            *line += strlen("red");
        } else if (**line == 'g') {
            cubes[count].g = n;
            *line += strlen("green");
        } else if (**line == 'b') {
            cubes[count].b = n;
            *line += strlen("blue");
        } else {
            assert(0 && "Unreachable");
        }

        if (**line == ',' || **line == ';') {
            if (**line == ';') ++count;

            ++(*line);
        }
    }

    ++count;
    return count;
}

int read_game_id(char **line) {
    // Read XX from "Game XX: ..."
    int id;

    *line += strlen("Game");
    id = strtol(*line, line, 10);
    ++(*line); // Consume ':'

    return id;
}

void part1(Result *result, char **lines) {
    int cube_count;
    int possible;
    int id;

    int sum = 0;
    for (char *line = *lines; *lines; line = *(++lines)) {
        Cubes cubes[MAX_CUBES] = {0};

        if (*line == '\0') break; // Filter out empty lines that appear at the end of the file

        id = read_game_id(&line);

        cube_count = read_game_cubes(&line, cubes);

        possible = 1;
        for (int i = 0; i < cube_count && possible; ++i) {
            possible = (cubes[i].r <= 12 && cubes[i].g <= 13 && cubes[i].b <= 14);
        }

        if (possible) sum += id;
    }

    result->integer = sum;
}

void part2(Result *result, char **lines) {
    int cube_count;

    int sum = 0;
    for (char *line = *lines; *lines; line = *(++lines)) {
        Cubes cubes[MAX_CUBES] = {0};
        int max_r = 0;
        int max_g = 0;
        int max_b = 0;

        if (*line == '\0') break; // Filter out empty lines that appear at the end of the file

        read_game_id(&line); // Consume game ID

        cube_count = read_game_cubes(&line, cubes);

        for (int i = 0; i < cube_count; ++i) {
            if (cubes[i].r > max_r) max_r = cubes[i].r;
            if (cubes[i].g > max_g) max_g = cubes[i].g;
            if (cubes[i].b > max_b) max_b = cubes[i].b;
        }

        sum += max_r * max_g * max_b;
    }

    result->integer = sum;
}

int main() {
    char **input_lines;
    Result result;

    input_lines = read_lines_from_file("input.txt");

    printf("----- PART 1 -----\n");
    check_example_int(part1, EXAMPLE_INPUT, EXAMPLE_RESULT);
    part1(&result, input_lines);
    printf("Sum of ID of valid games: %d\n\n", result.integer);

    printf("----- PART 2 -----\n");
    check_example_int(part2, EXAMPLE_INPUT, EXAMPLE_RESULT_2);
    part2(&result, input_lines);
    printf("Sum of power of sets: %d\n", result.integer);

    free(*input_lines);
    free(input_lines);

    return 0;
}

