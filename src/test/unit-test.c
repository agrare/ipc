
#include <stdlib.h>
#include <string.h>
#include "test/unit-test.h"

void unit_test_init(struct unit_test *unit_test)
{
	memset(unit_test, 0, sizeof(*unit_test));
}

int unit_test_set_add_unit_test(struct unit_test_set *unit_test_set,
		unit_test_fn_t unit_test_fn, const char *unit_test_name)
{
	size_t nr_unit_tests, unit_test_set_size;

	if (!unit_test_set) {
		return -1;
	}

	nr_unit_tests = unit_test_set->nr_unit_tests;
	unit_test_set_size = sizeof(*unit_test_set->unit_tests) * (nr_unit_tests + 1);

	unit_test_set->unit_tests = realloc(unit_test_set->unit_tests, unit_test_set_size);
	if (!unit_test_set->unit_tests) {
		return -1;
	}

	unit_test_init(&unit_test_set->unit_tests[nr_unit_tests]);
	unit_test_set->unit_tests[nr_unit_tests].unit_test_fn = unit_test_fn;
	unit_test_set->unit_tests[nr_unit_tests].unit_test_name = unit_test_name;
	unit_test_set->nr_unit_tests = nr_unit_tests + 1;

	return 0;
}

int unit_test_run(struct unit_test *unit_test)
{
	return unit_test->unit_test_fn();
}

