#ifndef _UNIT_TEST_H
#define _UNIT_TEST_H

#include <unistd.h>

typedef int (*unit_test_fn_t)(void);

struct unit_test {
	unit_test_fn_t unit_test_fn;
	const char    *unit_test_name;
	int            unit_test_return_code;
	char         **unit_test_error_stack;
};

struct unit_test_set {
	size_t            nr_unit_tests;
	struct unit_test *unit_tests;
};

#define UNIT_TEST_SET_INIT { 0, NULL }

extern int unit_test_set_add_unit_test(struct unit_test_set *unit_test_set,
		unit_test_fn_t unit_test_fn, const char *unit_test_name);

extern int unit_test_run(struct unit_test *unit_test);

#endif /* _UNIT_TEST_H */

