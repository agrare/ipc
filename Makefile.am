ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}
AM_CPPFLAGS = \
	-include $(top_builddir)/config.h \
	-D_XOPEN_SOURCE=500               \
	-I $(top_srcdir)/src              \
	-I $(top_srcdir)/src/shared

pkginclude_HEADERS =
bin_PROGRAMS =
noinst_PROGRAMS =
lib_LTLIBRARIES =
noinst_LTLIBRARIES =

bin_PROGRAMS += ipcd
ipcd_SOURCES = \
	src/ipc/ipcd.c
ipcd_LDADD = \
	libshared.la

lib_LTLIBRARIES  += libipc.la
libipc_la_SOURCES = \
	src/libipc/libipc.h
pkginclude_HEADERS += \
	src/libipc/libipc.h

noinst_LTLIBRARIES  += libshared.la
libshared_la_SOURCES = \
	src/shared/conf-parser.h \
	src/shared/conf-parser.c \
	src/shared/string-util.h \
	src/shared/string-util.c

noinst_LTLIBRARIES += libtest.la
libtest_la_SOURCES = \
	src/test/test-suite.h \
	src/test/test-suite.c \
	src/test/unit-test.h \
	src/test/unit-test.c

noinst_PROGRAMS += test-shared
test_shared_SOURCES = \
	test/test-shared.c
test_shared_LDADD = \
	libshared.la \
	libtest.la
