#include "fltk4lua.hxx"
#include "f4l_valuator.hxx"
#include "f4l_widget.hxx"
#include "f4l_enums.hxx"
#include <FL/Fl_Value_Input.H>
#include <cstring>
#include <climits>


namespace {

  inline Fl_Value_Input* check_value_input( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_VALUE_INPUT_NAME );
    return static_cast< Fl_Value_Input* >( p );
  }


  int value_input_index_( lua_State* L, Fl_Value_Input* v,
                          char const* key, size_t n ) {
    using namespace std;
    switch( n ) {
      case 4:
        if( F4L_MEMCMP( key, "soft", 4 ) == 0 ) {
          lua_pushboolean( L, v->soft() );
          return 1;
        }
        break;
      case 5:
        if( F4L_MEMCMP( key, "input", 5 ) == 0 ) {
          if( moon_getuvfield( L, 1, "input" ) == LUA_TNIL ) {
            f4l_new_member< Fl_Input >( L, F4L_INPUT_NAME, &v->input, 1 );
            lua_pushvalue( L, -1 );
            moon_setuvfield( L, 1, "input" );
          }
          return 1;
        }
        break;
      case 8:
        if( F4L_MEMCMP( key, "shortcut", 8 ) == 0 ) {
          f4l_push_shortcut( L, v->shortcut() );
          return 1;
        } else if( F4L_MEMCMP( key, "textfont", 8 ) == 0 ) {
          f4l_push_font( L, v->textfont() );
          return 1;
        } else if( F4L_MEMCMP( key, "textsize", 8 ) == 0 ) {
          lua_pushinteger( L, v->textsize() );
          return 1;
        }
        break;
      case 9:
        if( F4L_MEMCMP( key, "textcolor", 9 ) == 0 ) {
          f4l_push_color( L, v->textcolor() );
          return 1;
        }
        break;
      case 12:
        if( F4L_MEMCMP( key, "cursor_color", 12 ) == 0 ) {
          f4l_push_color( L, v->cursor_color() );
          return 1;
        }
        break;
    }
    return 0;
  }


  int value_input_newindex_( lua_State* L, Fl_Value_Input* v,
                             char const* key, size_t n ) {
    using namespace std;
    switch( n ) {
      case 4:
        if( F4L_MEMCMP( key, "soft", 4 ) == 0 ) {
          v->soft( lua_toboolean( L, 3 ) );
          return 1;
        }
        break;
      case 8:
        if( F4L_MEMCMP( key, "shortcut", 8 ) == 0 ) {
          v->shortcut( f4l_check_shortcut( L, 3 ) );
          return 1;
        } else if( F4L_MEMCMP( key, "textfont", 8 ) == 0 ) {
          v->textfont( f4l_check_font( L, 3 ) );
          return 1;
        } else if( F4L_MEMCMP( key, "textsize", 8 ) == 0 ) {
          v->textsize( moon_checkint( L, 3, 0, INT_MAX ) );
          return 1;
        }
        break;
      case 9:
        if( F4L_MEMCMP( key, "textcolor", 9 ) == 0 ) {
          v->textcolor( f4l_check_color( L, 3 ) );
          return 1;
        }
        break;
      case 12:
        if( F4L_MEMCMP( key, "cursor_color", 12 ) == 0 ) {
          v->cursor_color( f4l_check_color( L, 3 ) );
          return 1;
        }
        break;
    }
    return 0;
  }

} // anonymous namespace


F4L_DEF_DELETE( Fl_Value_Input )


F4L_LUA_LLINKAGE_BEGIN

static int new_value_input( lua_State* L ) {
  F4L_TRY( L ) {
    f4l_new_widget< Fl_Value_Input >( L, F4L_VALUE_INPUT_NAME,
                                      f4l_delete_Fl_Value_Input );
  } F4L_CATCH( L );
  return 1;
}


static int value_input_index( lua_State* L ) {
  Fl_Value_Input* v = check_value_input( L, 1 );
  size_t n = 0;
  char const* key = luaL_checklstring( L, 2, &n );
  F4L_TRY( L ) {
    if( !value_input_index_( L, v, key, n ) &&
        !f4l_valuator_index_( L, v, key, n ) &&
        !f4l_widget_index_( L, v, key, n ) &&
        !f4l_bad_property( L, F4L_VALUE_INPUT_NAME, key ) )
      lua_pushnil( L );
  } F4L_CATCH( L );
  return 1;
}


static int value_input_newindex( lua_State* L ) {
  Fl_Value_Input* v = check_value_input( L, 1 );
  size_t n = 0;
  char const* key = luaL_checklstring( L, 2, &n );
  F4L_TRY( L ) {
    (void)(value_input_newindex_( L, v, key, n ) ||
           f4l_valuator_newindex_( L, v, key, n ) ||
           f4l_widget_newindex_( L, v, key, n ) ||
           f4l_bad_property( L, F4L_VALUE_INPUT_NAME, key ));
  } F4L_CATCH( L );
  return 0;
}

F4L_LUA_LLINKAGE_END


F4L_DEF_CAST( Fl_Value_Input, Fl_Valuator )
F4L_DEF_CAST( Fl_Value_Input, Fl_Widget )


MOON_LOCAL void f4l_value_input_setup( lua_State* L ) {
  luaL_Reg const methods[] = {
    F4L_WIDGET_METHODS,
    F4L_VALUATOR_METHODS,
    { "__index", value_input_index },
    { "__newindex", value_input_newindex },
    { NULL, NULL }
  };
  moon_defobject( L, F4L_VALUE_INPUT_NAME, 0, methods, 0 );
  moon_defcast( L, F4L_VALUE_INPUT_NAME, F4L_VALUATOR_NAME,
                f4l_cast_Fl_Value_Input_Fl_Valuator );
  moon_defcast( L, F4L_VALUE_INPUT_NAME, F4L_WIDGET_NAME,
                f4l_cast_Fl_Value_Input_Fl_Widget );
  f4l_new_class_table( L, "Value_Input", new_value_input );
}

