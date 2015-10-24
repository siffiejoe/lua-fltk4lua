#include "fltk4lua.hxx"
#include "f4l_valuator.hxx"
#include "f4l_widget.hxx"
#include "f4l_enums.hxx"
#include <FL/Fl_Value_Output.H>
#include <cstring>
#include <climits>


namespace {

  inline Fl_Value_Output* check_value_output( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_VALUE_OUTPUT_NAME );
    return static_cast< Fl_Value_Output* >( p );
  }


  int value_output_index_( lua_State* L, Fl_Value_Output* v,
                           char const* key, size_t n ) {
    using namespace std;
    switch( n ) {
      case 4:
        if( F4L_MEMCMP( key, "soft", 4 ) == 0 ) {
          lua_pushboolean( L, v->soft() );
          return 1;
        }
        break;
      case 8:
        if( F4L_MEMCMP( key, "textfont", 8 ) == 0 ) {
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
    }
    return 0;
  }


  int value_output_newindex_( lua_State* L, Fl_Value_Output* v,
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
        if( F4L_MEMCMP( key, "textfont", 8 ) == 0 ) {
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
    }
    return 0;
  }

} // anonymous namespace


F4L_DEF_DELETE( Fl_Value_Output )


F4L_LUA_LLINKAGE_BEGIN

static int new_value_output( lua_State* L ) {
  F4L_TRY( L ) {
    f4l_new_widget< Fl_Value_Output >( L, F4L_VALUE_OUTPUT_NAME,
                                       f4l_delete_Fl_Value_Output );
  } F4L_CATCH( L );
  return 1;
}


static int value_output_index( lua_State* L ) {
  Fl_Value_Output* v = check_value_output( L, 1 );
  size_t n = 0;
  char const* key = luaL_checklstring( L, 2, &n );
  F4L_TRY( L ) {
    if( !value_output_index_( L, v, key, n ) &&
        !f4l_valuator_index_( L, v, key, n ) &&
        !f4l_widget_index_( L, v, key, n ) &&
        !f4l_bad_property( L, F4L_VALUE_OUTPUT_NAME, key ) )
      lua_pushnil( L );
  } F4L_CATCH( L );
  return 1;
}


static int value_output_newindex( lua_State* L ) {
  Fl_Value_Output* v = check_value_output( L, 1 );
  size_t n = 0;
  char const* key = luaL_checklstring( L, 2, &n );
  F4L_TRY( L ) {
    (void)(value_output_newindex_( L, v, key, n ) ||
           f4l_valuator_newindex_( L, v, key, n ) ||
           f4l_widget_newindex_( L, v, key, n ) ||
           f4l_bad_property( L, F4L_VALUE_OUTPUT_NAME, key ));
  } F4L_CATCH( L );
  return 0;
}

F4L_LUA_LLINKAGE_END


F4L_DEF_CAST( Fl_Value_Output, Fl_Valuator )
F4L_DEF_CAST( Fl_Value_Output, Fl_Widget )


MOON_LOCAL void f4l_value_output_setup( lua_State* L ) {
  luaL_Reg const methods[] = {
    F4L_WIDGET_METHODS,
    F4L_VALUATOR_METHODS,
    { "__index", value_output_index },
    { "__newindex", value_output_newindex },
    { NULL, NULL }
  };
  moon_defobject( L, F4L_VALUE_OUTPUT_NAME, 0, methods, 0 );
  moon_defcast( L, F4L_VALUE_OUTPUT_NAME, F4L_VALUATOR_NAME,
                f4l_cast_Fl_Value_Output_Fl_Valuator );
  moon_defcast( L, F4L_VALUE_OUTPUT_NAME, F4L_WIDGET_NAME,
                f4l_cast_Fl_Value_Output_Fl_Widget );
  f4l_new_class_table( L, "Value_Output", new_value_output );
}

