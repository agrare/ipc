
#ifndef _SHARED_LOG_H
#define _SHARED_LOG_H

#include <string.h>             /* strerror_r */
#include <systemd/sd-journal.h> /* sd_journal_print */

#define _log_common(level, fmt, ...) sd_journal_print(level, fmt, ##__VA_ARGS__)
#define log_emerg(fmt, ...)  _log_common(LOG_EMERG,   fmt, ##__VA_ARGS__)
#define log_alert(fmt, ...)  _log_common(LOG_ALERT,   fmt, ##__VA_ARGS__)
#define log_crit(fmt, ...)   _log_common(LOG_CRIT,    fmt, ##__VA_ARGS__)
#define log_err(fmt, ...)    _log_common(LOG_ERR,     fmt, ##__VA_ARGS__)
#define log_warn(fmt, ...)   _log_common(LOG_WARNING, fmt, ##__VA_ARGS__)
#define log_notice(fmt, ...) _log_common(LOG_NOTICE,  fmt, ##__VA_ARGS__)
#define log_info(fmt, ...)   _log_common(LOG_INFO,    fmt, ##__VA_ARGS__)
#define log_debug(fmt, ...)  _log_common(LOG_DEBUG,   fmt, ##__VA_ARGS__)

#define log_err_errno(errnum, fmt, ...) do {        \
	char errbuf[1024];                          \
	strerror_r(errnum, errbuf, sizeof(errbuf)); \
	log_err(fmt ": %s", ##__VA_ARGS__, errbuf); \
} while (0)

#endif /* _SHARED_LOG_H */

