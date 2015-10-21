#ifndef F4L_BROWSERX_H_
#define F4L_BROWSERX_H_

#include "fltk4lua.hxx"
#include <FL/Fl_Browser_.H>

/* (Meta-)methods for Fl_Browser_ widgets: */
MOON_LOCAL int f4l_browserx_index_( lua_State* L, Fl_Browser_* b,
                                    char const* key, size_t n );
MOON_LOCAL int f4l_browserx_newindex_( lua_State* L, Fl_Browser_* b,
                                       char const* key, size_t n );

F4L_LUA_LLINKAGE_BEGIN
MOON_LOCAL int f4l_browserx_deselect( lua_State* L );
MOON_LOCAL int f4l_browserx_scrollbar_left( lua_State* L );
MOON_LOCAL int f4l_browserx_scrollbar_right( lua_State* L );
MOON_LOCAL int f4l_browserx_sort( lua_State* L );
F4L_LUA_LLINKAGE_END


#define F4L_BROWSERX_METHODS \
  { "deselect", f4l_browserx_deselect }, \
  { "scrollbar_left", f4l_browserx_scrollbar_left }, \
  { "scrollbar_right", f4l_browserx_scrollbar_right }, \
  { "sort", f4l_browserx_sort }


#endif /* F4L_BROWSERX_H_ */

