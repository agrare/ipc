
#ifndef _LIBIPC_H
#define _LIBIPC_H

struct libipc_conn;

extern int libipc_open(struct libipc_conn **conn, const char *hostname, int port);

extern int libipc_close(struct libipc_conn *conn);

extern ssize_t libipc_read(struct libipc_conn *conn, void *buf, size_t count);

extern ssize_t libipc_write(struct libipc_conn *conn, const void *buf, size_t count);

#endif /* _LIBIPC_H */

