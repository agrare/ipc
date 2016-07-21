
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "string-util.h"

#define WHITESPACE " \t\n\r"
#define NEWLINE    "\n\r"

char *strstrip(char *str)
{
	char *p;
	if (str) {
		str += strspn(str, WHITESPACE);
		for (p = strchr(str, '\0'); p > str; p--) {
			if (!strchr(WHITESPACE, p[-1]))
				break;
		}

		*p = '\0';
	}

	return str;
}

int strappend(char **dest, const char *src)
{
	short initial;
	size_t len;

	if (!dest) {
		return -1;
	}

	initial = *dest == NULL;

	len = strlen(src);
	if (!initial) {
		len += strlen(*dest);
	}

	*dest = realloc(*dest, len + 1);
	if (*dest == NULL) {
		return -errno;
	}

	if (initial) {
		(*dest)[0] = '\0';
	}

	strcat(*dest, src);

	return 0;
}

void truncate_nl(char *str)
{
	if (str) {
		str[strcspn(str, NEWLINE)] = 0;
	}
}

