
#include <pthread.h>

#include "shared/thread.h"

int thread_create(struct thread *t, void *(*fn)(void *), void *arg)
{
	int err;

	err = pthread_attr_init(&t->attr);
	if (err != 0) {
		return -1;
	}

	err = pthread_attr_setdetachstate(&t->attr, PTHREAD_CREATE_JOINABLE);
	if (err != 0) {
		pthread_attr_destroy(&t->attr);
		return -1;
	}

	err = pthread_create(&t->tid, &t->attr, fn, arg);
	pthread_attr_destroy(&t->attr);

	return err;
}

