#ifndef _SHARED_STRING_UTIL_H
#define _SHARED_STRING_UTIL_H

extern char *strstrip(char *str);
extern int   strappend(char **dest, const char *src);
extern void truncate_nl(char *str);

#endif /* _SHARED_STRING_UTIL_H */

