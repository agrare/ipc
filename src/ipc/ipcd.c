#include <stdio.h>
#include <signal.h>
#include <systemd/sd-daemon.h>

#include "shared/conf-parser.h"
#include "shared/signal.h"

#include "ipcd.h"

static int signal_handler(int sig)
{
	printf("received signal %d\n", sig);

	switch (sig) {
	case SIGINT:
	case SIGTERM:
		return 1;
	case SIGHUP:
		/* TODO reload config */
	default:
		return 0;
	}
}

int main(void)
{
	struct ipcd_conf ipcd_conf;
	int err, n_fds;

	err = conf_parse(_CONF_DIR "/ipcd.conf", ipcd_conf_table, &ipcd_conf);
	if (err != 0) {
		return -1;
	}

	err = setup_signal_thread();
	if (err != 0) {
		return -1;
	}

	n_fds = sd_listen_fds(1);
	if (n_fds < 0) {
		return -1;
	}

	sd_notify(0, "READY=1");

	err = signal_thread(signal_handler);

	sd_notify(0, "STOPPING=1");

	return err;
}
