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
    "Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green"
};

#define EXAMPLE_RESULT 8

int determine_possible(char **input, int max_r, int max_g, int max_b) {
    int n;
    int fail = 0;

    while (1) {
        n = strtol(*input, input, 10);
        assert(**input == ' ');
        ++(*input); // Skip space

        if (**input == 'r') {
            fail = (n > max_r);
            *input += strlen("red");
        } else if (**input == 'g') {
            fail = (n > max_g);
            *input += strlen("green");
        } else if (**input == 'b') {
            fail = (n > max_b);
            *input += strlen("blue");
        } else {
            assert(0 && "Unreachable");
        }

        if (fail) {
            return 0;
        }

        if (**input == '\0') {
            break;
        }

        assert(**input == ',' || **input == ';');
        ++(*input); // Skip ',' or ';'
    }

    return 1;
}

void part1(Result *result, char **lines) {
    int id;

    int sum = 0;
    for (char *line = *lines; *lines; line = *(++lines)) {
        if (*line == '\0') break; // Filter out empty lines that appear at the end of the file

        line += strlen("Game");
        id = strtol(line, &line, 10);
        ++line; // Consume ':'

        if (determine_possible(&line, 12, 13, 14)) {
            sum += id;
        }
    }

    result->integer = sum;
}

void part2(Result *result, char *input) {
    result->integer = 0;
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
    //check_example_int(part2, EXAMPLE_INPUT_2, EXAMPLE_RESULT_2);
    //part2(&result, input);
    printf("Part 2 TBD\n");

    free(*input_lines);
    free(input_lines);

    return 0;
}

