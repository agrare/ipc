#ifndef _IPCD_H_
#define _IPCD_H_

struct ipcd_conf {
	char *loglevel;
};

struct conf_table_item ipcd_conf_table[] = {
	{"loglevel", conf_parse_string, offsetof(struct ipcd_conf, loglevel)},
	{0, 0, 0}
};

#endif /* _IPCD_H_ */
