#include "fltk4lua.hxx"
#include "f4l_valuator.hxx"
#include "f4l_widget.hxx"
#include <FL/Fl_Roller.H>


namespace {

  inline Fl_Roller* check_roller( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_ROLLER_NAME );
    return static_cast< Fl_Roller* >( p );
  }


  int roller_index_( lua_State* L, Fl_Roller* r,
                     char const* key, size_t n ) {
    if( n == 4 && F4L_MEMCMP( key, "type", 4 ) == 0 ) {
      f4l_push_type_valuator( L, r->type() );
      return 1;
    }
    return 0;
  }


  int roller_newindex_( lua_State* L, Fl_Roller* r,
                        char const* key, size_t n ) {
    if( n == 4 && F4L_MEMCMP( key, "type", 4 ) == 0 ) {
      r->type( f4l_check_type_valuator( L, 3 ) );
      return 1;
    }
    return 0;
  }

} // anonymous namespace


F4L_DEF_DELETE( Fl_Roller )


F4L_LUA_LLINKAGE_BEGIN

static int new_roller( lua_State* L ) {
  F4L_TRY( L ) {
    f4l_new_widget< Fl_Roller>( L, F4L_ROLLER_NAME,
                                f4l_delete_Fl_Roller );
  } F4L_CATCH( L );
  return 1;
}


static int roller_index( lua_State* L ) {
  Fl_Roller* r = check_roller( L, 1 );
  size_t n = 0;
  char const* key = luaL_checklstring( L, 2, &n );
  F4L_TRY( L ) {
    if( !roller_index_( L, r, key, n ) &&
        !f4l_valuator_index_( L, r, key, n ) &&
        !f4l_widget_index_( L, r, key, n ) &&
        !f4l_bad_property( L, F4L_ROLLER_NAME, key ) )
      lua_pushnil( L );
  } F4L_CATCH( L );
  return 1;
}


static int roller_newindex( lua_State* L ) {
  Fl_Roller* r = check_roller( L, 1 );
  size_t n = 0;
  char const* key = luaL_checklstring( L, 2, &n );
  F4L_TRY( L ) {
    (void)(roller_newindex_( L, r, key, n ) ||
           f4l_valuator_newindex_( L, r, key, n ) ||
           f4l_widget_newindex_( L, r, key, n ) ||
           f4l_bad_property( L, F4L_ROLLER_NAME, key ));
  } F4L_CATCH( L );
  return 0;
}

F4L_LUA_LLINKAGE_END


F4L_DEF_CAST( Fl_Roller, Fl_Valuator )
F4L_DEF_CAST( Fl_Roller, Fl_Widget )


MOON_LOCAL void f4l_roller_setup( lua_State* L ) {
  luaL_Reg const methods[] = {
    F4L_WIDGET_METHODS,
    F4L_VALUATOR_METHODS,
    { "__index", roller_index },
    { "__newindex", roller_newindex },
    { NULL, NULL }
  };
  moon_defobject( L, F4L_ROLLER_NAME, 0, methods, 0 );
  moon_defcast( L, F4L_ROLLER_NAME, F4L_VALUATOR_NAME,
                f4l_cast_Fl_Roller_Fl_Valuator );
  moon_defcast( L, F4L_ROLLER_NAME, F4L_WIDGET_NAME,
                f4l_cast_Fl_Roller_Fl_Widget );
  f4l_new_class_table( L, "Roller", new_roller );
}

