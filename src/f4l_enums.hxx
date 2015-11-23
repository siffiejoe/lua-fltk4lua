#ifndef F4L_ENUMS_HXX_
#define F4L_ENUMS_HXX_

#include "fltk4lua.hxx"
#include <FL/Enumerations.H>

/* common macros for creating code from an enum definition list */
#define F4L_GEN_NAME( _a, _b )  "FL_" _a,
#define F4L_GEN_RNAME( _a, _b ) _a,
#define F4L_GEN_VALUE( _a, _b ) _b,
#define F4L_GEN_CASE( _a, _b )  \
  case _b: lua_pushliteral( L, "FL_" _a ); break;
#define F4L_GEN_RCASE( _a, _b ) \
  case _b: lua_pushliteral( L, _a ); break;

/* The Fl_Widget::type() range is categorized according to the
 * Widget that uses the values. */
#define F4L_GEN_TYPE_ENUM( _list, _suffix ) \
  MOON_LOCAL int f4l_check_type_ ## _suffix( lua_State* L, int idx ) { \
    static char const* const names[] = { \
      _list( F4L_GEN_RNAME ) \
      NULL \
    }; \
    static int const values[] = { \
      _list( F4L_GEN_VALUE ) \
      0 \
    }; \
    return values[ luaL_checkoption( L, idx, NULL, names ) ]; \
  } \
  MOON_LOCAL void f4l_push_type_ ## _suffix( lua_State* L, int v ) { \
    switch( v ) { \
      _list( F4L_GEN_RCASE ) \
      default: \
        luaL_error( L, "unknown " #_suffix " type" ); \
    } \
  }


MOON_LOCAL Fl_Shortcut f4l_check_shortcut( lua_State* L, int idx );
MOON_LOCAL void f4l_push_shortcut( lua_State* L, Fl_Shortcut s );

MOON_LOCAL Fl_Damage f4l_check_damage( lua_State* L, int idx );
MOON_LOCAL void f4l_push_damage( lua_State* L, Fl_Damage d );

MOON_LOCAL Fl_Event f4l_check_event( lua_State* L, int idx );
MOON_LOCAL void f4l_push_event( lua_State* L, Fl_Event e );

MOON_LOCAL Fl_Labeltype f4l_check_labeltype( lua_State* L, int idx );
MOON_LOCAL void f4l_push_labeltype( lua_State* L, Fl_Labeltype t );

MOON_LOCAL Fl_Mode f4l_check_mode( lua_State* L, int idx );
MOON_LOCAL void f4l_push_mode( lua_State* L, Fl_Mode m );

MOON_LOCAL Fl_When f4l_check_when( lua_State* L, int idx );
MOON_LOCAL void f4l_push_when( lua_State* L, Fl_When w );

MOON_LOCAL int f4l_check_fd_when( lua_State* L, int idx );

MOON_LOCAL Fl_Cursor f4l_check_cursor( lua_State* L, int idx );
MOON_LOCAL void f4l_push_cursor( lua_State* L, Fl_Cursor c );

MOON_LOCAL Fl_Boxtype f4l_check_boxtype( lua_State* L, int idx );
MOON_LOCAL void f4l_push_boxtype( lua_State* L, Fl_Boxtype b );

MOON_LOCAL Fl_Align f4l_check_align( lua_State* L, int idx );
MOON_LOCAL void f4l_push_align( lua_State* L, Fl_Align a );

MOON_LOCAL Fl_Font f4l_check_font( lua_State* L, int idx );
MOON_LOCAL void f4l_push_font( lua_State* L, Fl_Font f );

MOON_LOCAL Fl_Color f4l_check_color( lua_State* L, int idx );
MOON_LOCAL void f4l_push_color( lua_State* L, Fl_Color c );

MOON_LOCAL Fl::Fl_Option f4l_check_option( lua_State* L, int idx );

MOON_LOCAL void f4l_enums_setup( lua_State* L );


#endif /* F4L_ENUMS_HXX_ */

