#ifndef _SHARED_STRING_UTIL_H
#define _SHARED_STRING_UTIL_H

#define WHITESPACE " \t\n\r"
#define NEWLINE    "\n\r"
#define COMMENTS   "#"

extern char *strstrip(char *str);
extern void truncate_nl(char *str);

#endif /* _SHARED_STRING_UTIL_H */

