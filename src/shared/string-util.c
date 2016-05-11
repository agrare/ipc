
#include <string.h>

#include "string-util.h"

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

void truncate_nl(char *str)
{
	if (str) {
		str[strcspn(str, NEWLINE)] = 0;
	}
}

