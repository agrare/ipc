
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "conf-parser.h"
#include "string-util.h"

int conf_table_item_lookup(const void *table, const char *lvalue,
		conf_parser_callback *func, void **data, void *userdata)
{
	const struct conf_table_item *t;
	for (t = table; t->lvalue; t++) {
		if (strcmp(lvalue, t->lvalue))
			continue;
		*func = t->parser;
		*data = (uint8_t *) userdata + t->offset;
	}

	return 0;
}

static int parse_line(char *line, const void *table, void *userdata)
{
	char *lvalue, *rvalue, *p;
	conf_parser_callback func;
	void *data;

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

	if (conf_table_item_lookup(table, lvalue, &func, &data, userdata) != 0) {
		return -1;
	}

	if (func) {
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

int conf_parse_int(const char *lvalue, const char *rvalue, void *data)
{
	int *result = (int *) data;
	(void) lvalue;
	*result = atoi(rvalue);
	return 0;
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

