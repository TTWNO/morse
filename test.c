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

const char* PASS_FORMAT = "[%s]: \"%s\" %s \"%s\"\n";
const char* FAIL_FORMAT = "[%s]: \"%s\" %s \"%s\"\n";

void assert_str_eq(const char* s1, const char* s2){
    tests_run++;
    if (strcmp(s1, s2) == 0){
        printf(PASS_FORMAT, PASS, s1, EQ, s2);
        tests_passed++;
    } else {
        printf(PASS_FORMAT, FAIL, s1, NEQ, s2);
        tests_failed++;
    }
}

void assert_str_neq(const char* s1, const char* s2){
    tests_run++;
    if (strcmp(s1, s2) != 0){
        printf(PASS_FORMAT, PASS, s1, NEQ, s2);
        tests_passed++;
    } else {
        printf(PASS_FORMAT, FAIL, s1, EQ, s2);
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
    strcpy(result, "");
    strcpy(result, string_to_morse(input));
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
	assert_ctm('Z', "--..");
}

void test_string_to_morse(){
    assert_stm("Hello", ".... . .-. .-. .."); 
    assert_stm("world", ".-- --- .-. .-.. -.."); 
    assert_stm("Hello world!", ".... . .-. .-. .--- / .-- --- .-. .-.. -.. / -.-.--");
    assert_stm("I! HATE! YOU!", ".. -.-.-- / .... .- - . -.-.-- / -.-- -- ..- -.-.--");
}

void all_tests(){
    test_tests();
	printf("test_tests tests complete!\n");
    test_to_morse();
	printf("char_to_morse tests complete!\n");
    test_string_to_morse();
    printf("string_to_morse tests complete!\n");
}

int main(int argc, char **argv) {
	all_tests();
	if (tests_run == tests_passed){
		printf("ALL TESTS PASSED\n");
	}
	printf("Tests run: %d\n", tests_run);
	printf("Tests passed: %d\n", tests_passed);
	printf("Tests failed: %d\n", tests_failed);
	return 0;
}

