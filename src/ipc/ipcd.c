#include "conf-parser.h"
#include "ipcd.h"

int main(void)
{
	struct ipcd_conf ipcd_conf;
	int err;

	err = conf_parse("src/ipc/ipcd.conf", ipcd_conf_table, &ipcd_conf);
	if (err != 0) {
		return -1;
	}

	return 0;
}
