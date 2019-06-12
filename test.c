#include <stdio.h>
#include "minunit.h"
#include "morse.h"

int tests_run = 0;
int tests_passed = 0;
int tests_failed = 0;

static char * test_tests1(){
	mu_assert("Error, - != -", "-" == "-");
	return 0;
}

static char * test_tests2(){
	mu_assert_neg("Error, - == .", "-" == ".");
	return 0;
}

static char * test_to_morse(){
	char_to_morse('a');
	printf("trying to run ctm\n");
	char* r1;
	r1 = char_to_morse('a');
	printf("ctm('a') works!");
	mu_assert_str(char_to_morse, 'a', ".-");
	mu_assert_str(char_to_morse, 'b', "-...");
	mu_assert_str(char_to_morse, 'c', "-.-.");
	mu_assert_str(char_to_morse, 'd', "-..");
	mu_assert_str(char_to_morse, 'e', ".");
	mu_assert_str(char_to_morse, 'f', "..-.");
	mu_assert_str(char_to_morse, 'g', "--.");
	mu_assert_str(char_to_morse, 'h', "....");
	mu_assert_str(char_to_morse, 'i', "..");
	mu_assert_str(char_to_morse, 'j', ".---");
	mu_assert_str(char_to_morse, 'k', "-.-");
	mu_assert_str(char_to_morse, 'l', ".-..");
	mu_assert_str(char_to_morse, 'm', "--");
	mu_assert_str(char_to_morse, 'n', "-.");
	mu_assert_str(char_to_morse, 'o', "---");
	mu_assert_str(char_to_morse, 'p', ".--.");
	mu_assert_str(char_to_morse, 'q', "--.-");
	mu_assert_str(char_to_morse, 'r', ".-.");
	mu_assert_str(char_to_morse, 's', "...");
	mu_assert_str(char_to_morse, 't', "-");
	mu_assert_str(char_to_morse, 'u', "..-");
	mu_assert_str(char_to_morse, 'v', "...-");
	mu_assert_str(char_to_morse, 'w', ".--");
	mu_assert_str(char_to_morse, 'x', "-..-");
	mu_assert_str(char_to_morse, 'y', "-.--");
	mu_assert_str(char_to_morse, 'z', "--..");
	return 0;
}

static char * all_tests(){
	mu_run_test(test_tests1);
	printf("test_tests1 complete!\n");
	mu_run_test(test_tests2);
	printf("test_tests2 complete!\n");
	mu_run_test(test_to_morse);
	printf("test_to_morse complete!\n");
	return 0;
}

int main(int argc, char **argv) {
	char *result = all_tests();
	if (tests_run == tests_passed){
		printf("ALL TESTS PASSED\n");
	}
	printf("Tests run: %d\n", tests_run);
	printf("Tests passed: %d\n", tests_passed);
	printf("Tests failed: %d\n", tests_failed);
	return 0;
}

