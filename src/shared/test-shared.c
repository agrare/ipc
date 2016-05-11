
#include <stdio.h>
#include <string.h>
#include "string-util.h"

struct unit_test {
	int (*unit_test_fn)(void);
	const char *name;
};

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
	int err, nr_errors = 0;
	size_t i, nr_tests;

	struct unit_test unit_tests[] = {
		{test_string_util_strstrip_null_string,               "strstrip: null string"},
		{test_string_util_strstrip_empty_string,              "strstrip: empty string"},
		{test_string_util_strstrip_one_space,                 "strstrip: one space"},
		{test_string_util_strstrip_multiple_spaces,           "strstrip: multiple spaces"},
		{test_string_util_strstrip_leading_space,             "strstrip: leading space"},
		{test_string_util_strstrip_multiple_leading_spaces,   "strstrip: multiple leading spaces"},
		{test_string_util_strstrip_trailing_space,            "strstrip: trailing space"},
		{test_string_util_strstrip_multiple_trailing_spaces,  "strstrip: multiple trailing spaces"},
		{test_string_util_strstrip_leading_and_trailing_space,             "strstrip: leading and trailing space"},
		{test_string_util_strstrip_multiple_leading_and_trailing_spaces,   "strstrip: multiple leading and trailing spaces"},
		{test_string_util_strstrip_middle_space,              "strstrip: middle space"},
		{test_string_util_strstrip_leading_and_middle_spaces, "strstrip: leading and middle space"},
		{test_string_util_strstrip_leading_and_middle_and_trailing_spaces, "strstrip: leading, middle, and trailing spaces"},
	};

	nr_tests = sizeof(unit_tests)/sizeof(*unit_tests);

	for (i = 0; i < nr_tests; i++) {
		struct unit_test *ut = &unit_tests[i];

		err = ut->unit_test_fn();
		if (err != 0) {
			fprintf(stderr, "%s: failed\n", ut->name);
			nr_errors++;
		}
	}

	return nr_errors;
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

