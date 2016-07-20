
#include <errno.h>
#include <stdio.h>
#include "test/test-suite.h"
#include "shared/conf-parser.h"

#define TEST_DATA_DIR "test/shared/data"

static int test_conf_parse_string_empty_string(void)
{
	char *result;
	int ret;

	ret = conf_parse_string(NULL, "", &result);
	if (!ret) {
		ret = result == NULL || result[0] != '\0';
	}

	return ret;
}

static void test_conf_parse_string(struct test_suite *test_suite)
{
	test_suite_add_unit_test(test_suite,
		test_conf_parse_string_empty_string,
		"conf_parse_string: empty string");
}

static int test_conf_parse_int_empty_string(void)
{
	int ret, result;

	ret = conf_parse_int(NULL, "", &result);
	if (!ret) {
		ret = result != 0;
	}

	return ret;
}

static int test_conf_parse_int_zero(void)
{
	int ret, result;

	ret = conf_parse_int(NULL, "0", &result);
	if (!ret) {
		ret = result != 0;
	}

	return ret;
}

static int test_conf_parse_int_overflow(void)
{
	int ret, result;

	ret = conf_parse_int(NULL, "2147483648", &result) != -ERANGE;

	return ret;
}

static int test_conf_parse_int_underflow(void)
{
	int ret, result;

	ret = conf_parse_int(NULL, "-2147483649", &result) != -ERANGE;

	return ret;
}

static int test_conf_parse_unsigned_overflow(void)
{
	int ret;
	unsigned result;

	ret = conf_parse_unsigned(NULL, "4294967296", &result) != -ERANGE;

	return ret;
}

static int test_conf_parse_unsigned_zero(void)
{
	int ret;
	unsigned result;

	ret = conf_parse_unsigned(NULL, "0", &result);
	if (!ret) {
		ret = result != 0;
	}

	return ret;
}

static void test_conf_parse_int(struct test_suite *test_suite)
{
	test_suite_add_unit_test(test_suite,
		test_conf_parse_int_empty_string,
		"conf_parse_int: empty string");
	test_suite_add_unit_test(test_suite,
		test_conf_parse_int_zero,
		"conf_parse_int: zero string");
	test_suite_add_unit_test(test_suite,
		test_conf_parse_int_overflow,
		"conf_parse_int: overflow");
	test_suite_add_unit_test(test_suite,
		test_conf_parse_int_underflow,
		"conf_parse_int: underflow");
	test_suite_add_unit_test(test_suite,
		test_conf_parse_unsigned_zero,
		"conf_parse_unsigned: zero string");
	test_suite_add_unit_test(test_suite,
		test_conf_parse_unsigned_overflow,
		"conf_parse_unsigned: overflow");
}

static int test_conf_parse_null_file(void)
{
	return conf_parse(NULL, NULL, NULL) != -1;
}

static int test_conf_parse_empty_file(void)
{
	const char path[] = TEST_DATA_DIR "/conf-parser-test-empty.conf";
	struct conf_table_item conf_table[] = {{0, 0, 0}};

	return conf_parse(path, conf_table, NULL);
}

static int test_conf_parse_newline_file(void)
{
	const char path[] = TEST_DATA_DIR "/conf-parser-test-newline.conf";
	struct conf_table_item conf_table[] = {{0, 0, 0}};

	return conf_parse(path, conf_table, NULL);
}

static int test_conf_parse_comments_file(void)
{
	const char path[] = TEST_DATA_DIR "/conf-parser-test-comments.conf";
	struct conf_table_item conf_table[] = {{0, 0, 0}};

	return conf_parse(path, conf_table, NULL);
}

static void test_conf_parse(struct test_suite *test_suite)
{
	test_suite_add_unit_test(test_suite,
		test_conf_parse_null_file, "conf_parse: null file");
	test_suite_add_unit_test(test_suite,
		test_conf_parse_empty_file, "conf_parse: empty file");
	test_suite_add_unit_test(test_suite,
		test_conf_parse_newline_file, "conf_parse: single newline");
	test_suite_add_unit_test(test_suite,
		test_conf_parse_comments_file, "conf_parse: only comments");
}

int main(void)
{
	struct test_suite conf_parser_test_suite =
		TEST_SUITE_INIT("conf-parser");
	int nr_errors;

	test_conf_parse_string(&conf_parser_test_suite);
	test_conf_parse_int(&conf_parser_test_suite);
	test_conf_parse(&conf_parser_test_suite);

	nr_errors = test_suite_run(&conf_parser_test_suite);
	if (nr_errors > 0) {
		fprintf(stderr, "%d tests failed\n", nr_errors);
	} else {
		printf("All tests passed\n");
	}

	return nr_errors;
}

