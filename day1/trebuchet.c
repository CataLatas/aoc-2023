#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers.h"

#define EXAMPLE_INPUT "1abc2\n" \
                      "pqr3stu8vwx\n" \
                      "a1b2c3d4e5f\n" \
                      "treb7uchet\n"

#define EXAMPLE_RESULT 142

#define EXAMPLE_INPUT_2 "two1nine\n" \
                        "eightwothree\n" \
                        "abcone2threexyz\n" \
                        "xtwone3four\n" \
                        "4nineeightseven2\n" \
                        "zoneight234\n" \
                        "7pqrstsixteen\n"

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

int calculate_sum(char *input, int(*map_to_digit)(char*)) {
    int first;
    int last;
    int sum;

    for (sum = 0; *input; ++input) {
        for (first = last = -1; *input && *input != '\n'; ++input) {
            int digit = map_to_digit(input);

            if (digit != -1) {
                if (first == -1) first = digit;

                last = digit;
            }
        }

        if (first != -1 && last != -1) {
            sum += first*10 + last;
        }
    }

    return sum;
}

void part1(Result *result, char *input) {
    result->integer = calculate_sum(input, get_digit_part1);
}

void part2(Result *result, char *input) {
    result->integer = calculate_sum(input, get_digit_part2);
}

int main() {
    char *input;
    Result result;

    input = read_entire_file("input.txt");

    printf("----- PART 1 -----\n");
    check_example_int(part1, EXAMPLE_INPUT, EXAMPLE_RESULT);
    part1(&result, input);
    printf("Sum of calibration values: %d\n\n", result.integer);

    printf("----- PART 2 -----\n");
    check_example_int(part2, EXAMPLE_INPUT_2, EXAMPLE_RESULT_2);
    part2(&result, input);
    printf("Sum of calibration values: %d\n", result.integer);

    free(input);

    return 0;
}

