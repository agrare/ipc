
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <poll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include "shared/log.h"

#include "ipcd.h"

#define _MAX_SOCKETS 1024

static int ipcd_listen_accept(int sockfd)
{
	struct sockaddr_storage addr;
	socklen_t len;
	int fd;

	len = sizeof(addr);

	fd = accept(sockfd, (struct sockaddr *) &addr, &len);
	if (fd == -1) {
		log_err_errno(errno, "accept");
		return -1;
	}

	if (fcntl(fd, F_SETFD, O_NONBLOCK) == -1) {
		log_err_errno(errno, "fcntl");
		close(fd);
		return -1;
	}

	return fd;
}

void *ipcd_listen(void *arg)
{
	struct pollfd fds[_MAX_SOCKETS];
	int err, listen_fd = (uintptr_t) arg;
	nfds_t i, nfds = 1;

	if (fcntl(listen_fd, F_SETFD, O_NONBLOCK) == -1) {
		log_err_errno(errno, "fcntl %d", listen_fd);
		pthread_exit((void *) -1);
	}

	fds[0].fd = listen_fd;
	fds[0].events = POLLIN;

	for (i = 1; i < _MAX_SOCKETS; i++) {
		fds[i].fd = -1;
		fds[i].events = 0;
	}

	for (;;) {
		int new_fd = -1;

		log_info("polling for events");

		err = poll(fds, nfds, -1);
		if (err == -1) {
			log_err_errno(errno, "poll");
			continue;
		} else if (err == 0) {
			continue;
		}

		for (i = 0; i < nfds; i++) {
			if (fds[i].revents == 0) {
				continue;
			}

			if (fds[i].fd == listen_fd) {
				new_fd = ipcd_listen_accept(fds[i].fd);
				if (new_fd != -1) {
					log_info("received new connection %d", new_fd);
				}
			} else {
				char buf[1024];
				ssize_t len = read(fds[i].fd, buf, sizeof(buf));
				if (len == -1) {
					log_err_errno(errno, "read");
				} else if (len == 0) {
					log_info("closing connection %d", fds[i].fd);
					close(fds[i].fd);
					fds[i].fd = -1;
				} else {
					log_info("received %s from client", buf);
					write(fds[i].fd, buf, len);
				}
			}
		}

		if (new_fd != -1) {
			if (nfds >= _MAX_SOCKETS) {
				close(new_fd);
			} else {
				fds[nfds].fd = new_fd;
				fds[nfds].events = POLLIN;
				nfds++;
			}
		}
	}

	pthread_exit(NULL);
}

