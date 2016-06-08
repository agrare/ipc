#include <systemd/sd-daemon.h>

#include "shared/conf-parser.h"
#include "shared/signal.h"

#include "ipcd.h"

int main(void)
{
	struct ipcd_conf ipcd_conf;
	int err;

	err = conf_parse(_CONF_DIR "/ipcd.conf", ipcd_conf_table, &ipcd_conf);
	if (err != 0) {
		return -1;
	}

	err = setup_signal_thread();
	if (err != 0) {
		return -1;
	}

	sd_notify(0, "READY=1");

	err = signal_thread(signal_handler);

	sd_notify(0, "STOPPING=1");

	return err;
}
