#ifndef _IPCD_H_
#define _IPCD_H_

struct ipcd_conf {
	char *loglevel;
};

extern void *ipcd_listen(void *arg);

#endif /* _IPCD_H_ */

