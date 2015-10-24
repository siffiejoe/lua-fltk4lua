#include "fltk4lua.hxx"
#include "f4l_menu.hxx"
#include "f4l_widget.hxx"
#include "f4l_enums.hxx"
#include <FL/Fl_Input_Choice.H>
#include <cstring>
#include <climits>


namespace {

  inline Fl_Input_Choice* check_input_choice( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_INPUT_CHOICE_NAME );
    return static_cast< Fl_Input_Choice* >( p );
  }


  int input_choice_index_( lua_State* L, Fl_Input_Choice* ic,
                           char const* key, size_t n ) {
    using namespace std;
    switch( n ) {
      case 5:
        if( F4L_MEMCMP( key, "input", 5 ) == 0 ) {
          if( moon_getuvfield( L, 1, "input" ) == LUA_TNIL ) {
            f4l_new_member< Fl_Input >( L, F4L_INPUT_NAME,
                                        ic->input(), 1 );
            lua_pushvalue( L, -1 );
            moon_setuvfield( L, 1, "input" );
          }
          return 1;
        } else if( F4L_MEMCMP( key, "value", 5 ) == 0 ) {
          char const* s = ic->value();
          if( s != NULL )
            lua_pushstring( L, ic->value() );
          else
            lua_pushnil( L );
          return 1;
        }
        break;
      case 7:
        if( F4L_MEMCMP( key, "changed", 7 ) == 0 ) {
          lua_pushboolean( L, ic->changed() );
          return 1;
        }
        break;
      case 8:
        if( F4L_MEMCMP( key, "down_box", 8 ) == 0 ) {
          f4l_push_boxtype( L, ic->down_box() );
          return 1;
        } else if( F4L_MEMCMP( key, "textfont", 8 ) == 0 ) {
          f4l_push_font( L, ic->textfont() );
          return 1;
        } else if( F4L_MEMCMP( key, "textsize", 8 ) == 0 ) {
          lua_pushinteger( L, ic->textsize() );
          return 1;
        }
        break;
      case 9:
        if( F4L_MEMCMP( key, "textcolor", 9 ) == 0 ) {
          f4l_push_color( L, ic->textcolor() );
          return 1;
        }
        break;
      case 10:
        if( F4L_MEMCMP( key, "menubutton", 10 ) == 0 ) {
          if( moon_getuvfield( L, 1, "menubutton" ) == LUA_TNIL ) {
            f4l_new_member< Fl_Menu_Button >( L, F4L_MENU_BUTTON_NAME,
                                              ic->menubutton(), 1 );
            lua_pushvalue( L, -1 );
            moon_setuvfield( L, 1, "menubutton" );
          }
          return 1;
        }
        break;
    }
    return 0;
  }


  int input_choice_newindex_( lua_State* L, Fl_Input_Choice* ic,
                              char const* key, size_t n ) {
    using namespace std;
    switch( n ) {
      case 5:
        if( F4L_MEMCMP( key, "value", 5 ) == 0 ) {
          if( lua_type( L, 3 ) == LUA_TNUMBER ) {
            int idx = moon_checkint( L, 3, 0, INT_MAX );
            int sz = 0;
            Fl_Menu_Item const* mi = ic->menu();
            if( mi != NULL )
              sz = mi->size();
            luaL_argcheck( L, idx < sz, 3, "index too large" );
            ic->value( idx );
          } else {
            char const* s = luaL_optstring( L, 3, NULL );
            ic->value( s );
          }
          return 1;
        }
        break;
      case 8:
        if( F4L_MEMCMP( key, "down_box", 8 ) == 0 ) {
          ic->down_box( f4l_check_boxtype( L, 3 ) );
          return 1;
        } else if( F4L_MEMCMP( key, "textfont", 8 ) == 0 ) {
          ic->textfont( f4l_check_font( L, 3 ) );
          return 1;
        } else if( F4L_MEMCMP( key, "textsize", 8 ) == 0 ) {
          ic->textsize( moon_checkint( L, 3, 0, INT_MAX ) );
          return 1;
        }
        break;
      case 9:
        if( F4L_MEMCMP( key, "textcolor", 9 ) == 0 ) {
          ic->textcolor( f4l_check_color( L, 3 ) );
          return 1;
        }
        break;
    }
    return 0;
  }

} // anonymous namespace


F4L_DEF_DELETE( Fl_Input_Choice )


F4L_LUA_LLINKAGE_BEGIN

static int new_input_choice( lua_State* L ) {
  F4L_TRY( L ) {
    Fl_Input_Choice* ic = NULL;
    ic = f4l_new_widget< Fl_Input_Choice >( L, F4L_INPUT_CHOICE_NAME,
                                            f4l_delete_Fl_Input_Choice );
    /* The input userdata can be created on demand in the __index
     * metamethod, but we need the menubutton registered as a widget
     * in the implementation of add() and clear(). */
    f4l_new_member< Fl_Menu_Button >( L, F4L_MENU_BUTTON_NAME,
                                      ic->menubutton(), -1 );
    moon_setuvfield( L, -2, "menubutton" );
  } F4L_CATCH( L );
  return 1;
}


static int input_choice_index( lua_State* L ) {
  Fl_Input_Choice* ic = check_input_choice( L, 1 );
  size_t n = 0;
  char const* key = luaL_checklstring( L, 2, &n );
  F4L_TRY( L ) {
    if( !input_choice_index_( L, ic, key, n ) &&
        !f4l_widget_index_( L, ic, key, n ) &&
        !f4l_bad_property( L, F4L_INPUT_CHOICE_NAME, key ) )
      lua_pushnil( L );
  } F4L_CATCH( L );
  return 1;
}


static int input_choice_newindex( lua_State* L ) {
  Fl_Input_Choice* ic = check_input_choice( L, 1 );
  size_t n = 0;
  char const* key = luaL_checklstring( L, 2, &n );
  F4L_TRY( L ) {
    (void)(input_choice_newindex_( L, ic, key, n ) ||
           f4l_widget_newindex_( L, ic, key, n ) ||
           f4l_bad_property( L, F4L_INPUT_CHOICE_NAME, key ));
  } F4L_CATCH( L );
  return 0;
}


static int input_choice_add( lua_State* L ) {
  Fl_Input_Choice* ic = check_input_choice( L, 1 );
  luaL_checkstring( L, 2 );
  lua_settop( L, 2 );
  f4l_push_widget( L, ic->menubutton() );
  lua_replace( L, 1 );
  /* Forward to f4l_menu_add(). A similar thing happens in
   * Fl_Input_Choice::add() anyway, but this way we don't have
   * to duplicate the book keeping code. */
  f4l_menu_add( L );
  return 0;
}


static int input_choice_clear( lua_State* L ) {
  Fl_Input_Choice* ic = check_input_choice( L, 1 );
  lua_settop( L, 1 );
  f4l_push_widget( L, ic->menubutton() );
  lua_replace( L, 1 );
  /* Forward to f4l_menu_clear(). A similar thing happens in
   * Fl_Input_Choice::clear() anyway, but this way we don't have
   * to duplicate the book keeping code. */
  return f4l_menu_clear( L );
}


static int input_choice_clear_changed( lua_State* L ) {
  Fl_Input_Choice* ic = check_input_choice( L, 1 );
  F4L_TRY( L ) {
    ic->clear_changed();
  } F4L_CATCH( L );
  return 0;
}


static int input_choice_set_changed( lua_State* L ) {
  Fl_Input_Choice* ic = check_input_choice( L, 1 );
  F4L_TRY( L ) {
    ic->set_changed();
  } F4L_CATCH( L );
  return 0;
}

F4L_LUA_LLINKAGE_END


F4L_DEF_CAST( Fl_Input_Choice, Fl_Widget )


MOON_LOCAL void f4l_input_choice_setup( lua_State* L ) {
  luaL_Reg const methods[] = {
    F4L_WIDGET_METHODS,
    { "add", input_choice_add },
    { "clear", input_choice_clear },
    { "clear_changed", input_choice_clear_changed },
    { "set_changed", input_choice_set_changed },
    { "__index", input_choice_index },
    { "__newindex", input_choice_newindex },
    { NULL, NULL }
  };
  moon_defobject( L, F4L_INPUT_CHOICE_NAME, 0, methods, 0 );
  moon_defcast( L, F4L_INPUT_CHOICE_NAME, F4L_WIDGET_NAME,
                f4l_cast_Fl_Input_Choice_Fl_Widget );
  f4l_new_class_table( L, "Input_Choice", new_input_choice );
}

