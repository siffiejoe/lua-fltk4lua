#include "fltk4lua.hxx"
#include "f4l_valuator.hxx"
#include "f4l_widget.hxx"
#include <FL/Fl_Adjuster.H>

namespace {

  inline Fl_Adjuster* check_adjuster( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_ADJUSTER_NAME );
    return static_cast< Fl_Adjuster* >( p );
  }

  int adjuster_index_( lua_State* L, Fl_Adjuster* a,
                       char const* key, size_t n ) {
    switch( n ) {
      case 4:
        if( F4L_MEMCMP( key, "soft", 4 ) == 0 ) {
          lua_pushboolean( L, a->soft() );
          return 1;
        }
        break;
    }
    return 0;
  }

  int adjuster_newindex_( lua_State* L, Fl_Adjuster* a,
                          char const* key, size_t n ) {
    switch( n ) {
      case 4:
        if( F4L_MEMCMP( key, "soft", 4 ) == 0 ) {
          a->soft( lua_toboolean( L, 3 ) );
          return 1;
        }
        break;
    }
    return 0;
  }

  int adjuster_index( lua_State* L ) {
    Fl_Adjuster* a = check_adjuster( L, 1 );
    size_t n = 0;
    char const* key = luaL_checklstring( L, 2, &n );
    F4L_TRY {
      if( !adjuster_index_( L, a, key, n ) &&
          !f4l_valuator_index_( L, a, key, n ) &&
          !f4l_widget_index_( L, a, key, n ) )
        lua_pushnil( L );
    } F4L_CATCH( L );
    return 1;
  }

  int adjuster_newindex( lua_State* L ) {
    Fl_Adjuster* a = check_adjuster( L, 1 );
    size_t n = 0;
    char const* key = luaL_checklstring( L, 2, &n );
    F4L_TRY {
      (void)(adjuster_newindex_( L, a, key, n ) ||
             f4l_valuator_newindex_( L, a, key, n ) ||
             f4l_widget_newindex_( L, a, key, n ));
    } F4L_CATCH( L );
    return 0;
  }

  int new_adjuster( lua_State* L ) {
    F4L_TRY {
      f4l_new_widget< Fl_Adjuster >( L, F4L_ADJUSTER_NAME );
    } F4L_CATCH( L );
    return 1;
  }

} // anonymous namespace


MOON_LOCAL void f4l_adjuster_setup( lua_State* L ) {
  luaL_Reg const functions[] = {
    { "Adjuster", new_adjuster },
    { NULL, NULL }
  };
  luaL_Reg const methods[] = {
    F4L_WIDGET_METHODS,
    F4L_VALUATOR_METHODS,
    { "__index", adjuster_index },
    { "__newindex", adjuster_newindex },
    { NULL, NULL }
  };
  moon_defobject( L, F4L_ADJUSTER_NAME, 0, methods, 0 );
  moon_defcast( L, F4L_ADJUSTER_NAME, F4L_VALUATOR_NAME,
                f4l_cast< Fl_Adjuster, Fl_Valuator > );
  moon_defcast( L, F4L_ADJUSTER_NAME, F4L_WIDGET_NAME,
                f4l_cast< Fl_Adjuster, Fl_Widget > );
  luaL_setfuncs( L, functions, 0 );
}
