#ifndef F4L_WINDOW_HXX_
#define F4L_WINDOW_HXX_

#include "fltk4lua.hxx"
#include <FL/Fl_Window.H>


/* (Meta-)methods for Fl_Windows: */
MOON_LOCAL int f4l_window_index_( lua_State* L, Fl_Window* w,
                                  char const* key, size_t n );
MOON_LOCAL int f4l_window_newindex_( lua_State* L, Fl_Window* w,
                                     char const* key, size_t n );

MOON_LOCAL int f4l_window_clear_border( lua_State* L );
MOON_LOCAL int f4l_window_cursor( lua_State* L );
MOON_LOCAL int f4l_window_default_cursor( lua_State* L );
MOON_LOCAL int f4l_window_free_position( lua_State* L );
MOON_LOCAL int f4l_window_fullscreen( lua_State* L );
MOON_LOCAL int f4l_window_fullscreen_off( lua_State* L );
MOON_LOCAL int f4l_window_iconize( lua_State* L );
MOON_LOCAL int f4l_window_make_current( lua_State* L );
MOON_LOCAL int f4l_window_resize( lua_State* L );
MOON_LOCAL int f4l_window_set_modal( lua_State* L );
MOON_LOCAL int f4l_window_set_non_modal( lua_State* L );
MOON_LOCAL int f4l_window_set_override( lua_State* L );
MOON_LOCAL int f4l_window_show( lua_State* L );
MOON_LOCAL int f4l_window_size_range( lua_State* L );


#define F4L_WINDOW_METHODS \
  { "clear_border", f4l_window_clear_border }, \
  { "cursor", f4l_window_cursor }, \
  { "default_cursor", f4l_window_default_cursor }, \
  { "free_position", f4l_window_free_position }, \
  { "fullscreen", f4l_window_fullscreen }, \
  { "fullscreen_off", f4l_window_fullscreen_off }, \
  { "iconize", f4l_window_iconize }, \
  { "make_current", f4l_window_make_current }, \
  { "resize", f4l_window_resize }, \
  { "set_modal", f4l_window_set_modal }, \
  { "set_non_modal", f4l_window_set_non_modal }, \
  { "set_override", f4l_window_set_override }, \
  { "show", f4l_window_show }, \
  { "size_range", f4l_window_size_range }


#endif /* F4L_WINDOW_HXX_ */

