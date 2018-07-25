include_HEADERS = func.h
lib_LTLIBRARIES = libmymath.la
libmymath_la_SOURCES = func.cpp
# header path:
libmymath_la_CPPFLAGS = -I $(top_srcdir)/my_1st_libs
# linking against other libraries:
libmymath_la_LIBADD = $(top_srcdir)/my_1st_libs/libchecker.la

# my type:
libmymath_la_LDFLAGS = -shared
