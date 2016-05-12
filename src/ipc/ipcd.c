#include "conf-parser.h"

int main(void)
{
	int err;

	err = conf_parse("ipcd.conf");
	if (err != 0) {
		return -1;
	}

	return 0;
}
