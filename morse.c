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
const char* char_to_morse(char letter){
    const char* result_ptr = malloc(sizeof(char)*MAX_MORSE_LENGTH);
    bool result_set = false;
    for (int i = 0; i < NUM_OF_SYMBOLS; i++){
       	if (letter == SYMBOLS[i]){
	  result_ptr = MORSE[i];
          result_set = true;
		}
    }
    if (!result_set){
        result_ptr = MORSE_ERROR;
    }
    return result_ptr;
}

char* string_to_morse(char* string){
	int string_len = strlen(string);
	// worse possible case is 8 times the length (assuming all numbers/punctuation, and adding spaces)
    // +1 for NULL terminator
    char* result = malloc(sizeof(char)*string_len*MAX_MORSE_LENGTH);
    // sets everything to null in the string, just in case there was data there previously.
    strcpy(result, "");
	for (int i = 0; i < string_len; i++){
		strcat(result, char_to_morse(string[i]));
        if (i != string_len-1){
            strcat(result, " ");
        }
	}
	return result;
}

const char morse_to_char(const char* morse){
    bool found_symbol = false;
    char result;
	for (int i = 0; i < NUM_OF_SYMBOLS && !found_symbol; i++){
		if (strcmp(morse, MORSE[i]) == 0){
			result = SYMBOLS[i];
            found_symbol = true;
		}
	}
    if (!found_symbol){
        result = SYMBOL_ERROR;
    }
    return result;
}

char* morse_to_string(const char* morse_to_cpy){
	int morse_length = strlen(morse_to_cpy)+1;
	char morse[morse_length];
	strcpy(morse, morse_to_cpy);

    // allocate the amount of space the morse takes up for the text string
    // this could be changed, but I don't see the point in optimizing the small things here.
    char* result = malloc(sizeof(char)*strlen(morse));
	// copy nothing to the string to avoid extra data
	//strcpy(result, "");

	// split by the space character
	char* morse_ptr = strtok(morse, " \n");
	// until we reach the end of the string
	while (morse_ptr != NULL){
		char char_to_add = morse_to_char(morse_ptr);
		// give the address of the single character to concatinate to result
		strcat(result, &char_to_add);
		// reset the morse ptr for the next section between a space
		morse_ptr = strtok(NULL, " \n");
	}
	return result;
}
