typedef union {
    int   integer;
    char *string;
} Result;

typedef void (Solver)(Result*, char**);

void  check_example_int(Solver *solver, char **lines, int expected);
void  check_example_str(Solver *solver, char **lines, char *expected);
char* read_entire_file(char *filename);
char** read_lines_from_file(char *filename);

