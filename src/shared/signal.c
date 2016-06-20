
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "shared/signal.h"

int setup_signal_thread(void)
{
	sigset_t sig_mask;
	int err;

	sigfillset(&sig_mask);
	sigdelset(&sig_mask, SIGKILL);
	sigdelset(&sig_mask, SIGSTOP);

	err = pthread_sigmask(SIG_SETMASK, &sig_mask, NULL);
	if (err) {
		fprintf(stderr, "pthread_sigmask: %s", strerror(err));
		return -1;
	}

	return 0;
}

int signal_thread(int (*signal_handler)(int))
{
	sigset_t sig_mask;
	int err, sig;

	sigfillset(&sig_mask);
	sigdelset(&sig_mask, SIGKILL);
	sigdelset(&sig_mask, SIGSTOP);

	for (;;) {
		err = sigwait(&sig_mask, &sig);
		if (err) {
			break;
		}

		if (signal_handler(sig)) {
			break;
		}
	}

	return err;
}

