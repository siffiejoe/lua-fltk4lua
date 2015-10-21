#ifndef F4L_WINDOW_HXX_
#define F4L_WINDOW_HXX_

#include "fltk4lua.hxx"
#include "f4l_widget.hxx"
#include <FL/Fl_Window.H>

/* Windows have an additional constructor signature */
template< typename T >
MOON_LOCAL T* f4l_new_window( lua_State* L, char const* tname,
                              moon_object_destructor destructor ) {
  int top = lua_gettop( L );
  int has_properties = 0;
  int has_x_y = 1;
  if( top == 2 && lua_istable( L, 2 ) ) {
    has_properties = 1;
    if( lua_rawgeti( L, 2, 4 ) == LUA_TNIL ) {
      has_x_y = 0;
      lua_pop( L, 1 );
      lua_replace( L, 1 );
      for( int i = 1; i <= 3; ++i )
        lua_rawgeti( L, 1, i );
    } else
      lua_pop( L, 1 );
  } else
    has_x_y = top >= 5;
  if( !has_x_y ) {
    lua_settop( L, 4 );
    lua_rotate( L, 1, -1 );
    int w = moon_checkint( L, 1, 0, INT_MAX );
    int h = moon_checkint( L, 2, 0, INT_MAX );
    char const* label = luaL_optstring( L, 3, NULL );
    void** p = moon_newpointer( L, tname, destructor );
    lua_newtable( L );
    if( label != NULL ) {
      lua_pushvalue( L, 3 );
      lua_setfield( L, -2, "label" );
    }
    lua_setuservalue( L, -2 );
    T* window = new T( w, h, label );
    *p = static_cast< void* >( window );
    f4l_register_widget( L, window );
    if( has_properties )
      f4l_add_properties( L, 5, 4 );
    return window;
  } else /* use the normal 4/5 argument Fl_Widget constructor */
    return f4l_new_widget< T >( L, tname, destructor );
}


/* (Meta-)methods for Fl_Windows: */
MOON_LOCAL int f4l_window_index_( lua_State* L, Fl_Window* w,
                                  char const* key, size_t n );
MOON_LOCAL int f4l_window_newindex_( lua_State* L, Fl_Window* w,
                                     char const* key, size_t n );

F4L_LUA_LLINKAGE_BEGIN
MOON_LOCAL int f4l_window_clear_border( lua_State* L );
MOON_LOCAL int f4l_window_cursor( lua_State* L );
MOON_LOCAL int f4l_window_default_cursor( lua_State* L );
MOON_LOCAL int f4l_window_free_position( lua_State* L );
MOON_LOCAL int f4l_window_fullscreen( lua_State* L );
MOON_LOCAL int f4l_window_fullscreen_off( lua_State* L );
MOON_LOCAL int f4l_window_iconize( lua_State* L );
MOON_LOCAL int f4l_window_make_current( lua_State* L );
MOON_LOCAL int f4l_window_set_modal( lua_State* L );
MOON_LOCAL int f4l_window_set_non_modal( lua_State* L );
MOON_LOCAL int f4l_window_set_override( lua_State* L );
MOON_LOCAL int f4l_window_show( lua_State* L );
MOON_LOCAL int f4l_window_size_range( lua_State* L );
F4L_LUA_LLINKAGE_END


#define F4L_WINDOW_METHODS \
  { "clear_border", f4l_window_clear_border }, \
  { "cursor", f4l_window_cursor }, \
  { "default_cursor", f4l_window_default_cursor }, \
  { "fullscreen", f4l_window_fullscreen }, \
  { "fullscreen_off", f4l_window_fullscreen_off }, \
  { "iconize", f4l_window_iconize }, \
  { "make_current", f4l_window_make_current }, \
  { "set_modal", f4l_window_set_modal }, \
  { "set_non_modal", f4l_window_set_non_modal }, \
  { "set_override", f4l_window_set_override }, \
  { "show", f4l_window_show }, \
  { "size_range", f4l_window_size_range }


#endif /* F4L_WINDOW_HXX_ */

