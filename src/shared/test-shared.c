
#include <stdio.h>
#include <string.h>
#include "test/test-suite.h"
#include "string-util.h"

static int test_string_util_strstrip_null_string(void)
{
	return strstrip(NULL) != NULL;
}

static int test_string_util_strstrip_empty_string(void)
{
	char str[] = "";
	return strcmp(strstrip(str), "");
}

static int test_string_util_strstrip_one_space(void)
{
	char str[] = " ";
	return strcmp(strstrip(str), "");
}

static int test_string_util_strstrip_multiple_spaces(void)
{
	char str[] = "      ";
	return strcmp(strstrip(str), "");
}

static int test_string_util_strstrip_leading_space(void)
{
	char str[] = " hello!";
	return strcmp(strstrip(str), "hello!");
}

static int test_string_util_strstrip_multiple_leading_spaces(void)
{
	char str[] = "    hello!";
	return strcmp(strstrip(str), "hello!");
}

static int test_string_util_strstrip_trailing_space(void)
{
	char str[] = "hello! ";
	return strcmp(strstrip(str), "hello!");
}

static int test_string_util_strstrip_multiple_trailing_spaces(void)
{
	char str[] = "hello!    ";
	return strcmp(strstrip(str), "hello!");
}

static int test_string_util_strstrip_leading_and_trailing_space(void)
{
	char str[] = " hello! ";
	return strcmp(strstrip(str), "hello!");
}

static int test_string_util_strstrip_multiple_leading_and_trailing_spaces(void)
{
	char str[] = "      hello!    ";
	return strcmp(strstrip(str), "hello!");
}

static int test_string_util_strstrip_middle_space(void)
{
	char str[] = "hello, world!";
	return strcmp(strstrip(str), "hello, world!");
}

static int test_string_util_strstrip_leading_and_middle_spaces(void)
{
	char str[] = "  hello, world!";
	return strcmp(strstrip(str), "hello, world!");
}

static int test_string_util_strstrip_leading_and_middle_and_trailing_spaces(void)
{
	char str[] = "  hello, world!   ";
	return strcmp(strstrip(str), "hello, world!");
}

static int test_string_util_strstrip(void)
{
	struct test_suite test_suite = TEST_SUITE_INIT("string-util: strstrip");
	test_suite_add_unit_test(&test_suite,
		test_string_util_strstrip_null_string, "null string");
	test_suite_add_unit_test(&test_suite,
		test_string_util_strstrip_empty_string, "empty string");
	test_suite_add_unit_test(&test_suite,
		test_string_util_strstrip_one_space, "one space");
	test_suite_add_unit_test(&test_suite,
		test_string_util_strstrip_multiple_spaces, "multiple spaces");
	test_suite_add_unit_test(&test_suite,
		test_string_util_strstrip_leading_space, "leading space");
	test_suite_add_unit_test(&test_suite,
		test_string_util_strstrip_multiple_leading_spaces, "multiple leading spaces");
	test_suite_add_unit_test(&test_suite,
		test_string_util_strstrip_trailing_space, "trailing space");
	test_suite_add_unit_test(&test_suite,
		test_string_util_strstrip_multiple_trailing_spaces, "multiple trailing spaces");
	test_suite_add_unit_test(&test_suite,
		test_string_util_strstrip_leading_and_trailing_space, "leading and trailing space");
	test_suite_add_unit_test(&test_suite,
		test_string_util_strstrip_multiple_leading_and_trailing_spaces, "multiple leading and trailing spaces");
	test_suite_add_unit_test(&test_suite,
		test_string_util_strstrip_middle_space, "middle space");
	test_suite_add_unit_test(&test_suite,
		test_string_util_strstrip_leading_and_middle_spaces, "leading and middle space");
	test_suite_add_unit_test(&test_suite,
		test_string_util_strstrip_leading_and_middle_and_trailing_spaces, "leading, middle, and trailing spaces");

	return test_suite_run(&test_suite);
}

static int test_string_util_truncate_nl(void)
{
	return 0;
}

static int test_string_util(void)
{
	int nr_errors = 0;

	nr_errors += test_string_util_strstrip();
	nr_errors += test_string_util_truncate_nl();

	return nr_errors;
}

int main(void)
{
	int nr_errors = 0;

	nr_errors += test_string_util();

	if (nr_errors > 0) {
		fprintf(stderr, "%d tests failed\n", nr_errors);
	} else {
		printf("All tests passed\n");
	}

	return nr_errors;
}

