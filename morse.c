#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define MAX_STRING_LENGTH 1024
#define NUM_OF_LETTERS 36
#define DASH_PAUSE_LENGTH 1000000
#define DOT_PAUSE_LENGTH 500000


static char* CHRISTMAS_PHRASES[] = {"Merry Christmas", "Happy Haunika", "Happy Holidays!", "Jingle bells! Jingle bells!"};

static const char LOWERCASE_LETTERS[NUM_OF_LETTERS] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
static const char UPPERCASE_LETTERS[NUM_OF_LETTERS] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

static const char MORSE[NUM_OF_LETTERS][6] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", "-----"};

void print_single_morse(char charToMorse){
	int sizeOfMorseCode;	

	// Loop through every character in the list of letters
	for (int j = 0; j < NUM_OF_LETTERS; j++){
		// If the character in the input string matches the character the character from the list
		if (charToMorse == LOWERCASE_LETTERS[j] || charToMorse == UPPERCASE_LETTERS[j]){
			sizeOfMorseCode = strlen(MORSE[j]);	
			// Print chracter in ascii in brackets before the morse code
			printf("(%c)", charToMorse, sizeOfMorseCode);
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
		}
	}
}

void print_morse(char* strToMorse){
	int sizeOfInputString;
	sizeOfInputString = strlen(strToMorse);

	// Loop through every character in the input string
	for (int i = 0; i < sizeOfInputString; i++){
		print_single_morse(strToMorse[i]);
	}
}

int main(int argc, char *argv[]){
	if (argc > 1){
		if (strcmp(argv[1], "--interactive") == 0 || strcmp(argv[1], "-i") == 0){
			printf("Entering interactive mode!\n");
			int sizeOfInputString;
			char inputString[MAX_STRING_LENGTH];
			printf("Enter a string: ");
			scanf("%[^\n]s", inputString);
			sizeOfInputString = strlen(inputString);

			printf("\"%s\" has length of %d\n", inputString, sizeOfInputString);
			printf("\n");
		  
			print_morse(inputString);
			printf("\n");
		}
	// If not interactive mode
	} else {
		for (int i = 0; i < 4; i++){
			print_morse(CHRISTMAS_PHRASES[i]);
			printf("\n\n");
		}
	}
	return 0;
}

