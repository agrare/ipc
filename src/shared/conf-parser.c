
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "conf-parser.h"
#include "string-util.h"

#define COMMENTS   "#"

void conf_table_item_lookup(const void *table, const char *lvalue,
                            conf_parser_callback *func, void **data,
                            void *userdata)
{
	const struct conf_table_item *t;

	for (t = table; t->lvalue; t++) {
		if (strcmp(lvalue, t->lvalue))
			continue;
		*func = t->parser;
		*data = (uint8_t *) userdata + t->offset;
	}
}

static int parse_line(char *line, const void *table, void *userdata)
{
	char *lvalue, *rvalue, *p;
	conf_parser_callback func = NULL;
	void *data = NULL;

	/* strip leading and trailing whitespace */
	line = strstrip(line);
	if (!line) {
		return 0;
	}

	/* return if the first character is a newline or comment */
	if (strchr(COMMENTS "\n", line[0])) {
		return 0;
	}

	/* handle config file sections */
	if (line[0] == '[') {
		/* TODO */
		return 0;
	}

	/* split the config line into key = val pairs */
	p = strchr(line, '=');
	if (!p) {
		return -1;
	}

	*p = 0;
	p++;

	lvalue = strstrip(line);
	rvalue = strstrip(p);

	conf_table_item_lookup(table, lvalue, &func, &data, userdata);

	if (func && data) {
		return func(lvalue, rvalue, data);
	}

	return 0;
}

int conf_parse(const char *filename, const void *table, void *userdata)
{
	FILE *f;
	int err = 0;

	if (!filename) {
		return -1;
	}

	f = fopen(filename, "r");
	if (!f) {
		return -1;
	}

	while (!err && !feof(f)) {
		char l[2048];

		if (!fgets(l, sizeof(l), f))
			break;

		truncate_nl(l);

		err = parse_line(l, table, userdata);
	}

	if (!feof(f))
		err = -1;

	fclose(f);
	return err;
}

static int conf_parse_int_internal(const char *lvalue, const char *rvalue,
		long long int *result)
{
	int err = 0, save_errno;
	char *endptr;

	(void) lvalue;

	save_errno = errno;
	errno = 0;

	*result = strtoll(rvalue, &endptr, 0);
	if (errno != 0) {
		err = -errno;
	}

	errno = save_errno;

	return err;
}

static int conf_parse_unsigned_internal(const char *lvalue, const char *rvalue,
		unsigned long long int *result)
{
	int err = 0, save_errno;
	char *endptr;

	(void) lvalue;

	save_errno = errno;
	errno = 0;

	*result = strtoull(rvalue, &endptr, 0);
	if (errno != 0) {
		err = -errno;
	}

	errno = save_errno;

	return err;
}

int conf_parse_int(const char *lvalue, const char *rvalue, void *data)
{
	long long int result;
	int err;

	err = conf_parse_int_internal(lvalue, rvalue, &result);
	if (!err) {
		if (result > INT_MAX || result < INT_MIN) {
			err = -ERANGE;
		} else {
			*((int *) data) = result;
		}
	}

	return err;
}

int conf_parse_long_int(const char *lvalue, const char *rvalue, void *data)
{
	long long int result;
	int err;

	err = conf_parse_int_internal(lvalue, rvalue, &result);
	if (!err) {
		if (result > LONG_MAX || result < LONG_MIN) {
			err = -ERANGE;
		} else {
			*((int *) data) = result;
		}
	}

	return err;
}

int conf_parse_long_long_int(const char *lvalue, const char *rvalue, void *data)
{
	long long int result;
	int err;

	err = conf_parse_int_internal(lvalue, rvalue, &result);
	if (!err) {
		if (result > LLONG_MAX || result < LLONG_MIN) {
			err = -ERANGE;
		} else {
			*((int *) data) = result;
		}
	}

	return err;
}

int conf_parse_unsigned(const char *lvalue, const char *rvalue, void *data)
{
	unsigned long long int result;
	int err;

	err = conf_parse_unsigned_internal(lvalue, rvalue, &result);
	if (!err) {
		if (result > UINT_MAX) {
			err = -ERANGE;
		} else {
			*((int *) data) = result;
		}
	}

	return err;
}

int conf_parse_unsigned_long(const char *lvalue, const char *rvalue, void *data)
{
	unsigned long long int result;
	int err;

	err = conf_parse_unsigned_internal(lvalue, rvalue, &result);
	if (!err) {
		if (result > ULONG_MAX) {
			err = -ERANGE;
		} else {
			*((int *) data) = result;
		}
	}

	return err;
}

int conf_parse_unsigned_long_long(const char *lvalue, const char *rvalue, void *data)
{
	unsigned long long int result;
	int err;

	err = conf_parse_unsigned_internal(lvalue, rvalue, &result);
	if (!err) {
		if (result > ULLONG_MAX) {
			err = -ERANGE;
		} else {
			*((int *) data) = result;
		}
	}

	return err;
}

int conf_parse_string(const char *lvalue, const char *rvalue, void *data)
{
	char **result = (char **) data;
	(void) lvalue;
	*result = strdup(rvalue);
	if (!*result)
		return -1;
	return 0;
}

