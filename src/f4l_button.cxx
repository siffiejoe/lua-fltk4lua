#include "fltk4lua.hxx"
#include "f4l_button.hxx"
#include "f4l_widget.hxx"
#include "f4l_enums.hxx"
#include <cstring>

namespace {

#define TYPE_LIST( _ ) \
  _( "FL_NORMAL_BUTTON", FL_NORMAL_BUTTON ) \
  _( "FL_TOGGLE_BUTTON", FL_TOGGLE_BUTTON ) \
  _( "FL_RADIO_BUTTON", FL_RADIO_BUTTON )

  F4L_GEN_TYPE_ENUM( TYPE_LIST, button )


  inline Fl_Button* check_button( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_BUTTON_NAME );
    return static_cast< Fl_Button* >( p );
  }

  inline Fl_Repeat_Button* check_repeat_button( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_REPEAT_BUTTON_NAME );
    return static_cast< Fl_Repeat_Button* >( p );
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

  int new_check_button( lua_State* L ) {
    F4L_TRY {
      f4l_new_widget< Fl_Check_Button >( L, F4L_CHECK_BUTTON_NAME );
    } F4L_CATCH( L );
    return 1;
  }

  int new_light_button( lua_State* L ) {
    F4L_TRY {
      f4l_new_widget< Fl_Light_Button >( L, F4L_LIGHT_BUTTON_NAME );
    } F4L_CATCH( L );
    return 1;
  }

  int new_repeat_button( lua_State* L ) {
    F4L_TRY {
      f4l_new_widget< Fl_Repeat_Button >( L, F4L_REPEAT_BUTTON_NAME );
    } F4L_CATCH( L );
    return 1;
  }

  int new_return_button( lua_State* L ) {
    F4L_TRY {
      f4l_new_widget< Fl_Return_Button >( L, F4L_RETURN_BUTTON_NAME );
    } F4L_CATCH( L );
    return 1;
  }

  int new_round_button( lua_State* L ) {
    F4L_TRY {
      f4l_new_widget< Fl_Round_Button >( L, F4L_ROUND_BUTTON_NAME );
    } F4L_CATCH( L );
    return 1;
  }

  /* a non-virtual member function that is overridden in the class
   * Fl_Repeat_Button */
  int repeat_button_deactivate( lua_State* L ) {
    Fl_Repeat_Button* b = check_repeat_button( L, 1 );
    F4L_TRY {
      b->deactivate();
    } F4L_CATCH( L );
    return 0;
  }

} // anonymous namespace


MOON_LOCAL int f4l_button_index_( lua_State* L, Fl_Button* b,
                                  char const* key, size_t n ) {
  using namespace std;
  switch( n ) {
    case 4:
      if( F4L_MEMCMP( key, "type", 4 ) == 0 ) {
        f4l_push_type_button( L, b->type() );
        return 1;
      }
      break;
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
  using namespace std;
  switch( n ) {
    case 4:
      if( F4L_MEMCMP( key, "type", 4 ) == 0 ) {
        b->type( f4l_check_type_button( L, 3 ) );
        return 1;
      }
      break;
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
  luaL_Reg const methods[] = {
    F4L_WIDGET_METHODS,
    F4L_BUTTON_METHODS,
    { "__index", button_index },
    { "__newindex", button_newindex },
    { NULL, NULL }
  };
  luaL_Reg const rb_methods[] = {
    F4L_WIDGET_METHODS,
    F4L_BUTTON_METHODS,
    { "deactivate", repeat_button_deactivate },
    { "__index", button_index },
    { "__newindex", button_newindex },
    { NULL, NULL }
  };

  moon_defobject( L, F4L_BUTTON_NAME, 0, methods, 0 );
  moon_defcast( L, F4L_BUTTON_NAME, F4L_WIDGET_NAME,
                f4l_cast< Fl_Button, Fl_Widget > );

  moon_defobject( L, F4L_CHECK_BUTTON_NAME, 0, methods, 0 );
  moon_defcast( L, F4L_CHECK_BUTTON_NAME, F4L_BUTTON_NAME,
                f4l_cast< Fl_Check_Button, Fl_Button > );
  moon_defcast( L, F4L_CHECK_BUTTON_NAME, F4L_WIDGET_NAME,
                f4l_cast< Fl_Check_Button, Fl_Widget > );

  moon_defobject( L, F4L_LIGHT_BUTTON_NAME, 0, methods, 0 );
  moon_defcast( L, F4L_LIGHT_BUTTON_NAME, F4L_BUTTON_NAME,
                f4l_cast< Fl_Light_Button, Fl_Button > );
  moon_defcast( L, F4L_LIGHT_BUTTON_NAME, F4L_WIDGET_NAME,
                f4l_cast< Fl_Light_Button, Fl_Widget > );

  moon_defobject( L, F4L_REPEAT_BUTTON_NAME, 0, rb_methods, 0 );
  moon_defcast( L, F4L_REPEAT_BUTTON_NAME, F4L_BUTTON_NAME,
                f4l_cast< Fl_Repeat_Button, Fl_Button > );
  moon_defcast( L, F4L_REPEAT_BUTTON_NAME, F4L_WIDGET_NAME,
                f4l_cast< Fl_Repeat_Button, Fl_Widget > );

  moon_defobject( L, F4L_RETURN_BUTTON_NAME, 0, methods, 0 );
  moon_defcast( L, F4L_RETURN_BUTTON_NAME, F4L_BUTTON_NAME,
                f4l_cast< Fl_Return_Button, Fl_Button > );
  moon_defcast( L, F4L_RETURN_BUTTON_NAME, F4L_WIDGET_NAME,
                f4l_cast< Fl_Return_Button, Fl_Widget > );

  moon_defobject( L, F4L_ROUND_BUTTON_NAME, 0, methods, 0 );
  moon_defcast( L, F4L_ROUND_BUTTON_NAME, F4L_BUTTON_NAME,
                f4l_cast< Fl_Round_Button, Fl_Button > );
  moon_defcast( L, F4L_ROUND_BUTTON_NAME, F4L_WIDGET_NAME,
                f4l_cast< Fl_Round_Button, Fl_Widget > );

  f4l_new_class_table( L, "Button", new_button );
  f4l_new_class_table( L, "Check_Button", new_check_button );
  f4l_new_class_table( L, "Light_Button", new_light_button );
  f4l_new_class_table( L, "Repeat_Button", new_repeat_button );
  f4l_new_class_table( L, "Return_Button", new_return_button );
  f4l_new_class_table( L, "Round_Button", new_round_button );
}

