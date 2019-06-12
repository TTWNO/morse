 /* file: minunit.h */
#include <string.h>
 #define mu_assert_str(function_name, input, output) do{ char* result = function_name(input);tests_run++; if (!(strcmp(result, output)==0)){printf("[FAILED] ");tests_failed++;}else{printf("[PASSED] ");tests_passed++;}; printf("%s(\"%s\"): \"%s\" == \"%s\"\n", function_name, input, result, output); } while (0)
 #define mu_assert(message, test) do { if (!(test)) return message; } while (0)

 #define mu_assert_neg(message, test) do { if ((test)){tests_failed++;return message;} else {tests_passed++;} } while (0)
 #define mu_run_test(test) do { char *message = test(); tests_run++; \
                                if (message) return message; } while (0)
 extern int tests_run;
