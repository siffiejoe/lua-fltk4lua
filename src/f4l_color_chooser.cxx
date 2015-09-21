#include "fltk4lua.hxx"
#include "f4l_group.hxx"
#include "f4l_widget.hxx"
#include <FL/Fl_Color_Chooser.H>
#include <cstring>

namespace {

  inline Fl_Color_Chooser* check_color_chooser( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_COLOR_CHOOSER_NAME );
    return static_cast< Fl_Color_Chooser* >( p );
  }

  int chooser_index_( lua_State* L, Fl_Color_Chooser* c,
                      char const* key, size_t n ) {
    using namespace std;
    switch( n ) {
      case 1:
        switch( *key ) {
          case 'r':
            lua_pushnumber( L, c->r() );
            return 1;
          case 'g':
            lua_pushnumber( L, c->g() );
            return 1;
          case 'b':
            lua_pushnumber( L, c->b() );
            return 1;
        }
        break;
      case 3:
        if( F4L_MEMCMP( key, "hue", 3 ) == 0 ) {
          lua_pushnumber( L, c->hue() );
          return 1;
        }
        break;
      case 4:
        if( F4L_MEMCMP( key, "mode", 4 ) == 0 ) {
          lua_pushinteger( L, c->mode() );
          return 1;
        }
        break;
      case 5:
        if( F4L_MEMCMP( key, "value", 5 ) == 0 ) {
          lua_pushnumber( L, c->value() );
          return 1;
        }
        break;
      case 10:
        if( F4L_MEMCMP( key, "saturation", 10 ) == 0 ) {
          lua_pushnumber( L, c->saturation() );
          return 1;
        }
        break;
    }
    return 0;
  }

  int chooser_newindex_( lua_State* L, Fl_Color_Chooser* c,
                         char const* key, size_t n ) {
    using namespace std;
    switch( n ) {
      case 4:
        if( F4L_MEMCMP( key, "mode", 4 ) == 0 ) {
          c->mode( moon_checkint( L, 3, 0, 3 ) );
          return 1;
        }
        break;
    }
    return 0;
  }

  int chooser_index( lua_State* L ) {
    Fl_Color_Chooser* c = check_color_chooser( L, 1 );
    size_t n = 0;
    char const* key = luaL_checklstring( L, 2, &n );
    F4L_TRY {
      if( !chooser_index_( L, c, key, n ) &&
          !f4l_group_index_( L, c, key, n ) &&
          !f4l_widget_index_( L, c, key, n ) )
        lua_pushnil( L );
    } F4L_CATCH( L );
    return 1;
  }

  int chooser_newindex( lua_State* L ) {
    Fl_Color_Chooser* c = check_color_chooser( L, 1 );
    size_t n = 0;
    char const* key = luaL_checklstring( L, 2, &n );
    F4L_TRY {
      (void)(chooser_newindex_( L, c, key, n ) ||
             f4l_group_newindex_( L, c, key, n ) ||
             f4l_widget_newindex_( L, c, key, n ));
    } F4L_CATCH( L );
    return 0;
  }

  int new_color_chooser( lua_State* L ) {
    F4L_TRY {
      f4l_new_widget< Fl_Color_Chooser >( L, F4L_COLOR_CHOOSER_NAME );
    } F4L_CATCH( L );
    return 1;
  }

  int chooser_rgb( lua_State* L ) {
    Fl_Color_Chooser* c = check_color_chooser( L, 1 );
    double r = luaL_checknumber( L, 2 );
    double g = luaL_checknumber( L, 3 );
    double b = luaL_checknumber( L, 4 );
    F4L_TRY {
      lua_pushboolean( L, c->rgb( r, g, b ) );
    } F4L_CATCH( L );
    return 1;
  }

  int chooser_hsv( lua_State* L ) {
    Fl_Color_Chooser* c = check_color_chooser( L, 1 );
    double h = luaL_checknumber( L, 2 );
    double s = luaL_checknumber( L, 3 );
    double v = luaL_checknumber( L, 4 );
    F4L_TRY {
      lua_pushboolean( L, c->hsv( h, s, v ) );
    } F4L_CATCH( L );
    return 1;
  }

} // anonymous namespace


MOON_LOCAL void f4l_color_chooser_setup( lua_State* L ) {
  luaL_Reg const methods[] = {
    F4L_WIDGET_METHODS,
    F4L_GROUP_METHODS,
    { "rgb", chooser_rgb },
    { "hsv", chooser_hsv },
    { "__index", chooser_index },
    { "__newindex", chooser_newindex },
    { NULL, NULL }
  };
  moon_defobject( L, F4L_COLOR_CHOOSER_NAME, 0, methods, 0 );
  moon_defcast( L, F4L_COLOR_CHOOSER_NAME, F4L_GROUP_NAME,
                f4l_cast< Fl_Color_Chooser, Fl_Group > );
  moon_defcast( L, F4L_COLOR_CHOOSER_NAME, F4L_WIDGET_NAME,
                f4l_cast< Fl_Color_Chooser, Fl_Widget > );
  f4l_new_class_table( L, "Color_Chooser", new_color_chooser );
}

