
#include <getopt.h>
#include <stdio.h>
#include <signal.h>
#include <systemd/sd-daemon.h>
#include <systemd/sd-journal.h>

#include "shared/conf-parser.h"
#include "shared/signal.h"

#include "ipcd.h"

static int verbose = 0;

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

int main(int argc, char *argv[])
{
	const char *conf_file = _CONF_DIR "/ipcd.conf";
	struct ipcd_conf ipcd_conf;
	int err, n_fds;

	for (;;) {
		int c, option_index = 0;
		const char *option_string = "f:";

		static struct option long_options[] = {
			{"file",    required_argument, 0,        'f'},
			{"verbose", no_argument,       &verbose, 1},
			{0,         0,                 0,        0}
		};

		c = getopt_long(argc, argv, option_string,
		                long_options, &option_index);
		if (c == -1) {
			break;
		}

		switch (c) {
		case 'f':
			conf_file = optarg;
			break;
		default:
			break;
		}
	}

	err = conf_parse(conf_file, ipcd_conf_table, &ipcd_conf);
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

