
#ifndef _SHARED_THREAD_H
#define _SHARED_THREAD_H

struct thread {
	pthread_t      tid;
	pthread_attr_t attr;
};

extern int thread_create(struct thread *t, void *(*fn)(void *), void *arg);

#endif /* _SHARED_THREAD_H */

