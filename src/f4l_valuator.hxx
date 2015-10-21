#ifndef F4L_VALUATOR_HXX_
#define F4L_VALUATOR_HXX_

#include "fltk4lua.hxx"
#include <FL/Fl_Valuator.H>

MOON_LOCAL int f4l_check_type_valuator( lua_State* L, int idx );
MOON_LOCAL void f4l_push_type_valuator( lua_State* L, int v );

/* (Meta-)methods for Fl_Valuators: */
MOON_LOCAL int f4l_valuator_index_( lua_State* L, Fl_Valuator* v,
                                    char const* key, size_t n );
MOON_LOCAL int f4l_valuator_newindex_( lua_State* L, Fl_Valuator* v,
                                       char const* key, size_t n );

F4L_LUA_LLINKAGE_BEGIN
MOON_LOCAL int f4l_valuator_bounds( lua_State* L );
MOON_LOCAL int f4l_valuator_clamp( lua_State* L );
MOON_LOCAL int f4l_valuator_format( lua_State* L );
MOON_LOCAL int f4l_valuator_increment( lua_State* L );
MOON_LOCAL int f4l_valuator_range( lua_State* L );
MOON_LOCAL int f4l_valuator_round( lua_State* L );
F4L_LUA_LLINKAGE_END


#define F4L_VALUATOR_METHODS \
  { "bounds", f4l_valuator_bounds }, \
  { "clamp", f4l_valuator_clamp }, \
  { "format", f4l_valuator_format }, \
  { "increment", f4l_valuator_increment }, \
  { "range", f4l_valuator_range }, \
  { "round", f4l_valuator_round }


#endif /* F4L_VALUATOR_HXX_ */

