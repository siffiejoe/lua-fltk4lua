#ifndef F4L_ENUMS_HXX_
#define F4L_ENUMS_HXX_

#include "fltk4lua.hxx"
#include <FL/Enumerations.H>

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

MOON_LOCAL void f4l_enums_setup( lua_State* L );


#endif /* F4L_ENUMS_HXX_ */

