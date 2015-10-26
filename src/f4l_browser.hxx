#ifndef F4L_BROWSER_H_
#define F4L_BROWSER_H_

#include "fltk4lua.hxx"
#include <FL/Fl_Browser.H>

/* (Meta-)methods for Fl_Browser widgets: */
MOON_LOCAL int f4l_browser_index_( lua_State* L, Fl_Browser* b,
                                   char const* key, size_t n );
MOON_LOCAL int f4l_browser_newindex_( lua_State* L, Fl_Browser* b,
                                      char const* key, size_t n );

F4L_LUA_LLINKAGE_BEGIN
MOON_LOCAL int f4l_browser_add( lua_State* L );
MOON_LOCAL int f4l_browser_clear( lua_State* L );
MOON_LOCAL int f4l_browser_displayed( lua_State* L );
MOON_LOCAL int f4l_browser_hide( lua_State* L );
MOON_LOCAL int f4l_browser_insert( lua_State* L );
MOON_LOCAL int f4l_browser_load( lua_State* L );
MOON_LOCAL int f4l_browser_make_visible( lua_State* L );
MOON_LOCAL int f4l_browser_move( lua_State* L );
MOON_LOCAL int f4l_browser_remove( lua_State* L );
MOON_LOCAL int f4l_browser_select( lua_State* L );
MOON_LOCAL int f4l_browser_selected( lua_State* L );
MOON_LOCAL int f4l_browser_show( lua_State* L );
MOON_LOCAL int f4l_browser_size( lua_State* L );
MOON_LOCAL int f4l_browser_swap( lua_State* L );
MOON_LOCAL int f4l_browser_text( lua_State* L );
MOON_LOCAL int f4l_browser_line_visible( lua_State* L );
F4L_LUA_LLINKAGE_END


#define F4L_BROWSER_METHODS \
  { "add", f4l_browser_add }, \
  { "clear", f4l_browser_clear }, \
  { "displayed", f4l_browser_displayed }, \
  { "hide", f4l_browser_hide }, \
  { "insert", f4l_browser_insert }, \
  { "load", f4l_browser_load }, \
  { "make_visible", f4l_browser_make_visible }, \
  { "move", f4l_browser_move }, \
  { "remove", f4l_browser_remove }, \
  { "select", f4l_browser_select }, \
  { "selected", f4l_browser_selected }, \
  { "show", f4l_browser_show }, \
  { "size", f4l_browser_size }, \
  { "swap", f4l_browser_swap }, \
  { "text", f4l_browser_text }, \
  { "line_visible", f4l_browser_line_visible }


#endif /* F4L_BROWSER_H_ */

