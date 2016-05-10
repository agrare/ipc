ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}
AM_CPPFLAGS = \
	-include $(top_builddir)/config.h \
	-I $(top_srcdir)/src

bin_PROGRAMS =
lib_LTLIBRARIES =
noinst_LTLIBRARIES =

bin_PROGRAMS += ipcd
ipcd_SOURCES  = src/ipc/ipcd.c
