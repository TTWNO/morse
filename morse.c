#include "morse.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>

#define NUM_OF_LETTERS 36

static char LOWERCASE_LETTERS[NUM_OF_LETTERS] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
static char UPPERCASE_LETTERS[NUM_OF_LETTERS] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

// 6 spaces are needed to store the null terminator :)
// C is fun?
static char MORSE[NUM_OF_LETTERS][6] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", "-----"};

char* char_to_morse(char letter){
	char result[6];
	for (int i = 0; i < NUM_OF_LETTERS; i++){
		if (letter == UPPERCASE_LETTERS[i] || letter == LOWERCASE_LETTERS[i]){
			strcpy(&result, MORSE[i]);
			//result = MORSE[i];
		}
	}
	return result;
}

char * to_morse(char* string){
	int string_len = strlen(string);
	// worse possible case is 6 times the length (assuming all numbers)
	char* result;
	for (int i = 0; i < strlen(string); i++){
		strcat(result, char_to_morse(string[i]));
	}
	return result;
}

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
