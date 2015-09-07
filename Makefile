.PHONY: all clean install
.SUFFIXES: .cxx

# works for Lua 5.2 on Debian based Linuxes:
DLL_INSTALL_DIR = /usr/lib/lua/5.2
LUA_INCDIR = /usr/include/lua5.2
FLTK_CONFIG = fltk-config

CXX = g++
CFLAGS = -Wall -Wextra -fpic -O2
MYCFLAGS = ${CFLAGS} -I${LUA_INCDIR} -Imoon -Icompat-5.3/c-api \
           -DMOON_PREFIX=f4l -DCOMPAT53_PREFIX=f4l -DNDEBUG \
           `${FLTK_CONFIG} --cxxflags`
MYLDFLAGS = `${FLTK_CONFIG} --ldflags`
LIBFLAG = -shared
LIB_EXTENSION = so

DLLBASENAME = fltk4lua
SOURCES = src/fltk4lua.cxx
OBJECTS = ${SOURCES:%.cxx=%.o} moon/moon.o compat-5.3/c-api/compat-5.3.o

all: ${DLLBASENAME}.${LIB_EXTENSION}

${DLLBASENAME}.${LIB_EXTENSION}: ${OBJECTS}
	${CXX} ${MYCFLAGS} ${LIBFLAG} -o $@ ${OBJECTS} ${MYLDFLAGS}

.c.o:
	${CXX} ${MYCFLAGS} -c -o $@ $<

.cxx.o:
	${CXX} ${MYCFLAGS} -c -o $@ $<

install: ${DLLBASENAME}.${LIB_EXTENSION}
	mkdir -p ${DLL_INSTALL_DIR}
	cp ${DLLBASENAME}.${LIB_EXTENSION} ${DLL_INSTALL_DIR}

clean:
	rm -f ${DLLBASENAME}.${LIB_EXTENSION} ${OBJECTS}

# dependencies
moon/moon.o: moon/moon.c moon/moon.h
compat-5.3/c-api/compat-5.3.o: compat-5.3/c-api/compat-5.3.c \
  compat-5.3/c-api/compat-5.3.h
src/fltk4lua.o: src/fltk4lua.cxx src/fltk4lua.hxx

