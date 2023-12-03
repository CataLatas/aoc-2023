typedef union {
	int   integer;
	char *string;
} Result;

typedef void (Solver)(Result*, char*);

void  check_example_int(Solver *solver, char *input, int expected);
void  check_example_str(Solver *solver, char *input, char *expected);
char* read_entire_file(char *filename);

