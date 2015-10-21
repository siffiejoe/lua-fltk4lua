#ifndef F4L_INPUT_HXX_
#define F4L_INPUT_HXX_

#include "fltk4lua.hxx"
#include <FL/Fl_Input_.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_File_Input.H>


/* (Meta-)methods for Fl_Inputs: */
MOON_LOCAL int f4l_input_index_( lua_State* L, Fl_Input* g,
                                 char const* key, size_t n );
MOON_LOCAL int f4l_input_newindex_( lua_State* L, Fl_Input* g,
                                    char const* key, size_t n );

F4L_LUA_LLINKAGE_BEGIN
MOON_LOCAL int f4l_input_copy( lua_State* L );
MOON_LOCAL int f4l_input_copy_cuts( lua_State* L );
MOON_LOCAL int f4l_input_cut( lua_State* L );
MOON_LOCAL int f4l_input_idx( lua_State* L );
MOON_LOCAL int f4l_input_insert( lua_State* L );
MOON_LOCAL int f4l_input_replace( lua_State* L );
MOON_LOCAL int f4l_input_size( lua_State* L );
MOON_LOCAL int f4l_input_undo( lua_State* L );
F4L_LUA_LLINKAGE_END


#define F4L_INPUT_METHODS \
  { "copy", f4l_input_copy }, \
  { "copy_cuts", f4l_input_copy_cuts }, \
  { "cut", f4l_input_cut }, \
  { "index", f4l_input_idx }, \
  { "insert", f4l_input_insert }, \
  { "replace", f4l_input_replace }, \
  { "size", f4l_input_size }, \
  { "undo", f4l_input_undo }


#endif /* F4L_INPUT_HXX_ */

