#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers.h"

// TODO: This is a trash solution
// Maybe look into actually using the input as a 2D array

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

int is_symbol(char c) {
    int ok = c != '\0' && c != '.' && (c < '0' || c > '9');
    if (ok) printf("FOUND A SYMBOL '%c' (0x%02X)\n", c, c);

    return ok;
}

// Sum of part numbers on specific line
// "middle" is our current line
int find_part_numbers(char *top, char *middle, char *bottom) {
    int sum = 0;

    char *str_begin = middle;

    while (*middle) {
        char *start_ptr = middle;

        int number;
        int start_index;
        int end_index;
        int is_part_number = 0;

        if (*middle >= '0' && *middle <= '9') {
            number = strtol(middle, &middle, 10);

            start_index = start_ptr - str_begin - 1;
            end_index = start_index + middle - start_ptr + 2;
            for (int i = start_index; i < end_index && !is_part_number; ++i) {
                if (i < 0) continue;

                if (is_symbol(top[i]) || is_symbol(bottom[i])) {
                    is_part_number = 1;
                }
            }

            if (!is_part_number) {
                is_part_number = (start_ptr >= str_begin && is_symbol(*(start_ptr - 1))) || is_symbol(*middle);
            }

            if (is_part_number) sum += number;
        } else {
            ++middle;
        }
    }

    return sum;
}

void part1(Result *result, char **lines) {
    char *top;
    char *middle;
    char *bottom;

    int length = strlen(*lines);
    int sum = 0;
    char *empty_line = malloc(length + 1);
    assert(empty_line != NULL && "Error allocating memory for empty line");

    for (int i = 0; i < length; ++i) {
        empty_line[i] = '.';
    }

    top = empty_line;
    middle = *lines;
    while (*lines) {
        if (**lines == '\0') break; // Filter out newline at the end of input

        bottom = *(++lines);
        // Newline at end of input or NULL (examples don't have the newline)
        // ...am I doing this right?
        if (bottom == NULL || *bottom == '\0') bottom = empty_line;

        printf("TOP    '%s'\n", top);
        printf("MIDDLE '%s'\n", middle);
        printf("BOTTOM '%s'\n", bottom);
        sum += find_part_numbers(top, middle, bottom);

        top = middle;
        middle = bottom;
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

