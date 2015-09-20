#include "fltk4lua.hxx"
#include "f4l_valuator.hxx"
#include "f4l_widget.hxx"
#include <FL/Fl_Roller.H>

namespace {

  inline Fl_Roller* check_roller( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_ROLLER_NAME );
    return static_cast< Fl_Roller* >( p );
  }

  int roller_index( lua_State* L ) {
    Fl_Roller* r = check_roller( L, 1 );
    size_t n = 0;
    char const* key = luaL_checklstring( L, 2, &n );
    F4L_TRY {
      if( !f4l_valuator_index_( L, r, key, n ) &&
          !f4l_widget_index_( L, r, key, n ) )
        lua_pushnil( L );
    } F4L_CATCH( L );
    return 1;
  }

  int roller_newindex( lua_State* L ) {
    Fl_Roller* r = check_roller( L, 1 );
    size_t n = 0;
    char const* key = luaL_checklstring( L, 2, &n );
    F4L_TRY {
      (void)(f4l_valuator_newindex_( L, r, key, n ) ||
             f4l_widget_newindex_( L, r, key, n ));
    } F4L_CATCH( L );
    return 0;
  }

  int new_roller( lua_State* L ) {
    F4L_TRY {
      f4l_new_widget< Fl_Roller>( L, F4L_ROLLER_NAME );
    } F4L_CATCH( L );
    return 1;
  }

} // anonymous namespace


MOON_LOCAL void f4l_roller_setup( lua_State* L ) {
  luaL_Reg const methods[] = {
    F4L_WIDGET_METHODS,
    F4L_VALUATOR_METHODS,
    { "__index", roller_index },
    { "__newindex", roller_newindex },
    { NULL, NULL }
  };
  moon_defobject( L, F4L_ROLLER_NAME, 0, methods, 0 );
  moon_defcast( L, F4L_ROLLER_NAME, F4L_VALUATOR_NAME,
                f4l_cast< Fl_Roller, Fl_Valuator > );
  moon_defcast( L, F4L_ROLLER_NAME, F4L_WIDGET_NAME,
                f4l_cast< Fl_Roller, Fl_Widget > );
  f4l_new_class( L, "Roller", new_roller );
}

