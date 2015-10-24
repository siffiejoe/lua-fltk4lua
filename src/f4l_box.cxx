#include "fltk4lua.hxx"
#include "f4l_widget.hxx"
#include <FL/Fl_Box.H>


namespace {

  inline Fl_Box* check_box( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_BOX_NAME );
    return static_cast< Fl_Box* >( p );
  }

} // anonymous namespace


F4L_DEF_DELETE( Fl_Box )


F4L_LUA_LLINKAGE_BEGIN

static int new_box( lua_State* L ) {
  F4L_TRY( L ) {
    f4l_new_widget< Fl_Box >( L, F4L_BOX_NAME,
                              f4l_delete_Fl_Box );
  } F4L_CATCH( L );
  return 1;
}


static int box_index( lua_State* L ) {
  Fl_Box* b = check_box( L, 1 );
  size_t n = 0;
  char const* key = luaL_checklstring( L, 2, &n );
  F4L_TRY( L ) {
    if( !f4l_widget_index_( L, b, key, n ) &&
        !f4l_bad_property( L, F4L_BOX_NAME, key ) )
      lua_pushnil( L );
  } F4L_CATCH( L );
  return 1;
}


static int box_newindex( lua_State* L ) {
  Fl_Box* b = check_box( L, 1 );
  size_t n = 0;
  char const* key = luaL_checklstring( L, 2, &n );
  F4L_TRY( L ) {
    (void)(f4l_widget_newindex_( L, b, key, n ) ||
           f4l_bad_property( L, F4L_BOX_NAME, key ));
  } F4L_CATCH( L );
  return 0;
}

F4L_LUA_LLINKAGE_END


F4L_DEF_CAST( Fl_Box, Fl_Widget )


MOON_LOCAL void f4l_box_setup( lua_State* L ) {
  luaL_Reg const methods[] = {
    F4L_WIDGET_METHODS,
    { "__index", box_index },
    { "__newindex", box_newindex },
    { NULL, NULL }
  };
  moon_defobject( L, F4L_BOX_NAME, 0, methods, 0 );
  moon_defcast( L, F4L_BOX_NAME, F4L_WIDGET_NAME,
                f4l_cast_Fl_Box_Fl_Widget );
  f4l_new_class_table( L, "Box", new_box );
}

