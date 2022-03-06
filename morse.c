// add test to check mirroring
#include "morse.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>

#define NUM_OF_SYMBOLS 82
#define MAX_MORSE_LENGTH 9

static const char SYMBOLS[NUM_OF_SYMBOLS] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    '.', ',', '?', '\'', '!', '/', '(', ')', '&', ':', ';', '=', '+', '-', '_', '"', '$', '@',
    ' '};

static const char SYMBOL_ERROR = '~';

static const char MORSE[NUM_OF_SYMBOLS][MAX_MORSE_LENGTH] = {
    // A-Z
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..",
    // a-z (same as above, but needed twice due to design choices)
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..",
    // 0-9
     "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.",
     // . , ? ' ! / ( ) & : ; = + - _ " $ @ EOF
     ".-.-.-", "--..--", "..--..", ".----.", "-.-.--", "-..-.", "-.--.", "-.--.-", ".-...", "---...", "-.-.-.", "-...-", ".-.-.", "-...-", "..--.-", ".-..-.", "...-..-", ".--.-.",
    // space
    "/"};

static const char* MORSE_ERROR = "........";

// This function returns a pointer to the morse code written above.
// The genuis of this function feels amazing because I've never used C before, but I see why
// ... it's used for performence!
//
// I do not copy ANY data. The pointer returned points to the above array!
const char* char_to_morse(char letter) {
    for (int i = 0; i < NUM_OF_SYMBOLS; i++) {
       	if (letter == SYMBOLS[i]) {
          return MORSE[i];
        }
    }
    return MORSE_ERROR;
}

void string_to_morse(char* string, char* result){
  int string_len = strlen(string);
	// worse possible case is 8 times the length (assuming all numbers/punctuation, and adding spaces)
  // +1 for NULL terminator
	for (int i = 0; i < string_len; i++){
		strcat(result, char_to_morse(string[i]));
        if (i != string_len-1){
            strcat(result, " ");
        }
	}
}

const char morse_to_char(const char* morse) {
	for (int i = 0; i < NUM_OF_SYMBOLS; i++) {
		if (strcmp(morse, MORSE[i]) == 0) {
      return SYMBOLS[i];
		}
	}
  return SYMBOL_ERROR;
}

void morse_to_string(const char* morse_to_cpy, char* result) {
	int morse_length = strlen(morse_to_cpy)+1;
	char morse[morse_length];
	strcpy(morse, morse_to_cpy);

	// split by the space character
	char* morse_ptr = strtok(morse, " \n");
	// until we reach the end of the string
	while (morse_ptr != NULL) {
		char char_to_add = morse_to_char(morse_ptr);
		// give the address of the single character to concatinate to result
		strcat(result, &char_to_add);
		// reset the morse ptr for the next section between a space
		morse_ptr = strtok(NULL, " \n");
	}
}
