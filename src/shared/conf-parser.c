
#include <stdio.h>
#include <string.h>

#include "conf-parser.h"
#include "string-util.h"

static int parse_line(char *line)
{
	char *key, *val, *p;

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

	key = strstrip(line);
	(void) key;
	val = strstrip(p);
	(void) val;

	return 0;
}

int conf_parse(const char *filename)
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

		err = parse_line(l);
	}

	if (!feof(f))
		err = -1;

	fclose(f);
	return err;
}

