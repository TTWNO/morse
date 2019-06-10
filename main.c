#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define MAX_STRING_LENGTH 1024
#define NUM_OF_LETTERS 36
#define DASH_PAUSE_LENGTH 300000
#define DOT_PAUSE_LENGTH 100000

int main(){

	static const char LETTERS[NUM_OF_LETTERS] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	static const char MORSE[NUM_OF_LETTERS][6] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", "-----"};

	char rawInputString[MAX_STRING_LENGTH];
	char inputString[MAX_STRING_LENGTH];
	int sizeOfInputString, sizeOfMorseCode;

	printf("Enter a string: ");
	scanf("%[^\n]s", &rawInputString);
	sizeOfInputString = strlen(rawInputString);
	strcpy(inputString, rawInputString);
	// change data in copied string if it is uppercase
	for (int i = 0; i < sizeOfInputString; i++){
		if (isupper(rawInputString[i])){
			inputString[i] = tolower(rawInputString[i]);
		}
	}

	printf("\"%s\" has length of %d\n", inputString, sizeOfInputString);
	// Loop through every character in the input string
	for (int i = 0; i < sizeOfInputString; i++){
		// Loop through every character in the list of letters
		for (int j = 0; j < NUM_OF_LETTERS; j++){
			// If the character in the input string matches the character the character from the list
			if (inputString[i] == LETTERS[j]){
				sizeOfMorseCode = strlen(MORSE[j]);	
				// Print chracter in ascii in brackets before the morse code
				printf("(%c)", inputString[i], sizeOfMorseCode);
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
	printf("\n");
	return 0;
}

