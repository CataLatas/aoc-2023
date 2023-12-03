#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"

#define EXAMPLE_INPUT "1abc2\n" \
                      "pqr3stu8vwx\n" \
                      "a1b2c3d4e5f\n" \
                      "treb7uchet\n"

#define EXAMPLE_RESULT 142

void part1(Result *result, char *input) {
	int first;
	int last;
	char c;

	result->integer = 0;
	while ((c = *input++)) {
		first = -1;
		last = -1;
		do {
			if (c >= '0' && c <= '9') {
				if (first == -1) first = c - '0';

				last = c - '0';
			}
		} while ((c = *input++) && c != '\n');

		if (first != -1 && last != -1) {
			result->integer += first*10 + last;
		}
	}
}

void part2(Result *result, char *input) {
	result->integer = 0;
}


int main() {
	char *input;
	Result result;

	check_example_int(part1, EXAMPLE_INPUT, EXAMPLE_RESULT);

	input = read_entire_file("input.txt");

	printf("----- PART 1 -----\n");
	part1(&result, input);
	printf("Sum of calibration values: %d\n\n", result.integer);

	printf("----- PART 2 -----\n");
	part2(&result, input);
	printf("PART 2 TBD\n");

	free(input);

	return 0;
}

