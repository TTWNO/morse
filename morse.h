#include <stdbool.h>

const char * char_to_morse(char letter);
char * string_to_morse(char* string);
char * from_morse(char* string);

void print_morse(char* string, bool b1, bool b2, long s1, long s2);
void reverse_morse(char* string);
char *multi_tok(char *input, char *delimiter);