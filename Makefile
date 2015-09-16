.PHONY: all clean install depend
.SUFFIXES: .cxx

# works for Lua 5.2 on Debian based Linuxes:
DLL_INSTALL_DIR = /usr/lib/lua/5.2
LUA_INCDIR = /usr/include/lua5.2
FLTK_CONFIG = fltk-config

CXX = g++
CFLAGS = -Wall -Wextra -fpic -O2
MYCFLAGS = ${CFLAGS} -I${LUA_INCDIR} -Imoon -Icompat-5.3/c-api \
           -DMOON_PREFIX=f4lx -DCOMPAT53_PREFIX=f4lx -DNDEBUG \
           `${FLTK_CONFIG} --cxxflags`
MYLDFLAGS = `${FLTK_CONFIG} --ldflags`
LIBFLAG = -shared
LIB_EXTENSION = so

DLLBASENAME = fltk4lua
SOURCES = src/fltk4lua.cxx src/f4l_widget.cxx src/f4l_group.cxx \
          src/f4l_enums.cxx src/f4l_box.cxx src/f4l_window.cxx
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

depend:
	rm -f dependencies.txt
	for f in ${SOURCES} moon/moon.c compat-5.3/c-api/compat-5.3.c; do \
	  obj=`echo "$$f" | sed 's/\.[^.]\+$$/.o/'`; \
	  gcc ${MYCFLAGS} -MM -MT "$$obj" "$$f" >> dependencies.txt; \
	done

clean:
	rm -f ${DLLBASENAME}.${LIB_EXTENSION} ${OBJECTS} dependencies.txt


# dependencies
src/fltk4lua.o: src/fltk4lua.cxx src/fltk4lua.hxx moon/moon.h \
 compat-5.3/c-api/compat-5.3.h
src/f4l_widget.o: src/f4l_widget.cxx src/fltk4lua.hxx moon/moon.h \
 compat-5.3/c-api/compat-5.3.h src/f4l_widget.hxx src/f4l_enums.hxx
src/f4l_group.o: src/f4l_group.cxx src/fltk4lua.hxx moon/moon.h \
 compat-5.3/c-api/compat-5.3.h src/f4l_group.hxx src/f4l_widget.hxx
src/f4l_enums.o: src/f4l_enums.cxx src/fltk4lua.hxx moon/moon.h \
 compat-5.3/c-api/compat-5.3.h src/f4l_enums.hxx moon/moon_flag.h
src/f4l_box.o: src/f4l_box.cxx src/fltk4lua.hxx moon/moon.h \
 compat-5.3/c-api/compat-5.3.h src/f4l_widget.hxx
src/f4l_window.o: src/f4l_window.cxx src/fltk4lua.hxx moon/moon.h \
 compat-5.3/c-api/compat-5.3.h src/f4l_window.hxx src/f4l_group.hxx \
 src/f4l_widget.hxx src/f4l_enums.hxx
moon/moon.o: moon/moon.c moon/moon.h
compat-5.3/c-api/compat-5.3.o: compat-5.3/c-api/compat-5.3.c \
 compat-5.3/c-api/compat-5.3.h

