#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers.h"

char *EXAMPLE_INPUT[] = {
    "1abc2",
    "pqr3stu8vwx",
    "a1b2c3d4e5f",
    "treb7uchet",
    NULL
};

#define EXAMPLE_RESULT 142

char *EXAMPLE_INPUT_2[] = {
    "two1nine",
    "eightwothree",
    "abcone2threexyz",
    "xtwone3four",
    "4nineeightseven2",
    "zoneight234",
    "7pqrstsixteen"
};

#define EXAMPLE_RESULT_2 281

int get_digit_part1(char *s) {
    if (*s >= '0' && *s <= '9') {
        return *s - '0';
    }

    return -1;
}

int get_digit_part2(char *s) {
    const static char* DIGITS_STR[] = {
        "one", "two", "three", "four", "five",
        "six", "seven", "eight", "nine"
    };

    int digit = get_digit_part1(s);
    if (digit != -1) return digit;

    for (int i = 0; i < 9; ++i) {
        if (strncmp(s, DIGITS_STR[i], strlen(DIGITS_STR[i])) == 0) {
            return i + 1;
        }
    }

    return -1;
}

int calculate_sum(char **lines, int(*map_to_digit)(char*)) {
    int first;
    int last;

    int sum = 0;
    for (char *line = *lines; *lines; line = *(++lines)) {
        if (*line == '\0') break; // Filter out empty line at end of input

        first = -1;
        last = -1;
        while (*line) {
            int digit = map_to_digit(line);

            if (digit != -1) {
                if (first == -1) first = digit;

                last = digit;
            }

            ++line;
        }

        assert(first != -1 && last != -1);
        sum += first*10 + last;
    }

    return sum;
}

void part1(Result *result, char **lines) {
    result->integer = calculate_sum(lines, get_digit_part1);
}

void part2(Result *result, char **lines) {
    result->integer = calculate_sum(lines, get_digit_part2);
}

int main() {
    char **lines;
    Result result;

    lines = read_lines_from_file("input.txt");

    printf("----- PART 1 -----\n");
    check_example_int(part1, EXAMPLE_INPUT, EXAMPLE_RESULT);
    part1(&result, lines);
    printf("Sum of calibration values: %d\n\n", result.integer);

    printf("----- PART 2 -----\n");
    check_example_int(part2, EXAMPLE_INPUT_2, EXAMPLE_RESULT_2);
    part2(&result, lines);
    printf("Sum of calibration values: %d\n", result.integer);

    free(*lines);
    free(lines);

    return 0;
}

