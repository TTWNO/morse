#include "morse.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#ifndef MAX_LINE_SIZE
#define MAX_LINE_SIZE 4096
#endif

const long DEFAULT_DASH_PAUSE = 300000;
const long DEFAULT_DOT_PAUSE = 150000;

int main(int argc, char *argv[]){
  int string_len;
  char* input_string = NULL;
  char* output_string = (char*) malloc(sizeof(char) * MAX_LINE_SIZE);
  // output_char tracks the current printing character when slow printing is enabled
  char output_char;

	long dash_delay = DEFAULT_DASH_PAUSE;
	long dot_delay = DEFAULT_DOT_PAUSE;

	bool is_slow = false;
	bool convert_from_morse = false;	

	size_t buflen = 0;

	for (int argi = 0; argi < argc; argi++){
		char* arg = argv[argi];
		if (strcmp(arg, "--slow") == 0 || strcmp(arg, "-s") == 0){
			is_slow = true;
		} else if (strcmp(arg, "--reverse") == 0 || strcmp(arg, "-x") == 0){
			convert_from_morse = true;
		} else if (strcmp(arg, "--dash-delay") == 0 || strcmp(arg, "-hd") == 0){
			if (argc > argi+1){
				dash_delay = strtol(argv[argi+1], NULL, 10);
			} else {
				printf("No --dash-delay argument provided.\nIgnoring!\n");
			}
		} else if (strcmp(arg, "--dot-delay") == 0 || strcmp(arg, "-td") == 0){
			if (argc > argi+1){
				dot_delay = strtol(argv[argi+1], NULL, 10);
			} else {
				printf("Not --dot-delay argument provited.\nIgnoring!\n");
			}
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

      if (is_slow){
        for (int i = 0; i < strlen(output_string); i++){
          output_char = output_string[i];
          if (output_char == '-'){
            usleep(dash_delay);
            printf("%c", output_char);
          } else if (output_char == '.'){
            usleep(dot_delay);
            printf("%c", output_char); 
          } else {
            printf("%c", output_char);
          }
          fflush(stdout);
        }
        printf("\n");
      } else {
        printf("%s\n", output_string);
        // force flush the buffer incase user is in interactive mode
        fflush(stdin);
      }
		}
	}

  free(output_string);
  free(input_string);
	return 0;
}
