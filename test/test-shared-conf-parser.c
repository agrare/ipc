
#include <stdio.h>
#include "test/test-suite.h"

int main(void)
{
	int nr_errors = 0;

	if (nr_errors > 0) {
		fprintf(stderr, "%d tests failed\n", nr_errors);
	} else {
		printf("All tests passed\n");
	}

	return nr_errors;
}

