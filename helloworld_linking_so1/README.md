executable file linking against shared library.

# `_LTLIBRARIES` primary

> 注意:
>
> configure.ac里: AC_CONFIG_MACRO_DIRS([m4])
>
> Makefile.am里: ACLOCAL_AMFLAGS = -I m4
>
> 两者要确保**同步**一起出现.


# autoconf

- `AC_CONFIG_MACRO_DIRS` : AC_CONFIG_MACRO_DIRS([m4])
- NOT use `AC_PROG_RANLIB` when building libtool libraries.

# automake

- `ACLOCAL_AMFLAGS = -I dir` : ACLOCAL_AMFLAGS = -I m4
- `xxx_la_LDFLAGS` : 参考libtool的Link mode
- `-rpath`: 例如 `libfoo_la_LDFLAGS = -rpath '$(libdir)'`


# libtool

## libtool 概念

- libtool objects: *.lo
- libtool libraries: *.la

Link mode:

- `-static`
- `-shared`
- `-module`
