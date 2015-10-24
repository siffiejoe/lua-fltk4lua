#include "fltk4lua.hxx"
#include "f4l_valuator.hxx"
#include "f4l_widget.hxx"
#include "f4l_enums.hxx"
#include <cstring>
#include <climits>


#define TYPE_LIST( _ ) \
  _( "FL_VERTICAL", FL_VERTICAL ) \
  _( "FL_HORIZONTAL", FL_HORIZONTAL )

  F4L_GEN_TYPE_ENUM( TYPE_LIST, valuator )


namespace {

  inline Fl_Valuator* check_valuator( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_VALUATOR_NAME );
    return static_cast< Fl_Valuator* >( p );
  }

} // anonymous namespace


MOON_LOCAL int f4l_valuator_index_( lua_State* L, Fl_Valuator* v,
                                    char const* key, size_t n ) {
  using namespace std;
  switch( n ) {
    case 4:
      if( F4L_MEMCMP( key, "step", 4 ) == 0 ) {
        lua_pushnumber( L, v->step() );
        return 1;
      }
      break;
    case 5:
      if( F4L_MEMCMP( key, "value", 5 ) == 0 ) {
        lua_pushnumber( L, v->value() );
        return 1;
      }
      break;
    case 7:
      if( F4L_MEMCMP( key, "maximum", 7 ) == 0 ) {
        lua_pushnumber( L, v->maximum() );
        return 1;
      } else if( F4L_MEMCMP( key, "minimum", 7 ) == 0 ) {
        lua_pushnumber( L, v->minimum() );
        return 1;
      }
      break;
  }
  return 0;
}


MOON_LOCAL int f4l_valuator_newindex_( lua_State* L, Fl_Valuator* v,
                                       char const* key, size_t n ) {
  using namespace std;
  switch( n ) {
    case 4:
      if( F4L_MEMCMP( key, "step", 4 ) == 0 ) {
        v->step( luaL_checknumber( L, 3 ) );
        return 1;
      }
      break;
    case 5:
      if( F4L_MEMCMP( key, "value", 5 ) == 0 ) {
        v->value( luaL_checknumber( L, 3 ) );
        return 1;
      }
      break;
    case 7:
      if( F4L_MEMCMP( key, "maximum", 7 ) == 0 ) {
        v->maximum( luaL_checknumber( L, 3 ) );
        return 1;
      } else if( F4L_MEMCMP( key, "minimum", 7 ) == 0 ) {
        v->minimum( luaL_checknumber( L, 3 ) );
        return 1;
      }
      break;
    case 9:
      if( F4L_MEMCMP( key, "precision", 9 ) == 0 ) {
        v->precision( moon_checkint( L, 3, 0, INT_MAX ) );
        return 1;
      }
      break;
  }
  return 0;
}


F4L_LUA_LLINKAGE_BEGIN

MOON_LOCAL int f4l_valuator_bounds( lua_State* L ) {
  Fl_Valuator* v = check_valuator( L, 1 );
  double a = luaL_checknumber( L, 2 );
  double b = luaL_checknumber( L, 3 );
  F4L_TRY( L ) {
    v->bounds( a, b );
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_valuator_clamp( lua_State* L ) {
  Fl_Valuator* v = check_valuator( L, 1 );
  double a = luaL_checknumber( L, 2 );
  F4L_TRY( L ) {
    lua_pushnumber( L, v->clamp( a ) );
  } F4L_CATCH( L );
  return 1;
}


MOON_LOCAL int f4l_valuator_format( lua_State* L ) {
  Fl_Valuator* v = check_valuator( L, 1 );
  char buffer[ 128 ];
  F4L_TRY( L ) {
    lua_pushlstring( L, buffer, v->format( buffer ) );
  } F4L_CATCH( L );
  return 1;
}


MOON_LOCAL int f4l_valuator_increment( lua_State* L ) {
  Fl_Valuator* v = check_valuator( L, 1 );
  double a = luaL_checknumber( L, 2 );
  int b = moon_checkint( L, 3, 1, INT_MAX );
  F4L_TRY( L ) {
    lua_pushnumber( L, v->increment( a, b ) );
  } F4L_CATCH( L );
  return 1;
}


MOON_LOCAL int f4l_valuator_range( lua_State* L ) {
  Fl_Valuator* v = check_valuator( L, 1 );
  double a = luaL_checknumber( L, 2 );
  double b = luaL_checknumber( L, 3 );
  F4L_TRY( L ) {
    v->range( a, b );
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_valuator_round( lua_State* L ) {
  Fl_Valuator* v = check_valuator( L, 1 );
  double a = luaL_checknumber( L, 2 );
  F4L_TRY( L ) {
    lua_pushnumber( L, v->round( a ) );
  } F4L_CATCH( L );
  return 1;
}

F4L_LUA_LLINKAGE_END

