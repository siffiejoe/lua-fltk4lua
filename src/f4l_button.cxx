#include "fltk4lua.hxx"
#include "f4l_button.hxx"
#include "f4l_widget.hxx"
#include "f4l_enums.hxx" // TODO
#include <cstring>
#include <climits> // TODO

namespace {

  inline Fl_Button* check_button( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_BUTTON_NAME );
    return static_cast< Fl_Button* >( p );
  }

  int button_index( lua_State* L ) {
    Fl_Button* b = check_button( L, 1 );
    size_t n = 0;
    char const* key = luaL_checklstring( L, 2, &n );
    F4L_TRY {
      if( !f4l_button_index_( L, b, key, n ) &&
          !f4l_widget_index_( L, b, key, n ) )
        lua_pushnil( L );
    } F4L_CATCH( L );
    return 1;
  }

  int button_newindex( lua_State* L ) {
    Fl_Button* b = check_button( L, 1 );
    size_t n = 0;
    char const* key = luaL_checklstring( L, 2, &n );
    F4L_TRY {
      (void)(f4l_button_newindex_( L, b, key, n ) ||
             f4l_widget_newindex_( L, b, key, n ));
    } F4L_CATCH( L );
    return 0;
  }

  int new_button( lua_State* L ) {
    F4L_TRY {
      f4l_new_widget< Fl_Button >( L, F4L_BUTTON_NAME );
    } F4L_CATCH( L );
    return 1;
  }

} // anonymous namespace


MOON_LOCAL int f4l_button_index_( lua_State* L, Fl_Button* b,
                                  char const* key, size_t n ) {
  switch( n ) {
    case 5:
      if( F4L_MEMCMP( key, "value", 5 ) == 0 ) {
        lua_pushboolean( L, b->value() );
        return 1;
      }
      break;
    case 8:
      if( F4L_MEMCMP( key, "down_box", 8 ) == 0 ) {
        f4l_push_boxtype( L, b->down_box() );
        return 1;
      }
      // TODO: shortcut
      break;
    case 10:
      if( F4L_MEMCMP( key, "down_color", 10 ) == 0 ) {
        f4l_push_color( L, b->down_color() );
        return 1;
      }
      break;
  }
  return 0;
}

MOON_LOCAL int f4l_button_newindex_( lua_State* L, Fl_Button* b,
                                     char const* key, size_t n ) {
  switch( n ) {
    case 5:
      if( F4L_MEMCMP( key, "value", 5 ) == 0 ) {
        b->value( lua_toboolean( L, 3 ) );
        return 1;
      }
      break;
    case 8:
      if( F4L_MEMCMP( key, "down_box", 8 ) == 0 ) {
        b->down_box( f4l_check_boxtype( L, 3 ) );
        return 1;
      }
      // TODO: shortcut
      break;
    case 10:
      if( F4L_MEMCMP( key, "down_color", 10 ) == 0 ) {
        b->down_color( f4l_check_color( L, 3 ) );
        return 1;
      }
      break;
  }
  return 0;
}


MOON_LOCAL int f4l_button_clear( lua_State* L ) {
  Fl_Button* b = check_button( L, 1 );
  F4L_TRY {
    lua_pushboolean( L, b->clear() );
  } F4L_CATCH( L );
  return 1;
}


MOON_LOCAL int f4l_button_set( lua_State* L ) {
  Fl_Button* b = check_button( L, 1 );
  F4L_TRY {
    lua_pushboolean( L, b->set() );
  } F4L_CATCH( L );
  return 1;
}


MOON_LOCAL int f4l_button_setonly( lua_State* L ) {
  Fl_Button* b = check_button( L, 1 );
  F4L_TRY {
    b->setonly();
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL void f4l_button_setup( lua_State* L ) {
  luaL_Reg const functions[] = {
    { "Button", new_button },
    { NULL, NULL }
  };
  luaL_Reg const methods[] = {
    F4L_WIDGET_METHODS,
    F4L_BUTTON_METHODS,
    { "__index", button_index },
    { "__newindex", button_newindex },
    { NULL, NULL }
  };
  moon_defobject( L, F4L_BUTTON_NAME, 0, methods, 0 );
  moon_defcast( L, F4L_BUTTON_NAME, F4L_WIDGET_NAME,
                f4l_cast< Fl_Button, Fl_Widget > );
  luaL_setfuncs( L, functions, 0 );
}

