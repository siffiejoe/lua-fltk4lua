#include "fltk4lua.hxx"
#include "f4l_widget.hxx"
#include "f4l_enums.hxx"
#include <FL/Fl_Spinner.H>
#include <cstring>
#include <climits>


#define TYPE_LIST( _ ) \
  _( "FL_INT_INPUT", FL_INT_INPUT ) \
  _( "FL_FLOAT_INPUT", FL_FLOAT_INPUT )

  F4L_GEN_TYPE_ENUM( TYPE_LIST, spinner )


namespace {

  inline Fl_Spinner* check_spinner( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_SPINNER_NAME );
    return static_cast< Fl_Spinner* >( p );
  }


  int spinner_index_( lua_State* L, Fl_Spinner* sp,
                      char const* key, size_t n ) {
    using namespace std;
    switch( n ) {
      case 4:
        if( F4L_MEMCMP( key, "step", 4 ) == 0 ) {
          lua_pushnumber( L, sp->step() );
          return 1;
        } else if( F4L_MEMCMP( key, "type", 4 ) == 0 ) {
          f4l_push_type_spinner( L, sp->type() );
          return 1;
        }
        break;
      case 5:
        if( F4L_MEMCMP( key, "color", 5 ) == 0 ) {
          f4l_push_color( L, sp->color() );
          return 1;
        } else if( F4L_MEMCMP( key, "value", 5 ) == 0 ) {
          lua_pushnumber( L, sp->value() );
          return 1;
        }
        break;
      case 6:
        if( F4L_MEMCMP( key, "format", 6 ) == 0 ) {
          lua_pushstring( L, sp->format() );
          return 1;
        }
        break;
      case 7:
        if( F4L_MEMCMP( key, "maximum", 7 ) == 0 ) {
          lua_pushnumber( L, sp->maximum() );
          return 1;
        } else if( F4L_MEMCMP( key, "minimum", 7 ) == 0 ) {
          lua_pushnumber( L, sp->minimum() );
          return 1;
        }
        break;
      case 8:
        if( F4L_MEMCMP( key, "textfont", 8 ) == 0 ) {
          f4l_push_font( L, sp->textfont() );
          return 1;
        } else if( F4L_MEMCMP( key, "textsize", 8 ) == 0 ) {
          lua_pushinteger( L, sp->textsize() );
          return 1;
        }
        break;
      case 9:
        if( F4L_MEMCMP( key, "textcolor", 9 ) == 0 ) {
          f4l_push_color( L, sp->textcolor() );
          return 1;
        }
        break;
    }
    return 0;
  }


  int spinner_newindex_( lua_State* L, Fl_Spinner* sp,
                         char const* key, size_t n ) {
    using namespace std;
    switch( n ) {
      case 4:
        if( F4L_MEMCMP( key, "step", 4 ) == 0 ) {
          sp->step( luaL_checknumber( L, 3 ) );
          return 1;
        } else if( F4L_MEMCMP( key, "type", 4 ) == 0 ) {
          sp->type( f4l_check_type_spinner( L, 3 ) );
          return 1;
        }
        break;
      case 5:
        if( F4L_MEMCMP( key, "color", 5 ) == 0 ) {
          sp->color( f4l_check_color( L, 3 ) );
          return 1;
        } else if( F4L_MEMCMP( key, "value", 5 ) == 0 ) {
          sp->value( luaL_checknumber( L, 3 ) );
          return 1;
        }
        break;
      case 6:
        if( F4L_MEMCMP( key, "format", 6 ) == 0 ) {
          sp->format( luaL_checkstring( L, 3 ) );
          return 1;
        }
        break;
      case 7:
        if( F4L_MEMCMP( key, "maximum", 7 ) == 0 ) {
          sp->maximum( luaL_checknumber( L, 3 ) );
          return 1;
        } else if( F4L_MEMCMP( key, "minimum", 7 ) == 0 ) {
          sp->minimum( luaL_checknumber( L, 3 ) );
          return 1;
        }
        break;
      case 8:
        if( F4L_MEMCMP( key, "textfont", 8 ) == 0 ) {
          sp->textfont( f4l_check_font( L, 3 ) );
          return 1;
        } else if( F4L_MEMCMP( key, "textsize", 8 ) == 0 ) {
          sp->textsize( moon_checkint( L, 3, 0, INT_MAX ) );
          return 1;
        }
        break;
      case 9:
        if( F4L_MEMCMP( key, "textcolor", 9 ) == 0 ) {
          sp->textcolor( f4l_check_color( L, 3 ) );
          return 1;
        }
        break;
    }
    return 0;
  }

} // anonymous namespace


F4L_DEF_DELETE( Fl_Spinner )


F4L_LUA_LLINKAGE_BEGIN

static int new_spinner( lua_State* L ) {
  F4L_TRY( L ) {
    f4l_new_widget< Fl_Spinner >( L, F4L_SPINNER_NAME,
                                  f4l_delete_Fl_Spinner );
  } F4L_CATCH( L );
  return 1;
}


static int spinner_index( lua_State* L ) {
  Fl_Spinner* sp = check_spinner( L, 1 );
  size_t n = 0;
  char const* key = luaL_checklstring( L, 2, &n );
  F4L_TRY( L ) {
    if( !spinner_index_( L, sp, key, n ) &&
        !f4l_widget_index_( L, sp, key, n ) &&
        !f4l_bad_property( L, F4L_SPINNER_NAME, key ) )
      lua_pushnil( L );
  } F4L_CATCH( L );
  return 1;
}


static int spinner_newindex( lua_State* L ) {
  Fl_Spinner* sp = check_spinner( L, 1 );
  size_t n = 0;
  char const* key = luaL_checklstring( L, 2, &n );
  F4L_TRY( L ) {
    (void)(spinner_newindex_( L, sp, key, n ) ||
           f4l_widget_newindex_( L, sp, key, n ) ||
           f4l_bad_property( L, F4L_SPINNER_NAME, key ));
  } F4L_CATCH( L );
  return 0;
}


static int spinner_range( lua_State* L ) {
  Fl_Spinner* sp = check_spinner( L, 1 );
  double a = luaL_checknumber( L, 2 );
  double b = luaL_checknumber( L, 3 );
  F4L_TRY( L ) {
    sp->range( a, b );
  } F4L_CATCH( L );
  return 0;
}

F4L_LUA_LLINKAGE_END


F4L_DEF_CAST( Fl_Spinner, Fl_Widget )


MOON_LOCAL void f4l_spinner_setup( lua_State* L ) {
  luaL_Reg const methods[] = {
    F4L_WIDGET_METHODS,
    { "range", spinner_range },
    { "__index", spinner_index },
    { "__newindex", spinner_newindex },
    { NULL, NULL }
  };
  moon_defobject( L, F4L_SPINNER_NAME, 0, methods, 0 );
  moon_defcast( L, F4L_SPINNER_NAME, F4L_WIDGET_NAME,
                f4l_cast_Fl_Spinner_Fl_Widget );
  f4l_new_class_table( L, "Spinner", new_spinner );
}

