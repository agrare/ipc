
#include <errno.h>
#include <getopt.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <systemd/sd-daemon.h>
#include <systemd/sd-journal.h>

#include "shared/conf-parser.h"
#include "shared/log.h"
#include "shared/signal.h"

#include "ipcd.h"

static int verbose = 0;

static struct conf_table_item ipcd_conf_table[] = {
	{"loglevel", conf_parse_string, offsetof(struct ipcd_conf, loglevel)},
	{0, 0, 0}
};

static int signal_handler(int sig)
{
	log_info("received signal %d", sig);

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

static int setup_listen_thread(pthread_t *tid, int n_fds)
{
	int err;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	err = pthread_create(tid, &attr, ipcd_listen, (void *) (uintptr_t) n_fds);

	pthread_attr_destroy(&attr);

	return err;
}

static int stop_listen_thread(pthread_t thread)
{
	void *retval;
	int err;

	err = pthread_cancel(thread);
	if (err != 0) {
		log_err_errno(-err, "failed to cancel listen thread");
		return err;
	}

	err = pthread_join(thread, &retval);
	if (err != 0) {
		log_err_errno(-err, "failed to join listen threda");
		return err;
	}

	log_info("listen thread exited with code %p", retval);

	return 0;
}

int main(int argc, char *argv[])
{
	const char *conf_file = _CONF_DIR "/ipcd.conf";
	struct ipcd_conf ipcd_conf;
	pthread_t listen_thread;
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
		log_err_errno(errno, "failed to parse %s", conf_file);
		return -1;
	}

	err = setup_signal_thread();
	if (err != 0) {
		log_err_errno(errno, "failed to set up signal mask");
		return -1;
	}

	err = sd_listen_fds(1);
	if (err < 0) {
		log_err_errno(-err, "failed to get number of listen fds");
		return -1;
	} else {
		n_fds = err;
	}

	err = setup_listen_thread(&listen_thread, n_fds);
	if (err != 0) {
		log_err_errno(-err, "failed to create listen threads");
		return -1;
	}

	sd_notify(0, "READY=1");

	err = signal_thread(signal_handler);

	sd_notify(0, "STOPPING=1");

	if (stop_listen_thread(listen_thread) != 0) {
		log_err("failed to cleanly shutdown listen thread");
	} else {
		log_info("listen thread stopped");
	}

	return err;
}

