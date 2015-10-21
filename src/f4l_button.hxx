#ifndef F4L_BUTTON_HXX_
#define F4L_BUTTON_HXX_

#include "fltk4lua.hxx"
#include <FL/Fl_Button.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Repeat_Button.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Round_Button.H>


/* (Meta-)methods for Fl_Buttons: */
MOON_LOCAL int f4l_button_index_( lua_State* L, Fl_Button* b,
                                  char const* key, size_t n );
MOON_LOCAL int f4l_button_newindex_( lua_State* L, Fl_Button* b,
                                     char const* key, size_t n );

F4L_LUA_LLINKAGE_BEGIN
MOON_LOCAL int f4l_button_clear( lua_State* L );
MOON_LOCAL int f4l_button_set( lua_State* L );
MOON_LOCAL int f4l_button_setonly( lua_State* L );
F4L_LUA_LLINKAGE_END


#define F4L_BUTTON_METHODS \
  { "clear", f4l_button_clear }, \
  { "set", f4l_button_set }, \
  { "setonly", f4l_button_setonly }


#endif /* F4L_BUTTON_HXX_ */

