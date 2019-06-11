#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>

#define NUM_OF_LETTERS 36

const long DEFAULT_DASH_PAUSE = 300000;
const long DEFAULT_DOT_PAUSE = 150000;

static char LOWERCASE_LETTERS[NUM_OF_LETTERS] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
static char UPPERCASE_LETTERS[NUM_OF_LETTERS] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

// 6 spaces are needed to store the null terminator :)
// C is fun?
static char MORSE[NUM_OF_LETTERS][6] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", "-----"};

char *multi_tok(char *input, char *delimiter) {
    static char *string;
    if (input != NULL)
        string = input;

    if (string == NULL)
        return string;

    char *end = strstr(string, delimiter);
    if (end == NULL) {
        char *temp = string;
        string = NULL;
        return temp;
    }

    char *temp = string;

    *end = '\0';
    string = end + strlen(delimiter);
    return temp;
}

void print_single_morse(char charToMorse, bool isSlow, bool addLetter, long dotDelay, long dashDelay){
	int sizeOfMorseCode;
	bool isConvertable = false;
	char convertedTo[6];	

	// Loop through every character in the list of letters
	for (int j = 0; j < NUM_OF_LETTERS; j++){
		// If the character in the input string matches the character the character from the list
		if (charToMorse == LOWERCASE_LETTERS[j] || charToMorse == UPPERCASE_LETTERS[j]){
			strcpy(convertedTo, MORSE[j]);
			sizeOfMorseCode = strlen(MORSE[j]);	
			isConvertable = true;
		}
	}

	if (addLetter){
		printf("(%c)", charToMorse);
	}
	if (isConvertable){
		if (isSlow){
			// loop through all the characters in the morse string
			for (int i = 0; i < strlen(convertedTo); i++){
				printf("%c", convertedTo[i]);
				// flush buffer to force visible slow writing
				fflush(stdout);
				if (convertedTo[i] == '-'){
					// usleep is a microseconds
					usleep(dashDelay);
				} else if (convertedTo[i] == '.'){
					usleep(dotDelay);
				}
			}
			// print a space after the squence of morse code characters
			printf(" ");
		// if not slow
		} else {
			printf("%s ", convertedTo);
		}
	// if not convertable
	} else {
		if (charToMorse == '-' || charToMorse == '.'){
		} else {
			printf("%c", charToMorse);
		}
	}
}

void print_morse(char* strToMorse, bool isSlow, bool addLetter, long dotDelay, long dashDelay){
	int sizeOfInputString;
	sizeOfInputString = strlen(strToMorse);

	// Loop through every character in the input string
	for (int i = 0; i < sizeOfInputString; i++){
		print_single_morse(strToMorse[i], isSlow, addLetter, dotDelay, dashDelay);
	}
}

void reverse_morse(char* morseToNormalize){
	bool isConvertable = false;
	char convertedChar;
	
	// go through every morse encoding
	for (int i = 0; i < NUM_OF_LETTERS; i++){
		// if the morse code is euqal to the input string
		if (strcmp(MORSE[i], morseToNormalize) == 0){
			isConvertable = true;
			convertedChar = UPPERCASE_LETTERS[i];
		}
	}
	if (isConvertable){
		printf("%c", convertedChar);
	// if not convertable to a normal character [A-Z0-9] print the character the stirng the way it is.
	} else {
		printf("%s", morseToNormalize);
	}
}

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
