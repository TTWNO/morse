#include "morse.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#ifndef MAX_LINE_SIZE
#define MAX_LINE_SIZE 4096
#endif

int main(int argc, char *argv[]){
  int string_len;
  char* input_string = NULL;
  char* output_string = (char*) malloc(sizeof(char) * MAX_LINE_SIZE);
  // output_char tracks the current printing character when slow printing is enabled

	bool convert_from_morse = false;	

	size_t buflen = 0;

	for (int argi = 0; argi < argc; argi++){
		char* arg = argv[argi];
		if (strcmp(arg, "--reverse") == 0 || strcmp(arg, "-x") == 0){
			convert_from_morse = true;
		}
	}

	if (convert_from_morse){
		// for every line in the input, until the end of file
		while ((string_len = getline(&input_string, &buflen, stdin))!=EOF){
      // This effectively strips the newline off the string
      if (input_string[string_len-1] == '\n'){
          input_string[string_len-1] = '\0';
      }
            
      morse_to_string(input_string, output_string);
      printf("%s\n", output_string);
      // force-flush the input buffer just in case the user is in interactive mode
      fflush(stdin);
    }	
	} else {
		// for each line of input
		while ((string_len = getline(&input_string, &buflen, stdin))!=EOF){
      // This effectively strips the newline off the string
      if (input_string[string_len-1] == '\n'){
          input_string[string_len-1] = '\0';
      }

      string_to_morse(input_string, output_string);

      printf("%s\n", output_string);
      // force flush the buffer incase user is in interactive mode; TODO, redo with if to check if fd is stdout
      fflush(stdin);
		}
	}

  free(output_string);
  free(input_string);
	return 0;
}
