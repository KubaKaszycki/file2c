#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([File2C], [0.1], [kuba.kaszycki@gmail.com], [file2c])
AC_CONFIG_SRCDIR([src/genfile.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([gnits])

# Checks for programs.
AC_PROG_CC
gl_EARLY

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T

# Checks for library functions.
AC_FUNC_MALLOC

gl_INIT

gl_FUNC_SNPRINTF
gl_FUNC_GETLINE
gl_FUNC_OPEN
gl_FUNC_CLOSE
gl_FUNC_READ
gl_FUNC_WRITE
gl_FUNC_FFLUSH
gl_FUNC_FPURGE
gl_FUNC_FOPEN
gl_FUNC_FCLOSE
gl_STDLIB_H
gl_STDIO_H
gl_UNISTD_H
gl_HEADER_ERRNO_H

AC_CONFIG_FILES([Makefile
		 doc/Makefile
		 include/Makefile
		 gnulib/Makefile
		 man/Makefile
		 src/Makefile])
AC_OUTPUT
