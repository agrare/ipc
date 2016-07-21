
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "test/test-suite.h"
#include "shared/string-util.h"

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

static void test_string_util_strstrip(struct test_suite *test_suite)
{
	test_suite_add_unit_test(test_suite,
		test_string_util_strstrip_null_string,
		"strstrip: null string");
	test_suite_add_unit_test(test_suite,
		test_string_util_strstrip_empty_string,
		"strstrip: empty string");
	test_suite_add_unit_test(test_suite,
		test_string_util_strstrip_one_space,
		"strstrip: one space");
	test_suite_add_unit_test(test_suite,
		test_string_util_strstrip_multiple_spaces,
		"strstrip: multiple spaces");
	test_suite_add_unit_test(test_suite,
		test_string_util_strstrip_leading_space,
		"strstrip: leading space");
	test_suite_add_unit_test(test_suite,
		test_string_util_strstrip_multiple_leading_spaces,
		"strstrip: multiple leading spaces");
	test_suite_add_unit_test(test_suite,
		test_string_util_strstrip_trailing_space,
		"strstrip: trailing space");
	test_suite_add_unit_test(test_suite,
		test_string_util_strstrip_multiple_trailing_spaces,
		"strstrip: multiple trailing spaces");
	test_suite_add_unit_test(test_suite,
		test_string_util_strstrip_leading_and_trailing_space,
		"strstrip: leading and trailing space");
	test_suite_add_unit_test(test_suite,
		test_string_util_strstrip_multiple_leading_and_trailing_spaces,
		"strstrip: multiple leading and trailing spaces");
	test_suite_add_unit_test(test_suite,
		test_string_util_strstrip_middle_space,
		"strstrip: middle space");
	test_suite_add_unit_test(test_suite,
		test_string_util_strstrip_leading_and_middle_spaces,
		"strstrip: leading and middle space");
	test_suite_add_unit_test(test_suite,
		test_string_util_strstrip_leading_and_middle_and_trailing_spaces,
		"strstrip: leading, middle, and trailing spaces");

}

static int test_string_util_strappend_null(void)
{
	return strappend(NULL, NULL) != -1;
}

static int test_string_util_strappend_initial(void)
{
	const char *src = "source string";
	char *dest = NULL;
	int ret;

	ret = strappend(&dest, src);
	if (!ret) {
		ret = strcmp(dest, src) != 0;
		free(dest);
	}

	return ret;
}

static int test_string_util_strappend_empty_dest(void)
{
	const char *src = "source string";
	char *dest = strdup("");
	int ret;

	ret = strappend(&dest, src);
	if (!ret) {
		ret = strcmp(dest, src) != 0;
		free(dest);
	}

	return ret;
}

static int test_string_util_strappend_empty_src(void)
{
	const char *src = "";
	char *dest = strdup("dest string");
	int ret;

	ret = strappend(&dest, src);
	if (!ret) {
		ret = strcmp(dest, "dest string") != 0;
		free(dest);
	}

	return ret;
}

static int test_string_util_strappend_concat(void)
{
	const char *src = "world!";
	char *dest = strdup("hello, ");
	int ret;

	ret = strappend(&dest, src);
	if (!ret) {
		ret = strcmp(dest, "hello, world!") != 0;
		free(dest);
	}

	return ret;
}

static void test_string_util_strappend(struct test_suite *test_suite)
{
	test_suite_add_unit_test(test_suite,
		test_string_util_strappend_null,
		"strappend: null");
	test_suite_add_unit_test(test_suite,
		test_string_util_strappend_initial,
		"strappend: initial alloc");
	test_suite_add_unit_test(test_suite,
		test_string_util_strappend_empty_dest,
		"strappend: empty dest");
	test_suite_add_unit_test(test_suite,
		test_string_util_strappend_empty_src,
		"strappend: empty source");
	test_suite_add_unit_test(test_suite,
		test_string_util_strappend_concat,
		"strappend: concatenate strings");
}

static int test_string_util_truncate_nl_null(void)
{
	truncate_nl(NULL); /* make sure it doesn't segfault */
	return 0;
}

static int test_string_util_truncate_nl_empty_string(void)
{
	char str[] = "";
	truncate_nl(str);
	return strcmp(str, "");
}

static int test_string_util_truncate_nl_newline_only(void)
{
	char str[] = "\n";
	truncate_nl(str);
	return strcmp(str, "");
}

static int test_string_util_truncate_nl_newline_last_char(void)
{
	char str[] = "hello, world!\n";
	truncate_nl(str);
	return strcmp(str, "hello, world!");
}

static int test_string_util_truncate_nl_newline_first_char(void)
{
	char str[] = "\nhello, world!";
	truncate_nl(str);
	return strcmp(str, "");
}

static int test_string_util_truncate_nl_newline_middle(void)
{
	char str[] = "hello, \nworld!";
	truncate_nl(str);
	return strcmp(str, "hello, ");
}

static void test_string_util_truncate_nl(struct test_suite *test_suite)
{
	test_suite_add_unit_test(test_suite,
		test_string_util_truncate_nl_null,
		"truncate_nl: null pointer");
	test_suite_add_unit_test(test_suite,
		test_string_util_truncate_nl_empty_string,
		"truncate_nl: empty string");
	test_suite_add_unit_test(test_suite,
		test_string_util_truncate_nl_newline_only,
		"truncate_nl: newline only");
	test_suite_add_unit_test(test_suite,
		test_string_util_truncate_nl_newline_last_char,
		"truncate_nl: newline last char");
	test_suite_add_unit_test(test_suite,
		test_string_util_truncate_nl_newline_first_char,
		"truncate_nl: newline first char");
	test_suite_add_unit_test(test_suite,
		test_string_util_truncate_nl_newline_middle,
		"truncate_nl: newline middle");
}

int main(void)
{
	struct test_suite test_suite = TEST_SUITE_INIT("string-util");
	int nr_errors;

	test_string_util_strstrip(&test_suite);
	test_string_util_strappend(&test_suite);
	test_string_util_truncate_nl(&test_suite);

	nr_errors = test_suite_run(&test_suite);
	if (nr_errors > 0) {
		fprintf(stderr, "%d tests failed\n", nr_errors);
	} else {
		printf("All tests passed\n");
	}

	return nr_errors;
}

