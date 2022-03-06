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

static char SYMBOLS[NUM_OF_SYMBOLS] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    '.', ',', '?', '\'', '!', '/', '(', ')', '&', ':', ';', '=', '+', '-', '_', '"', '$', '@',
    ' '};

static char SYMBOL_ERROR = '~';

static char MORSE[NUM_OF_SYMBOLS][MAX_MORSE_LENGTH] = {
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

static char* MORSE_ERROR = "........";

// This function returns a pointer to the morse code written above.
// The genuis of this function feels amazing because I've never used C before, but I see why
// ... it's used for performence!
//
// I do not copy ANY data. The pointer returned points to the above array!
char* char_to_morse(char letter) {
    for (int i = 0; i < NUM_OF_SYMBOLS; i++) {
       	if (letter == SYMBOLS[i]) {
          return MORSE[i];
        }
    }
    return MORSE_ERROR;
}

void string_to_morse(char* string, char* result){
  int on_char = 0;
  int string_len = strlen(string);
  char* morse;
	// worse possible case is 8 times the length (assuming all numbers/punctuation, and adding spaces)
  // +1 for NULL terminator
	for (int i = 0; i < string_len; i++){
    morse = char_to_morse(string[i]);
    int morse_len = strlen(morse);
    memcpy(result+on_char, morse, morse_len);
    on_char += morse_len;
    if (i != string_len-1){
      memcpy(result+on_char, " ", 1);
      on_char++;
    }
	}
  result[on_char] = '\0';
}

char morse_to_char(const char* morse) {
	for (int i = 0; i < NUM_OF_SYMBOLS; i++) {
		if (strcmp(morse, MORSE[i]) == 0) {
      return SYMBOLS[i];
		}
	}
  return SYMBOL_ERROR;
}

void morse_to_string(const char* morse_to_cpy, char* result) {
  int on_char = 0;
	char* morse = malloc(sizeof(char) * strlen(morse_to_cpy)+1);
	strcpy(morse, morse_to_cpy);

	// split by the space character
	char* morse_ptr = strtok(morse, " \n");
	// until we reach the end of the string
	while (morse_ptr != NULL) {
		char char_to_add = morse_to_char(morse_ptr);
		// give the address of the single character to concatinate to result
    result[on_char++] = char_to_add;
		// reset the morse ptr for the next section between a space
		morse_ptr = strtok(NULL, " \n");
	}
  free(morse);
  // add null terminator, necessary in C strings
  result[on_char] = '\0';
}
