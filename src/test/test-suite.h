#ifndef _TEST_SUITE_H
#define _TEST_SUITE_H

#include "test/unit-test.h"

struct test_suite {
	const char *name;
	struct unit_test_set unit_tests;
};

#define TEST_SUITE_INIT(NAME) { NAME, UNIT_TEST_SET_INIT }

extern int test_suite_add_unit_test(struct test_suite *test_suite,
		unit_test_fn_t unit_test_fn, const char *unit_test_name);

extern int test_suite_run(struct test_suite *test_suite);

#endif /* _TEST_SUITE_H */

