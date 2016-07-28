
#include <stdio.h>
#include "test/test-suite.h"

int test_suite_add_unit_test(struct test_suite *test_suite,
		unit_test_fn_t unit_test_fn, const char *unit_test_name)
{
	return unit_test_set_add_unit_test(&test_suite->unit_tests, unit_test_fn, unit_test_name);
}

int test_suite_run(struct test_suite *test_suite)
{
	size_t i, nr_errors = 0;
	int res;

	printf("test suite: %s\n", test_suite->name);

	for (i = 0; i < test_suite->unit_tests.nr_unit_tests; i++) {
		struct unit_test *unit_test = &test_suite->unit_tests.unit_tests[i];

		res = unit_test_run(unit_test);

		printf("%s: %s: %s\n", test_suite->name, unit_test->unit_test_name,
		       res == 0 ? "success" : "failure");
		if (res != 0) {
			nr_errors++;
		}
	}

	printf("test suite: %s: %zu unit tests %zu errors\n",
	       test_suite->name, test_suite->unit_tests.nr_unit_tests, nr_errors);

	return (int) nr_errors;
}

