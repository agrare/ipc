ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}
AM_CPPFLAGS = \
	-include $(top_builddir)/config.h \
	-I $(top_srcdir)/src              \
	-I $(top_srcdir)/src/shared

bin_PROGRAMS =
noinst_PROGRAMS =
lib_LTLIBRARIES =
noinst_LTLIBRARIES =

bin_PROGRAMS += ipcd
ipcd_SOURCES  = src/ipc/ipcd.c

lib_LTLIBRARIES  += libipc.la
libipc_la_SOURCES = src/libipc/libipc.h

noinst_LTLIBRARIES  += libshared.la
libshared_la_SOURCES = \
	src/shared/string-util.h \
	src/shared/string-util.c

noinst_PROGRAMS += test-shared
test_shared_SOURCES = src/shared/test-shared.c
test_shared_LDADD   = libshared.la
