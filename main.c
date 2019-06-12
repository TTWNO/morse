#include "morse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const long DEFAULT_DASH_PAUSE = 300000;
const long DEFAULT_DOT_PAUSE = 150000;

int main(int argc, char *argv[]){
	long dash_delay = DEFAULT_DASH_PAUSE;
	long dot_delay = DEFAULT_DOT_PAUSE;

	bool addLetterBeforeMorse = false;
	bool isSlow = false;
	bool convertFromMorse = false;	

	size_t buflen = 0;
	ssize_t lengthOfInputString;

	for (int argi = 0; argi < argc; argi++){
		char* arg = argv[argi];
		if (strcmp(arg, "--slow") == 0 || strcmp(arg, "-s") == 0){
			isSlow = true;
		} else if (strcmp(arg, "--verbose") == 0 || strcmp(arg, "-v") == 0){
			addLetterBeforeMorse = true;
		} else if (strcmp(arg, "--reverse") == 0 || strcmp(arg, "-x") == 0){
			convertFromMorse = true;
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

	if (convertFromMorse){
		char* inputString;
		char* wordToken;
		char* letterToken;
		// for every line in the input, until the end of file
		while ((getline(&inputString, &buflen, stdin))!=EOF){
			// find the next double space (produces in this program by default when outputting morse code)
			wordToken = multi_tok(inputString, "  ");
			// While there is another block of text after a double space
			while (wordToken){
				// find the next space or newline (newlines are not consumed by the getline function)
				letterToken = strtok(wordToken, " \n");
				// while there is another block of text after a space (a newline will not have text after it, as we're using getline)
				while (letterToken){
					// convert morse to ascii
					reverse_morse(letterToken);
					// set letterToken to new string after NEXT space/newline
					letterToken = strtok(NULL, " \n");
				}
				// set word token (all the characters that make up a word in morse) to the next block after a double space
				wordToken = multi_tok(NULL, "  ");
				// this puts a space after every morse converted character.
				// because strtok consumes the space it is not printed, or passed around
				printf(" ");
			}
			// add a newline for every line consumed by getline
			printf("\n");
			// force-flush the input buffer just in case the user is in interactive mode
			fflush(stdin);
		}	
	} else {
		char* inputString;
		// for each line of input
		while ((getline(&inputString, &buflen, stdin))!=EOF){
			// print the morse code of the line
			// by default it is passthrough, meaning any non [a-zA-Z0-9] characters are printed as they are.
			// the only exception is dashes and dots, which are removed from the ouptut to avoid confusing the input veriosn of the program
			print_morse(inputString, isSlow, addLetterBeforeMorse, dot_delay, dash_delay);
			// add a newline becuase it will not be printed otherwise
			printf("\n");
			// force flush the buffer incase user is in interactive mode
			fflush(stdin);
		}
	}
	return 0;
}
