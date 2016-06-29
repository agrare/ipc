#ifndef _IPCD_H_
#define _IPCD_H_

struct ipcd_conf {
	char *loglevel;
};

extern struct conf_table_item ipcd_conf_table[];

#endif /* _IPCD_H_ */

