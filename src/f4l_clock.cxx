#include "fltk4lua.hxx"
#include "f4l_widget.hxx"
#include "f4l_enums.hxx"
#include <FL/Fl_Clock.H>
#include <cstring>
#include <climits>


#define TYPE_LIST( _ ) \
  _( "FL_SQUARE_CLOCK", FL_SQUARE_CLOCK ) \
  _( "FL_ROUND_CLOCK", FL_ROUND_CLOCK )

  F4L_GEN_TYPE_ENUM( TYPE_LIST, clock )


namespace {

  inline Fl_Clock_Output* check_clock( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_CLOCK_OUTPUT_NAME );
    return static_cast< Fl_Clock_Output* >( p );
  }


  int clock_index_( lua_State* L, Fl_Clock_Output* c,
                    char const* key, size_t n ) {
    using namespace std;
    switch( n ) {
      case 4:
        if( F4L_MEMCMP( key, "hour", 4 ) == 0 ) {
          lua_pushinteger( L, c->hour() );
          return 1;
        } else if( F4L_MEMCMP( key, "type", 4 ) == 0 ) {
          f4l_push_type_clock( L, c->type() );
          return 1;
        }
        break;
      case 5:
        if( F4L_MEMCMP( key, "value", 5 ) == 0 ) {
          if( sizeof( lua_Integer ) * CHAR_BIT > 32 )
            lua_pushinteger( L, c->value() );
          else
            lua_pushnumber( L, c->value() );
          return 1;
        }
        break;
      case 6:
        if( F4L_MEMCMP( key, "minute", 6 ) == 0 ) {
          lua_pushinteger( L, c->minute() );
          return 1;
        } else if( F4L_MEMCMP( key, "second", 6 ) == 0 ) {
          lua_pushinteger( L, c->second() );
          return 1;
        }
        break;
    }
    return 0;
  }


  int clock_newindex_( lua_State* L, Fl_Clock_Output* c,
                       char const* key, size_t n ) {
    using namespace std;
    switch( n ) {
      case 4:
        if( F4L_MEMCMP( key, "type", 4 ) == 0 ) {
          c->type( f4l_check_type_clock( L, 3 ) );
          return 1;
        }
        break;
      case 5:
        if( F4L_MEMCMP( key, "value", 5 ) == 0 ) {
          if( sizeof( lua_Integer ) * CHAR_BIT > 32 )
            c->value( moon_checkint( L, 3, 0, ULONG_MAX ) );
          else
            c->value( static_cast< ulong >( luaL_checknumber( L, 3 ) ) );
          return 1;
        }
        break;
    }
    return 0;
  }

} // anonymous namespace


F4L_DEF_DELETE( Fl_Clock_Output )
F4L_DEF_DELETE( Fl_Clock )


F4L_LUA_LLINKAGE_BEGIN

static int new_clock_output( lua_State* L ) {
  F4L_TRY( L ) {
    f4l_new_widget< Fl_Clock_Output >( L, F4L_CLOCK_OUTPUT_NAME,
                                       f4l_delete_Fl_Clock_Output );
  } F4L_CATCH( L );
  return 1;
}


static int new_clock( lua_State* L ) {
  F4L_TRY( L ) {
    f4l_new_widget< Fl_Clock >( L, F4L_CLOCK_NAME,
                                f4l_delete_Fl_Clock );
  } F4L_CATCH( L );
  return 1;
}


static int clock_index( lua_State* L ) {
  Fl_Clock_Output* c = check_clock( L, 1 );
  size_t n = 0;
  char const* key = luaL_checklstring( L, 2, &n );
  F4L_TRY( L ) {
    if( !clock_index_( L, c, key, n ) &&
        !f4l_widget_index_( L, c, key, n ) &&
        !f4l_bad_property( L, F4L_CLOCK_OUTPUT_NAME, key ) )
      lua_pushnil( L );
  } F4L_CATCH( L );
  return 1;
}


static int clock_newindex( lua_State* L ) {
  Fl_Clock_Output* c = check_clock( L, 1 );
  size_t n = 0;
  char const* key = luaL_checklstring( L, 2, &n );
  F4L_TRY( L ) {
    (void)(clock_newindex_( L, c, key, n ) ||
           f4l_widget_newindex_( L, c, key, n ) ||
           f4l_bad_property( L, F4L_CLOCK_OUTPUT_NAME, key ));
  } F4L_CATCH( L );
  return 0;
}


static int clock_setvalue( lua_State* L ) {
  Fl_Clock_Output* c = check_clock( L, 1 );
  int h = moon_checkint( L, 2, 0, 23 );
  int m = moon_checkint( L, 3, 0, 59 );
  int s = moon_checkint( L, 4, 0, 60 );
  F4L_TRY( L ) {
    c->value( h, m, s );
  } F4L_CATCH( L );
  return 0;
}

F4L_LUA_LLINKAGE_END


F4L_DEF_CAST( Fl_Clock_Output, Fl_Widget )
F4L_DEF_CAST( Fl_Clock, Fl_Clock_Output )
F4L_DEF_CAST( Fl_Clock, Fl_Widget )


MOON_LOCAL void f4l_clock_setup( lua_State* L ) {
  luaL_Reg const methods[] = {
    F4L_WIDGET_METHODS,
    { "setvalue", clock_setvalue },
    { "__index", clock_index },
    { "__newindex", clock_newindex },
    { NULL, NULL }
  };

  moon_defobject( L, F4L_CLOCK_OUTPUT_NAME, 0, methods, 0 );
  moon_defcast( L, F4L_CLOCK_OUTPUT_NAME, F4L_WIDGET_NAME,
                f4l_cast_Fl_Clock_Output_Fl_Widget );

  moon_defobject( L, F4L_CLOCK_NAME, 0, methods, 0 );
  moon_defcast( L, F4L_CLOCK_NAME, F4L_CLOCK_OUTPUT_NAME,
                f4l_cast_Fl_Clock_Fl_Clock_Output );
  moon_defcast( L, F4L_CLOCK_NAME, F4L_WIDGET_NAME,
                f4l_cast_Fl_Clock_Fl_Widget );

  f4l_new_class_table( L, "Clock_Output", new_clock_output );
  f4l_new_class_table( L, "Clock", new_clock );
}

