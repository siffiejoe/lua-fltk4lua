#include "fltk4lua.hxx"
#include "f4l_valuator.hxx"
#include "f4l_widget.hxx"
#include "f4l_enums.hxx"
#include <FL/Fl_Dial.H>
#include <cstring>
#include <climits>


#define TYPE_LIST( _ ) \
  _( "FL_NORMAL_DIAL", FL_NORMAL_DIAL ) \
  _( "FL_FILL_DIAL", FL_FILL_DIAL ) \
  _( "FL_LINE_DIAL", FL_LINE_DIAL )

  F4L_GEN_TYPE_ENUM( TYPE_LIST, dial )


namespace {

  inline Fl_Dial* check_dial( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_DIAL_NAME );
    return static_cast< Fl_Dial* >( p );
  }


  int dial_index_( lua_State* L, Fl_Dial* d,
                   char const* key, size_t n ) {
    using namespace std;
    switch( n ) {
      case 4:
        if( F4L_MEMCMP( key, "type", 4 ) == 0 ){
          f4l_push_type_dial( L, d->type() );
          return 1;
        }
        break;
      case 6:
        if( F4L_MEMCMP( key, "angle1", 6 ) == 0 ) {
          lua_pushinteger( L, d->angle1() );
          return 1;
        } else if( F4L_MEMCMP( key, "angle2", 6 ) == 0 ) {
          lua_pushinteger( L, d->angle2() );
          return 1;
        }
        break;
    }
    return 0;
  }


  int dial_newindex_( lua_State* L, Fl_Dial* d,
                      char const* key, size_t n ) {
    using namespace std;
    switch( n ) {
      case 4:
        if( F4L_MEMCMP( key, "type", 4 ) == 0 ){
          d->type( f4l_check_type_dial( L, 3 ) );
          return 1;
        }
        break;
      case 6:
        if( F4L_MEMCMP( key, "angle1", 6 ) == 0 ) {
          d->angle1( moon_checkint( L, 3, SHRT_MIN, SHRT_MAX ) );
          return 1;
        } else if( F4L_MEMCMP( key, "angle2", 6 ) == 0 ) {
          d->angle2( moon_checkint( L, 3, SHRT_MIN, SHRT_MAX ) );
          return 1;
        }
        break;
    }
    return 0;
  }

} // anonymous namespace


F4L_DEF_DELETE( Fl_Dial )


F4L_LUA_LLINKAGE_BEGIN

static int new_dial( lua_State* L ) {
  F4L_TRY( L ) {
    f4l_new_widget< Fl_Dial>( L, F4L_DIAL_NAME,
                              f4l_delete_Fl_Dial );
  } F4L_CATCH( L );
  return 1;
}


static int dial_index( lua_State* L ) {
  Fl_Dial* d = check_dial( L, 1 );
  size_t n = 0;
  char const* key = luaL_checklstring( L, 2, &n );
  F4L_TRY( L ) {
    if( !dial_index_( L, d, key, n ) &&
        !f4l_valuator_index_( L, d, key, n ) &&
        !f4l_widget_index_( L, d, key, n ) &&
        !f4l_bad_property( L, F4L_DIAL_NAME, key ) )
      lua_pushnil( L );
  } F4L_CATCH( L );
  return 1;
}


static int dial_newindex( lua_State* L ) {
  Fl_Dial* d = check_dial( L, 1 );
  size_t n = 0;
  char const* key = luaL_checklstring( L, 2, &n );
  F4L_TRY( L ) {
    (void)(dial_newindex_( L, d, key, n ) ||
           f4l_valuator_newindex_( L, d, key, n ) ||
           f4l_widget_newindex_( L, d, key, n ) ||
           f4l_bad_property( L, F4L_DIAL_NAME, key ));
  } F4L_CATCH( L );
  return 0;
}


static int dial_angles( lua_State* L ) {
  Fl_Dial* d = check_dial( L, 1 );
  short a = moon_checkint( L, 2, SHRT_MIN, SHRT_MAX );
  short b = moon_checkint( L, 3, SHRT_MIN, SHRT_MAX );
  F4L_TRY( L ) {
    d->angles( a, b );
  } F4L_CATCH( L );
  return 0;
}

F4L_LUA_LLINKAGE_END


F4L_DEF_CAST( Fl_Dial, Fl_Valuator )
F4L_DEF_CAST( Fl_Dial, Fl_Widget )


MOON_LOCAL void f4l_dial_setup( lua_State* L ) {
  luaL_Reg const methods[] = {
    F4L_WIDGET_METHODS,
    F4L_VALUATOR_METHODS,
    { "angles", dial_angles },
    { "__index", dial_index },
    { "__newindex", dial_newindex },
    { NULL, NULL }
  };
  moon_defobject( L, F4L_DIAL_NAME, 0, methods, 0 );
  moon_defcast( L, F4L_DIAL_NAME, F4L_VALUATOR_NAME,
                f4l_cast_Fl_Dial_Fl_Valuator );
  moon_defcast( L, F4L_DIAL_NAME, F4L_WIDGET_NAME,
                f4l_cast_Fl_Dial_Fl_Widget );
  f4l_new_class_table( L, "Dial", new_dial );
}

