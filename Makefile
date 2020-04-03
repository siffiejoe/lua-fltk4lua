.PHONY: all clean install depend static dynamic
.SUFFIXES: .cxx

# works for Lua 5.2 on Debian based Linuxes:
DLL_INSTALL_DIR = /usr/lib/lua/5.2
LUA_INCDIR = /usr/include/lua5.2
FLTK_CONFIG = fltk-config
AR = ar
RANLIB = ranlib
CC = gcc
CFLAGS = -Wall -Wextra -fpic -Os
MYCFLAGS = ${CFLAGS} -I${LUA_INCDIR} -Imoon -Icompat-5.3/c-api \
           -DMOON_PREFIX=f4lx -DCOMPAT53_PREFIX=f4lx -DNDEBUG \
           `${FLTK_CONFIG} --use-images --cxxflags`
MYLDFLAGS = `${FLTK_CONFIG} --use-images --ldflags` -lstdc++
LIBFLAG = -shared
LIB_EXTENSION = so
STATICLIB_PREFIX = lib
STATICLIB_EXTENSION = a

DLLBASENAME = fltk4lua
SOURCES = \
 src/fltk4lua.cxx \
 src/f4l_enums.cxx \
 src/f4l_ask.cxx \
 src/f4l_image.cxx \
 src/f4l_shared_image.cxx \
 src/f4l_widget.cxx \
 src/f4l_box.cxx \
 src/f4l_button.cxx \
 src/f4l_chart.cxx \
 src/f4l_clock.cxx \
 src/f4l_group.cxx \
 src/f4l_browserx.cxx \
 src/f4l_browser.cxx \
 src/f4l_file_browser.cxx \
 src/f4l_check_browser.cxx \
 src/f4l_input_choice.cxx \
 src/f4l_color_chooser.cxx \
 src/f4l_pack.cxx \
 src/f4l_scroll.cxx \
 src/f4l_spinner.cxx \
 src/f4l_tabs.cxx \
 src/f4l_tile.cxx \
 src/f4l_window.cxx \
 src/f4l_wizard.cxx \
 src/f4l_input.cxx \
 src/f4l_menu.cxx \
 src/f4l_choice.cxx \
 src/f4l_menu_bar.cxx \
 src/f4l_menu_button.cxx \
 src/f4l_progress.cxx \
 src/f4l_valuator.cxx \
 src/f4l_adjuster.cxx \
 src/f4l_counter.cxx \
 src/f4l_dial.cxx \
 src/f4l_roller.cxx \
 src/f4l_slider.cxx \
 src/f4l_value_input.cxx \
 src/f4l_value_output.cxx
OBJECTS = ${SOURCES:%.cxx=%.o} moon/moon.o compat-5.3/c-api/compat-5.3.o

all: dynamic

static: ${STATICLIB_PREFIX}${DLLBASENAME}.${STATICLIB_EXTENSION}

dynamic: ${DLLBASENAME}.${LIB_EXTENSION}

${STATICLIB_PREFIX}${DLLBASENAME}.${STATICLIB_EXTENSION}: ${OBJECTS}
	${AR} rc ${STATICLIB_PREFIX}${DLLBASENAME}.${STATICLIB_EXTENSION} ${OBJECTS}
	${RANLIB} ${STATICLIB_PREFIX}${DLLBASENAME}.${STATICLIB_EXTENSION}

${DLLBASENAME}.${LIB_EXTENSION}: ${OBJECTS}
	${CC} ${MYCFLAGS} ${LIBFLAG} -o $@ ${OBJECTS} ${MYLDFLAGS}

.c.o:
	${CC} ${MYCFLAGS} -c -o $@ $<

.cxx.o:
	${CC} ${MYCFLAGS} -c -o $@ $<

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
	rm -f ${DLLBASENAME}.${LIB_EXTENSION} ${STATICLIB_PREFIX}${DLLBASENAME}.${STATICLIB_EXTENSION} ${OBJECTS} dependencies.txt


# dependencies
src/fltk4lua.o: src/fltk4lua.cxx src/fltk4lua.hxx \
 moon/moon.h compat-5.3/c-api/compat-5.3.h src/f4l_enums.hxx
src/f4l_enums.o: src/f4l_enums.cxx src/fltk4lua.hxx \
 compat-5.3/c-api/compat-5.3.h src/f4l_enums.hxx moon/moon_flag.h \
 moon/moon.h
src/f4l_ask.o: src/f4l_ask.cxx src/fltk4lua.hxx moon/moon.h \
 compat-5.3/c-api/compat-5.3.h src/f4l_enums.hxx
src/f4l_image.o: src/f4l_image.cxx src/fltk4lua.hxx moon/moon.h \
 compat-5.3/c-api/compat-5.3.h src/f4l_image.hxx src/f4l_enums.hxx
src/f4l_shared_image.o: src/f4l_shared_image.cxx src/fltk4lua.hxx \
 moon/moon.h compat-5.3/c-api/compat-5.3.h src/f4l_image.hxx
src/f4l_widget.o: src/f4l_widget.cxx src/fltk4lua.hxx moon/moon.h \
 compat-5.3/c-api/compat-5.3.h src/f4l_widget.hxx src/f4l_enums.hxx
src/f4l_box.o: src/f4l_box.cxx src/fltk4lua.hxx moon/moon.h \
 compat-5.3/c-api/compat-5.3.h src/f4l_widget.hxx
src/f4l_button.o: src/f4l_button.cxx src/fltk4lua.hxx moon/moon.h \
 compat-5.3/c-api/compat-5.3.h src/f4l_button.hxx src/f4l_widget.hxx \
 src/f4l_enums.hxx
src/f4l_chart.o: src/f4l_chart.cxx src/fltk4lua.hxx moon/moon.h \
 compat-5.3/c-api/compat-5.3.h src/f4l_widget.hxx src/f4l_enums.hxx
src/f4l_clock.o: src/f4l_clock.cxx src/fltk4lua.hxx moon/moon.h \
 compat-5.3/c-api/compat-5.3.h src/f4l_widget.hxx src/f4l_enums.hxx
src/f4l_group.o: src/f4l_group.cxx src/fltk4lua.hxx moon/moon.h \
 compat-5.3/c-api/compat-5.3.h src/f4l_group.hxx src/f4l_widget.hxx
src/f4l_browserx.o: src/f4l_browserx.cxx src/fltk4lua.hxx moon/moon.h \
 compat-5.3/c-api/compat-5.3.h src/f4l_browserx.hxx src/f4l_enums.hxx
src/f4l_browser.o: src/f4l_browser.cxx src/fltk4lua.hxx moon/moon.h \
 compat-5.3/c-api/compat-5.3.h src/f4l_browser.hxx src/f4l_browserx.hxx \
 src/f4l_widget.hxx src/f4l_enums.hxx
src/f4l_file_browser.o: src/f4l_file_browser.cxx src/fltk4lua.hxx \
 moon/moon.h compat-5.3/c-api/compat-5.3.h src/f4l_browser.hxx \
  src/f4l_browserx.hxx src/f4l_widget.hxx src/f4l_enums.hxx
src/f4l_check_browser.o: src/f4l_check_browser.cxx src/fltk4lua.hxx \
 moon/moon.h compat-5.3/c-api/compat-5.3.h src/f4l_browserx.hxx \
 src/f4l_widget.hxx
src/f4l_input_choice.o: src/f4l_input_choice.cxx src/fltk4lua.hxx \
 moon/moon.h compat-5.3/c-api/compat-5.3.h src/f4l_menu.hxx \
 src/f4l_widget.hxx src/f4l_enums.hxx
src/f4l_color_chooser.o: src/f4l_color_chooser.cxx src/fltk4lua.hxx \
 moon/moon.h compat-5.3/c-api/compat-5.3.h src/f4l_widget.hxx
src/f4l_pack.o: src/f4l_pack.cxx src/fltk4lua.hxx moon/moon.h \
 compat-5.3/c-api/compat-5.3.h src/f4l_group.hxx src/f4l_widget.hxx \
 src/f4l_enums.hxx
src/f4l_scroll.o: src/f4l_scroll.cxx src/fltk4lua.hxx moon/moon.h \
 compat-5.3/c-api/compat-5.3.h src/f4l_group.hxx src/f4l_widget.hxx \
 src/f4l_enums.hxx
src/f4l_spinner.o: src/f4l_spinner.cxx src/fltk4lua.hxx moon/moon.h \
 compat-5.3/c-api/compat-5.3.h src/f4l_widget.hxx src/f4l_enums.hxx
src/f4l_tabs.o: src/f4l_tabs.cxx src/fltk4lua.hxx moon/moon.h \
 compat-5.3/c-api/compat-5.3.h src/f4l_group.hxx src/f4l_widget.hxx
src/f4l_tile.o: src/f4l_tile.cxx src/fltk4lua.hxx moon/moon.h \
 compat-5.3/c-api/compat-5.3.h src/f4l_group.hxx src/f4l_widget.hxx
src/f4l_window.o: src/f4l_window.cxx src/fltk4lua.hxx moon/moon.h \
 compat-5.3/c-api/compat-5.3.h src/f4l_window.hxx src/f4l_widget.hxx \
 src/f4l_group.hxx src/f4l_enums.hxx
src/f4l_wizard.o: src/f4l_wizard.cxx src/fltk4lua.hxx moon/moon.h \
 compat-5.3/c-api/compat-5.3.h src/f4l_group.hxx src/f4l_widget.hxx
src/f4l_input.o: src/f4l_input.cxx src/fltk4lua.hxx moon/moon.h \
 compat-5.3/c-api/compat-5.3.h src/f4l_input.hxx src/f4l_widget.hxx \
 src/f4l_enums.hxx
src/f4l_menu.o: src/f4l_menu.cxx src/fltk4lua.hxx moon/moon.h \
 compat-5.3/c-api/compat-5.3.h src/f4l_menu.hxx src/f4l_widget.hxx \
 src/f4l_enums.hxx moon/moon_flag.h
src/f4l_choice.o: src/f4l_choice.cxx src/fltk4lua.hxx moon/moon.h \
 compat-5.3/c-api/compat-5.3.h src/f4l_menu.hxx src/f4l_widget.hxx
src/f4l_menu_bar.o: src/f4l_menu_bar.cxx src/fltk4lua.hxx moon/moon.h \
 compat-5.3/c-api/compat-5.3.h src/f4l_menu.hxx src/f4l_widget.hxx
src/f4l_menu_button.o: src/f4l_menu_button.cxx src/fltk4lua.hxx \
 moon/moon.h compat-5.3/c-api/compat-5.3.h src/f4l_menu.hxx \
 src/f4l_widget.hxx src/f4l_enums.hxx
src/f4l_progress.o: src/f4l_progress.cxx src/fltk4lua.hxx moon/moon.h \
 compat-5.3/c-api/compat-5.3.h src/f4l_widget.hxx
src/f4l_valuator.o: src/f4l_valuator.cxx src/fltk4lua.hxx moon/moon.h \
 compat-5.3/c-api/compat-5.3.h src/f4l_valuator.hxx src/f4l_widget.hxx \
 src/f4l_enums.hxx
src/f4l_adjuster.o: src/f4l_adjuster.cxx src/fltk4lua.hxx moon/moon.h \
 compat-5.3/c-api/compat-5.3.h src/f4l_valuator.hxx src/f4l_widget.hxx
src/f4l_counter.o: src/f4l_counter.cxx src/fltk4lua.hxx moon/moon.h \
 compat-5.3/c-api/compat-5.3.h src/f4l_valuator.hxx src/f4l_widget.hxx \
 src/f4l_enums.hxx
src/f4l_dial.o: src/f4l_dial.cxx src/fltk4lua.hxx moon/moon.h \
 compat-5.3/c-api/compat-5.3.h src/f4l_valuator.hxx src/f4l_widget.hxx \
 src/f4l_enums.hxx
src/f4l_roller.o: src/f4l_roller.cxx src/fltk4lua.hxx moon/moon.h \
 compat-5.3/c-api/compat-5.3.h src/f4l_valuator.hxx src/f4l_widget.hxx
src/f4l_slider.o: src/f4l_slider.cxx src/fltk4lua.hxx moon/moon.h \
 compat-5.3/c-api/compat-5.3.h src/f4l_slider.hxx src/f4l_valuator.hxx \
 src/f4l_widget.hxx src/f4l_enums.hxx
src/f4l_value_input.o: src/f4l_value_input.cxx src/fltk4lua.hxx \
 moon/moon.h compat-5.3/c-api/compat-5.3.h src/f4l_valuator.hxx \
 src/f4l_widget.hxx src/f4l_enums.hxx
src/f4l_value_output.o: src/f4l_value_output.cxx src/fltk4lua.hxx \
 moon/moon.h compat-5.3/c-api/compat-5.3.h src/f4l_valuator.hxx \
 src/f4l_widget.hxx src/f4l_enums.hxx
moon/moon.o: moon/moon.c moon/moon.h
compat-5.3/c-api/compat-5.3.o: compat-5.3/c-api/compat-5.3.c \
 compat-5.3/c-api/compat-5.3.h

