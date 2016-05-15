#ifndef _SHARED_CONF_PARSER_H
#define _SHARED_CONF_PARSER_H

#include <stddef.h>

typedef int (*conf_parser_callback)(const char *lvalue,
		const char *rvalue, void *data);

struct conf_table_item {
	const char          *lvalue;
	conf_parser_callback parser;
	size_t               offset;
};

extern int conf_parse(const char *filename, const void *table, void *userdata);

extern int conf_parse_int(const char *lvalue, const char *rvalue, void *data);
extern int conf_parse_string(const char *lvalue, const char *rvalue, void *data);

#endif /* _SHARED_CONF_PARSER_H */

