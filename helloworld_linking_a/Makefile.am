SUBDIRS = mylibs

# bin_PROGRAMS = hiworld
noinst_PROGRAMS = hiworld
hiworld_SOURCES = main.cpp
# header. (Put -I -D in _CPPFLAGS)
hiworld_CPPFLAGS = -Imylibs
# library:
# hiworld_LDFLAGS = -Lmylibs
# hiworld_LDADD = -lmymath
hiworld_LDADD = mylibs/libmymath.a
