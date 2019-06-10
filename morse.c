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

static const char MORSE[NUM_OF_LETTERS][6] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", "-----"};

void print_single_morse(char charToMorse, bool isSlow, bool addLetter){
	int sizeOfMorseCode;

	// Loop through every character in the list of letters
	for (int j = 0; j < NUM_OF_LETTERS; j++){
		// If the character in the input string matches the character the character from the list
		if (charToMorse == LOWERCASE_LETTERS[j] || charToMorse == UPPERCASE_LETTERS[j]){
			sizeOfMorseCode = strlen(MORSE[j]);	
			// Print chracter in ascii in brackets before the morse code
			if (addLetter){
				printf("(%c)", charToMorse, sizeOfMorseCode);
			}
			// if speed restraints are being added for effect
			if (isSlow){
				// Loop through each character in the morse code for that chracter
				for (int k = 0; k < sizeOfMorseCode; k++){
					printf("%c", MORSE[j][k]);
					// Force flush buffer so it is garunteed to be written to, with the delays in between
					fflush(stdout);
					// If the morse character is a dash	
					if (MORSE[j][k] == '-'){
						// ******* TODO: Replace with Arduino light code
						// Long delay code
						usleep(DASH_PAUSE_LENGTH);
					} else {
						// ******* TODO: Replace with Arduino light code
						// Short delay code
						usleep(DOT_PAUSE_LENGTH);
					}
				}
				printf(" ");
			// If not slow
			} else {
				printf("%s ", MORSE[j]);
			}
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

int main(int argc, char *argv[]){

	bool addLetterBeforeMorse = false;
	bool isSlow = false;

	char inputString[MAX_INPUT_SIZE];

	for (int argi = 0; argi < argc; argi++){
		char* arg = argv[argi];
		if (strcmp(arg, "--interactive") == 0 || strcmp(arg, "-i") == 0){
			printf("Entering interactive mode!\n");
			int sizeOfInputString;
			printf("Enter a string: ");
			scanf("%[^\n]s", inputString);
			sizeOfInputString = strlen(inputString);

			printf("\"%s\" has length of %d\n", inputString, sizeOfInputString);
			printf("\n");
		  
			print_morse(inputString, isSlow, addLetterBeforeMorse);
			printf("\n");
		} else if (strcmp(arg, "--slow") == 0 || strcmp(arg, "-s") == 0){
			isSlow = true;
		} else if (strcmp(arg, "--verbose") == 0 || strcmp(arg, "-v") == 0){
			addLetterBeforeMorse = true;
		}
	}
	scanf("%[^\n]s", inputString);
	print_morse(inputString, isSlow, addLetterBeforeMorse);
	printf("\n");

	return 0;
}

