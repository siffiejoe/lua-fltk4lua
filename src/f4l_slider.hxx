#ifndef F4L_SLIDER_HXX_
#define F4L_SLIDER_HXX_

#include "fltk4lua.hxx"
#include <FL/Fl_Slider.H>
#include <FL/Fl_Scrollbar.H>
#include <FL/Fl_Value_Slider.H>


/* (Meta-)methods for Fl_Sliders: */
MOON_LOCAL int f4l_slider_index_( lua_State* L, Fl_Slider* s,
                                  char const* key, size_t n );
MOON_LOCAL int f4l_slider_newindex_( lua_State* L, Fl_Slider* s,
                                     char const* key, size_t n );

F4L_LUA_LLINKAGE_BEGIN
MOON_LOCAL int f4l_slider_bounds( lua_State* L );
MOON_LOCAL int f4l_slider_scrollvalue( lua_State* L );
F4L_LUA_LLINKAGE_END


#define F4L_SLIDER_METHODS \
  { "bounds", f4l_slider_bounds }, \
  { "scrollvalue", f4l_slider_scrollvalue }


#endif /* F4L_SLIDER_HXX_ */

