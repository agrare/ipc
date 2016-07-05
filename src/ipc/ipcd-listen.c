
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <poll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <systemd/sd-daemon.h>
#include <unistd.h>

#include "shared/log.h"

#include "ipcd.h"

#define _MAX_FDS 1024

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

static int setup_listen_fds(struct pollfd *fds, int n_fds)
{
	int i, fd, err = 0;

	for (i = 0; i < n_fds; i++) {
		fd = SD_LISTEN_FDS_START + i;

		err = fcntl(fd, F_SETFD, O_NONBLOCK);
		if (err == -1) {
			log_err_errno(errno, "fcntl %d O_NONBLOCK", fd);
			break;
		}

		fds[i].fd     = fd;
		fds[i].events = POLLIN;
	}

	return 0;
}

void *ipcd_listen(void *arg)
{
	int i, err, n_fds, n_listen_fds;
	struct pollfd fds[_MAX_FDS] = {{-1, 0, 0}};

	n_fds = n_listen_fds = (uintptr_t) arg;

	if (setup_listen_fds(fds, n_listen_fds) != 0) {
		pthread_exit((void *) -1);
	}

	for (;;) {
		int new_fd = -1;

		log_info("polling for events");

		err = poll(fds, n_fds, -1);
		if (err == -1) {
			log_err_errno(errno, "poll");
			continue;
		} else if (err == 0) {
			continue;
		}

		for (i = 0; i < n_fds; i++) {
			if (fds[i].revents == 0) {
				continue;
			}

			if (i < n_listen_fds) {
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
			if (n_fds >= _MAX_FDS) {
				close(new_fd);
			} else {
				fds[n_fds].fd = new_fd;
				fds[n_fds].events = POLLIN;
				n_fds++;
			}
		}
	}

	pthread_exit(NULL);
}

