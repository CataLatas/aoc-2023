#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers.h"

char* EXAMPLE_INPUT[] = {
    "467..114..",
    "...*......",
    "..35..633.",
    "......#...",
    "617*......",
    ".....+.58.",
    "..592.....",
    "......755.",
    "...$.*....",
    ".664.598..",
    NULL
};

#define EXAMPLE_RESULT 4361

int is_symbol_at(char **lines, int lin, int col, int length) {
    char c;

    if (col < 0 || col >= length) return 0;
    if (lin < 0 || lines[lin] == NULL) return 0;

    // Absolutely hate those empty lines
    if (lines[lin][0] == '\0') return 0;

    c = lines[lin][col];
    return c != '.' && (c < '0' || c > '9');
}

void part1(Result *result, char **lines) {
    int length = strlen(*lines); // All lines have the same lengths
    int sum = 0;

    for (int lin = 0; lines[lin]; ++lin) {
        char *end;
        char *line_str = lines[lin];
        if (*line_str == '\0') break; // Filter out empty lines at end of input

        for (int col = 0; col < length; ++col) {
            if (line_str[col] >= '0' && line_str[col] <= '9') {
                int is_part_number = 0;
                int number = strtol(line_str+col, &end, 10);

                is_part_number = is_symbol_at(lines, lin, col-1, length) || is_symbol_at(lines, lin, end - line_str, length);

                for (int i = col-1; i <= end - line_str && !is_part_number; ++i) {
                    is_part_number = is_symbol_at(lines, lin-1, i, length) || is_symbol_at(lines, lin+1, i, length);
                }

                if (is_part_number) {
                    sum += number;
                }

                col = end - line_str;
            }
        }
    }

    result->integer = sum;
}

void part2(Result *result, char **lines) {
    result->integer = 0;
}

int main() {
    char **lines;
    Result result;

    lines = read_lines_from_file("input.txt");

    printf("----- PART 1 -----\n");
    check_example_int(part1, EXAMPLE_INPUT, EXAMPLE_RESULT);
    part1(&result, lines);
    printf("Sum of part numbers: %d\n\n", result.integer);

    //printf("----- PART 2 -----\n");
    //check_example_int(part2, EXAMPLE_INPUT, EXAMPLE_RESULT_2);
    //part2(&result, lines);
    //printf("Part 2 TBD\n", result.integer);

    free(*lines);
    free(lines);

    return 0;
}

