#include <stdio.h>
#include <string.h>
#include "morse.h"

int tests_run = 0;
int tests_passed = 0;
int tests_failed = 0;

const char* FAIL = "FAIL";
const char* PASS = "PASS";

const char* EQ = "==";
const char* NEQ = "!=";

const char* GREEN_TEXT = "\e[32m";
const char* RED_TEXT = "\e[31m";
const char* CLEAR_FORMAT = "\e[0m";

const char* PASS_FORMAT = "\e[32m[%s]: \"%s\" %s \"%s\"\e[0m\n";
const char* FAIL_FORMAT = "\e[31m[%s]: \"%s\" %s \"%s\"\e[0m\n";
const char* PASS_CHAR_FORMAT = "\e[32m[%s]: \'%c\' %s \'%c\'\e[0m\n";
const char* FAIL_CHAR_FORMAT = "\e[31m[%s]: \'%c\' %s \'%c\'\e[0m\n";

void assert_char_eq(const char c1, const char c2){
	tests_run++;
	if (c1 == c2){
		printf(PASS_CHAR_FORMAT, PASS, c1, EQ, c2);
		tests_passed++;
	} else {
		printf(FAIL_CHAR_FORMAT, FAIL, c1, NEQ, c2);
		tests_failed++;
	}
}

void assert_str_eq(const char* s1, const char* s2){
    tests_run++;
    if (strcmp(s1, s2) == 0){
        printf(PASS_FORMAT, PASS, s1, EQ, s2);
        tests_passed++;
    } else {
        printf(FAIL_FORMAT, FAIL, s1, NEQ, s2);
        tests_failed++;
    }
}

void assert_str_neq(const char* s1, const char* s2){
    tests_run++;
    if (strcmp(s1, s2) != 0){
        printf(PASS_FORMAT, PASS, s1, NEQ, s2);
        tests_passed++;
    } else {
        printf(FAIL_FORMAT, FAIL, s1, EQ, s2);
        tests_failed++;
    }
}

void assert_ctm(char input, char* output){
    const char* result = char_to_morse(input);
    assert_str_eq(result, output);
}

void assert_stm(char* input, char* output){
    char result[strlen(input)*8];
    // fill with blanks in case of previous data
//    strcpy(result, "");
    strcpy(result, string_to_morse(input));
    assert_str_eq(result, output);
}

void assert_mtc(char* input, char output){
	char result = morse_to_char(input);
	assert_char_eq(result, output);
}

void assert_mts(char* input, char* output){
	char* result = morse_to_string(input);
	assert_str_eq(result, output);
}

void test_tests(){
    assert_str_eq(".", ".");
    assert_str_neq("+", "-");
}

void test_to_morse(){
	assert_ctm('a', ".-");
	assert_ctm('A', ".-");
	assert_ctm('b', "-...");
	assert_ctm('B', "-...");
	assert_ctm('c', "-.-.");
	assert_ctm('C', "-.-.");
	assert_ctm('d', "-..");
	assert_ctm('D', "-..");
	assert_ctm('e', ".");
	assert_ctm('E', ".");
	assert_ctm('f', "..-.");
	assert_ctm('F', "..-.");
	assert_ctm('g', "--.");
	assert_ctm('G', "--.");
	assert_ctm('h', "....");
	assert_ctm('H', "....");
	assert_ctm('i', "..");
	assert_ctm('I', "..");
	assert_ctm('j', ".---");
	assert_ctm('J', ".---");
	assert_ctm('k', "-.-");
	assert_ctm('K', "-.-");
	assert_ctm('l', ".-..");
	assert_ctm('L', ".-..");
	assert_ctm('m', "--");
	assert_ctm('M', "--");
	assert_ctm('n', "-.");
	assert_ctm('N', "-.");
	assert_ctm('o', "---");
	assert_ctm('O', "---");
	assert_ctm('p', ".--.");
	assert_ctm('P', ".--.");
	assert_ctm('q', "--.-");
	assert_ctm('Q', "--.-");
	assert_ctm('r', ".-.");
	assert_ctm('R', ".-.");
	assert_ctm('s', "...");
	assert_ctm('S', "...");
	assert_ctm('t', "-");
	assert_ctm('T', "-");
	assert_ctm('u', "..-");
	assert_ctm('U', "..-");
	assert_ctm('v', "...-");
	assert_ctm('V', "...-");
	assert_ctm('w', ".--");
	assert_ctm('W', ".--");
	assert_ctm('x', "-..-");
	assert_ctm('X', "-..-");
	assert_ctm('y', "-.--");
	assert_ctm('Y', "-.--");
	assert_ctm('z', "--..");
	assert_ctm('0', "-----");
	assert_ctm('1', ".----");
	assert_ctm('2', "..---");
	assert_ctm('3', "...--");
	assert_ctm('4', "....-");
	assert_ctm('5', ".....");
	assert_ctm('6', "-....");
	assert_ctm('7', "--...");
	assert_ctm('8', "---..");
	assert_ctm('9', "----.");
	assert_ctm(' ', "/");
	assert_ctm('!', "-.-.--");
}

void test_string_to_morse(){
    assert_stm("Wee!", ".-- . . -.-.--");
    assert_stm("Hello", ".... . .-.. .-.. ---"); 
    assert_stm("world", ".-- --- .-. .-.. -.."); 
    assert_stm("Hello world!", ".... . .-.. .-.. --- / .-- --- .-. .-.. -.. -.-.--");
    assert_stm("I! HATE! YOU!", ".. -.-.-- / .... .- - . -.-.-- / -.-- --- ..- -.-.--");
	assert_stm("Whisky and rye", ".-- .... .. ... -.- -.-- / .- -. -.. / .-. -.-- .");
}

void test_morse_to_char(){
	assert_mtc(".-", 'A');
	assert_mtc("-...", 'B');
	assert_mtc("-.-.", 'C');
	assert_mtc("-..", 'D');
	assert_mtc(".", 'E');
	assert_mtc("..-.", 'F');
	assert_mtc("--.", 'G');
	assert_mtc("....", 'H');
	assert_mtc("..", 'I');
	assert_mtc(".---", 'J');
	assert_mtc("-.-", 'K');
	assert_mtc(".-..", 'L');
	assert_mtc("--", 'M');
	assert_mtc("-.", 'N');
	assert_mtc("---", 'O');
	assert_mtc(".--.", 'P');
	assert_mtc("--.-", 'Q');
	assert_mtc(".-.", 'R');
	assert_mtc("...", 'S');
	assert_mtc("-", 'T');
	assert_mtc("..-", 'U');
	assert_mtc("...-", 'V');
	assert_mtc(".--", 'W');
	assert_mtc("-..-", 'X');
	assert_mtc("-.--", 'Y');
	assert_mtc("--..", 'Z');
}

void test_morse_to_string(){
	assert_mts("... --- ...", "SOS");
	assert_mts(". . . . .", "EEEEE");
	assert_mts("- ... ....", "TSH");
	assert_mts("- - - - ... ... ... ... .... .... .... .... / .... .. .. .. ..", "TTTTSSSSHHHH HIIII");
	assert_mts("- .- .-. ..-. / -- .- .-.. .- -.- --- ...-", "TARF MALAKOV");
	assert_mts("- .- .. -", "TAIT");
	assert_mts("- .- .-.. -.-", "TALK");
	assert_mts("- .- ... -.- / -- .- ... - . .-.", "TASK MASTER");
	assert_mts("- .- .-. ..-. / -- .- .-.. .- -.- --- ...-", "TARF MALAKOV");
}

void all_tests(){
    test_tests();
	printf("test_tests tests complete!\n");
    test_to_morse();
	printf("char_to_morse tests complete!\n");
    test_string_to_morse();
    printf("string_to_morse tests complete!\n");
	test_morse_to_char();
	printf("test_morse_to_char tests complete!\n");
	test_morse_to_string();
	printf("test_morse_to_string tests complete!\n");
}

int main(int argc, char **argv) {
	bool done_printing_passed_tests = false;

	all_tests();
	if (tests_run == tests_passed){
		printf("ALL TESTS PASSED\n");
	}
	printf(GREEN_TEXT);
	for (int i = 0; i < tests_passed; i++){
		printf("=");
	}
	printf(CLEAR_FORMAT);
	printf(RED_TEXT);
	for (int i = 0; i < tests_failed; i++){
		printf("=");
	}
	printf("\n");
	printf(CLEAR_FORMAT);
	printf("Tests run: %d\n", tests_run);
	printf("Tests passed: %d\n", tests_passed);
	printf("Tests failed: %d\n", tests_failed);
	return 0;
}

