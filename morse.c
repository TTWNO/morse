#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_INPUT_SIZE USHRT_MAX
#define NUM_OF_LETTERS 36
#define DASH_PAUSE_LENGTH 1000000
#define DOT_PAUSE_LENGTH 500000

static const char LOWERCASE_LETTERS[NUM_OF_LETTERS] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
static const char UPPERCASE_LETTERS[NUM_OF_LETTERS] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

// 6 spaces are needed to store the null terminator :)
// C is fun?
static const char MORSE[NUM_OF_LETTERS][6] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", "-----"};

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

void print_single_morse(char charToMorse, bool isSlow, bool addLetter){
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
				if (convertedTo[i] == '-'){
					// usleep is a microseconds
					usleep(DASH_PAUSE_LENGTH);
				} else if (convertedTo[i] == '.'){
					usleep(DOT_PAUSE_LENGTH);
				}
			}
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

void print_morse(char* strToMorse, bool isSlow, bool addLetter){
	int sizeOfInputString;
	sizeOfInputString = strlen(strToMorse);

	// Loop through every character in the input string
	for (int i = 0; i < sizeOfInputString; i++){
		print_single_morse(strToMorse[i], isSlow, addLetter);
	}
}

void reverse_morse(char* morseToNormalize){
	bool isConvertable = false;
	char convertedChar;
	
	for (int i = 0; i < NUM_OF_LETTERS; i++){
		if (strcmp(MORSE[i], morseToNormalize) == 0){
			isConvertable = true;
			convertedChar = UPPERCASE_LETTERS[i];
		}
	}
	if (isConvertable){
		printf("%c", convertedChar);
	} else {
		printf("%s", morseToNormalize);
	}
}

int main(int argc, char *argv[]){

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
}
	}

	if (convertFromMorse){
		char* inputString;
		char* wordToken;

		char* letterToken;
		bool lastTokenWasEmpty = false;
		while ((getline(&inputString, &buflen, stdin))!=EOF){
			wordToken = multi_tok(inputString, "  ");
			while (wordToken){
				letterToken = strtok(wordToken, " \n");
				while (letterToken){
					reverse_morse(letterToken);
					letterToken = strtok(NULL, " \n");
				}
				wordToken = multi_tok(NULL, "  ");
				printf(" ");
			}
			printf("\n");
			fflush(stdin);	
		}	
	} else {
		char* inputString;
		while ((getline(&inputString, &buflen, stdin))!=EOF){
			print_morse(inputString, isSlow, addLetterBeforeMorse);
			printf("\n");
			fflush(stdin);
		}
	}

	return 0;
}
