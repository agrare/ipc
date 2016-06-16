
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "libipc.h"

struct libipc_conn {
	int sockfd;
};

static void conn_init(struct libipc_conn *conn)
{
	conn->sockfd = -1;
}

static int conn_alloc(struct libipc_conn **conn)
{
	if ((*conn = malloc(sizeof(**conn))) == NULL) {
		return -1;
	}

	conn_init(*conn);

	return 0;
}

static void conn_cleanup(struct libipc_conn *conn)
{
	if (conn->sockfd != -1) {
		close(conn->sockfd);
	}
}

static void conn_free(struct libipc_conn *conn)
{
	if (conn) {
		conn_cleanup(conn);
		free(conn);
	}
}

static int connect_to_host(const char *hostname, int port)
{
	struct addrinfo hints, *servinfo, *p;
	int sockfd = -1, s, err;
	char service[16];

	memset(&hints, 0, sizeof(hints));
	hints.ai_family   = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	snprintf(service, sizeof(service), "%d", port);

	err = getaddrinfo(hostname, service, &hints, &servinfo);
	if (err != 0) {
		return -1;
	}

	for (p = servinfo; p != NULL; p = p->ai_next) {
		s = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (s == -1) {
			continue;
		}

		err = connect(s, p->ai_addr, p->ai_addrlen);
		if (err == -1) {
			close(s);
			continue;
		}

		sockfd = s;
		break;
	}

	freeaddrinfo(servinfo);

	return sockfd;
}

int libipc_open(struct libipc_conn **conn, const char *hostname, int port)
{
	struct libipc_conn *c;

	if (conn_alloc(&c) != 0) {
		return -1;
	}

	c->sockfd = connect_to_host(hostname, port);
	if (c->sockfd == -1) {
		conn_free(c);
		return -1;
	}

	*conn = c;
	return 0;
}

int libipc_close(struct libipc_conn *conn)
{
	if (!conn) {
		return -1;
	}

	conn_free(conn);

	return 0;
}

ssize_t libipc_read(struct libipc_conn *conn, void *buf, size_t count)
{
	int flags;
	ssize_t ret;

	flags = 0;

	ret = recvfrom(conn->sockfd, buf, count, flags, NULL, 0);

	return ret;
}

ssize_t libipc_write(struct libipc_conn *conn, const void *buf, size_t count)
{
	int flags;
	ssize_t ret;

	flags = 0;

	ret = sendto(conn->sockfd, buf, count, flags, NULL, 0);

	return ret;
}

