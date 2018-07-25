# ACLOCAL_AMFLAGS = -I m4

include_HEADERS = func.h
lib_LTLIBRARIES = libmymath.la
# noinst_LTLIBRARIES = libmymath.la

libmymath_la_SOURCES = func.cpp

# see libtool LINK mode: -static, -shared, -module, etc
libmymath_la_LDFLAGS = -shared
libmymath_la_LDFLAGS += -version-info 2:15:0
