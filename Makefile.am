ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}
AM_CPPFLAGS = \
	-include $(top_builddir)/config.h \
	-D_XOPEN_SOURCE=500               \
	-I $(top_srcdir)/src              \
	-I $(top_srcdir)/src/shared

systemunitdir=$(prefix)/lib/systemd/system

pkginclude_HEADERS =
bin_PROGRAMS =
noinst_PROGRAMS =
TESTS =
lib_LTLIBRARIES =
noinst_LTLIBRARIES =
dist_systemunit_DATA =

bin_PROGRAMS += ipcd
ipcd_SOURCES = \
	src/ipc/ipcd.c
ipcd_LDADD = \
	libshared.la
dist_systemunit_DATA += \
	units/ipcd.socket \
	units/ipcd.service
units/ipcd.service: units/ipcd.service.in $(top_builddir)/config.status
	$(SED) \
	    -e 's|[@]prefix@|$(prefix)|g' \
	    -e 's|[@]exec_prefix@|$(exec_prefix)|g' \
	    -e 's|[@]sbindir@|$(sbindir)|g' \
	    -e 's|[@]datarootdir@|$(datarootdir)|g' \
	    < "$<" > "$@"

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

noinst_PROGRAMS += test-shared-string-util
test_shared_string_util_SOURCES = \
	test/test-shared-string-util.c
test_shared_string_util_LDADD = \
	libshared.la \
	libtest.la
TESTS += test-shared-string-util

noinst_PROGRAMS += test-shared-conf-parser
test_shared_conf_parser_SOURCES = \
	test/test-shared-conf-parser.c
test_shared_conf_parser_LDADD = \
	libshared.la \
	libtest.la
TESTS += test-shared-conf-parser
