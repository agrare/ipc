
#include <stdio.h>
#include "test/test-suite.h"

int test_suite_add_unit_test(struct test_suite *test_suite,
		unit_test_fn_t unit_test_fn, const char *unit_test_name)
{
	return unit_test_set_add_unit_test(&test_suite->unit_tests, unit_test_fn, unit_test_name);
}

int test_suite_run(struct test_suite *test_suite)
{
	size_t i;
	int nr_errors = 0;

	printf("Running test suite: %s\n", test_suite->name);

	for (i = 0; i < test_suite->unit_tests.nr_unit_tests; i++) {
		struct unit_test *unit_test = &test_suite->unit_tests.unit_tests[i];
		if (unit_test_run(unit_test) != 0) {
			printf("Failed: %s: %s\n", test_suite->name, unit_test->unit_test_name);
			nr_errors++;
		}
	}

	return nr_errors;
}

