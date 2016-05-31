#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([ipc], [0.0.1], [https://github.com/agrare/ipc/issues], [ipc], [http://github.com/agrare/ipc])

AC_CONFIG_SRCDIR([src/ipc/ipcd.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([build])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([subdir-objects -Wall -Werror])

# Checks for programs.
AC_PROG_CC
AM_PROG_AR
AM_PROG_CC_C_O

# Checks for libraries.
LT_INIT
AC_CHECK_LIB([libpthread], [pthread_create])
AC_CHECK_LIB([systemd], [sd_listen_fds])

# Checks for header files.
AC_CHECK_HEADER([systemd/sd-daemon.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
