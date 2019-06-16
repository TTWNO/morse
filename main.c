#include "morse.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

const long DEFAULT_DASH_PAUSE = 300000;
const long DEFAULT_DOT_PAUSE = 150000;

int main(int argc, char *argv[]){
    char* inputString;
    char* outputString;
    // outputChar tracks the current printing character when slow printing is enabled
    char outputChar;

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
		// for every line in the input, until the end of file
		while ((getline(&inputString, &buflen, stdin))!=EOF){
            int stringLen = strlen(inputString);

            // This effectively strips the newline off the string
            if (inputString[stringLen-1] == '\n'){
                inputString[stringLen-1] = '\0';
            }
            
            outputString = morse_to_string(inputString);
            printf("%s\n", outputString);
			// force-flush the input buffer just in case the user is in interactive mode
			fflush(stdin);
		}	
	} else {
		// for each line of input
		while ((getline(&inputString, &buflen, stdin))!=EOF){
            int stringLen = strlen(inputString);

            // This effectively strips the newline off the string
            if (inputString[stringLen-1] == '\n'){
                inputString[stringLen-1] = '\0';
            }

            outputString = string_to_morse(inputString);

            if (isSlow){
                for (int i = 0; i < strlen(outputString); i++){
                    outputChar = outputString[i];
                    if (outputChar == '-'){
                        usleep(dash_delay);
                        printf("%c", outputChar);
                    } else if (outputChar == '.'){
                        usleep(dot_delay);
                        printf("%c", outputChar); 
                    } else {
                        printf("%c", outputChar);
                    }
                    fflush(stdout);
                }
                printf("\n");
            } else {
                printf("%s\n", outputString);
                // force flush the buffer incase user is in interactive mode
                fflush(stdin);
            }
		}
	}
	return 0;
}
