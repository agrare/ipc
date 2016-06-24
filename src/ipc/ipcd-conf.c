
#include "shared/conf-parser.h"
#include "ipcd.h"

struct conf_table_item ipcd_conf_table[] = {
	{"loglevel", conf_parse_string, offsetof(struct ipcd_conf, loglevel)},
	{0, 0, 0}
};

