#include "morse.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>

#define NUM_OF_SYMBOLS 37

static const char LOWERCASE_LETTERS[NUM_OF_SYMBOLS] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ' '};
static const char UPPERCASE_LETTERS[NUM_OF_SYMBOLS] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ' '};

// 6 spaces are needed to store the null terminator :)
// C is fun?
static const char MORSE[NUM_OF_SYMBOLS][6] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", "-----", "/"};

// This function returns a pointer to the morse code written above.
// The genuis of this function feels amazing because I've never used C before, but I see why
// ... it's used for performence!
//
// I do not copy ANY data. The pointer returned points to the above array!
const char* char_to_morse(char letter){
    const char* result_ptr;
	for (int i = 0; i < NUM_OF_SYMBOLS; i++){
		if (letter == UPPERCASE_LETTERS[i] || letter == LOWERCASE_LETTERS[i]){
            result_ptr = MORSE[i];
		}
	}
	return result_ptr;
}

char* string_to_morse(char* string){
	int string_len = strlen(string);
	// worse possible case is 8 times the length (assuming all numbers/punctuation, and adding spaces)
	char result[string_len*8];
    char* result_ptr = result;
    // sets everything to null in the string, just in case there was data there previously.
    strcpy(result, "");
	for (int i = 0; i < string_len; i++){
		strcat(result, char_to_morse(string[i]));
        if (i != string_len-1){
            strcat(result, " ");
        }
	}
	return result_ptr;
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
	for (int j = 0; j < NUM_OF_SYMBOLS; j++){
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
	for (int i = 0; i < NUM_OF_SYMBOLS; i++){
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
