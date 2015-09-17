#include "fltk4lua.hxx"
#include "f4l_slider.hxx"
#include "f4l_valuator.hxx"
#include "f4l_widget.hxx"
#include "f4l_enums.hxx"
#include <cstring>
#include <climits>

namespace {

  inline Fl_Slider* check_slider( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_SLIDER_NAME );
    return static_cast< Fl_Slider* >( p );
  }

  int slider_index( lua_State* L ) {
    Fl_Slider* s = check_slider( L, 1 );
    size_t n = 0;
    char const* key = luaL_checklstring( L, 2, &n );
    F4L_TRY {
      if( !f4l_slider_index_( L, s, key, n ) &&
          !f4l_valuator_index_( L, s, key, n ) &&
          !f4l_widget_index_( L, s, key, n ) )
        lua_pushnil( L );
    } F4L_CATCH( L );
    return 1;
  }

  int slider_newindex( lua_State* L ) {
    Fl_Slider* s = check_slider( L, 1 );
    size_t n = 0;
    char const* key = luaL_checklstring( L, 2, &n );
    F4L_TRY {
      (void)(f4l_slider_newindex_( L, s, key, n ) ||
             f4l_valuator_newindex_( L, s, key, n ) ||
             f4l_widget_newindex_( L, s, key, n ));
    } F4L_CATCH( L );
    return 0;
  }

  int new_slider( lua_State* L ) {
    F4L_TRY {
      f4l_new_widget< Fl_Slider >( L, F4L_SLIDER_NAME );
    } F4L_CATCH( L );
    return 1;
  }

} // anonymous namespace


MOON_LOCAL int f4l_slider_index_( lua_State* L, Fl_Slider* s,
                                  char const* key, size_t n ) {
  switch( n ) {
    case 6:
      if( F4L_MEMCMP( key, "slider", 6 ) == 0 ) {
        f4l_push_boxtype( L, s->slider() );
        return 1;
      }
      break;
    case 11:
      if( F4L_MEMCMP( key, "slider_size", 11 ) == 0 ) {
        lua_pushnumber( L, s->slider_size() );
        return 1;
      }
      break;
  }
  return 0;
}

MOON_LOCAL int f4l_slider_newindex_( lua_State* L, Fl_Slider* s,
                                     char const* key, size_t n ) {
  switch( n ) {
    case 6:
      if( F4L_MEMCMP( key, "slider", 6 ) == 0 ) {
        s->slider( f4l_check_boxtype( L, 3 ) );
        return 1;
      }
      break;
    case 11:
      if( F4L_MEMCMP( key, "slider_size", 11 ) == 0 ) {
        s->slider_size( luaL_checknumber( L, 3 ) );
        return 1;
      }
      break;
  }
  return 0;
}


MOON_LOCAL int f4l_slider_bounds( lua_State* L ) {
  Fl_Slider* s = check_slider( L, 1 );
  double a = luaL_checknumber( L, 2 );
  double b = luaL_checknumber( L, 3 );
  F4L_TRY {
    s->bounds( a, b );
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_slider_scrollvalue( lua_State* L ) {
  Fl_Slider* s = check_slider( L, 1 );
  int p = moon_checkint( L, 2, 0, INT_MAX );
  int sz = moon_checkint( L, 3, 0, INT_MAX );
  int f = moon_checkint( L, 4, 0, INT_MAX );
  int t = moon_checkint( L, 5, 0, INT_MAX );
  F4L_TRY {
    lua_pushinteger( L, s->scrollvalue( p, sz, f, t ) );
  } F4L_CATCH( L );
  return 1;
}


MOON_LOCAL void f4l_slider_setup( lua_State* L ) {
  luaL_Reg const functions[] = {
    { "Slider", new_slider },
    { NULL, NULL }
  };
  luaL_Reg const methods[] = {
    F4L_WIDGET_METHODS,
    F4L_VALUATOR_METHODS,
    F4L_SLIDER_METHODS,
    { "__index", slider_index },
    { "__newindex", slider_newindex },
    { NULL, NULL }
  };
  moon_defobject( L, F4L_SLIDER_NAME, 0, methods, 0 );
  moon_defcast( L, F4L_SLIDER_NAME, F4L_VALUATOR_NAME,
                f4l_cast< Fl_Slider, Fl_Valuator > );
  moon_defcast( L, F4L_SLIDER_NAME, F4L_WIDGET_NAME,
                f4l_cast< Fl_Slider, Fl_Widget > );
  luaL_setfuncs( L, functions, 0 );
}

