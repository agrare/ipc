
#ifndef _SHARED_SIGNAL_H
#define _SHARED_SIGNAL_H

extern int setup_signal_thread(void);
extern int signal_thread(int (*signal_handler)(int));
extern int signal_handler(int sig);

#endif /* _SHARED_SIGNAL_H */

