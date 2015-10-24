#include "fltk4lua.hxx"
#include "f4l_menu.hxx"
#include "f4l_widget.hxx"
#include <FL/Fl_Menu_Bar.H>


namespace {

  inline Fl_Menu_Bar* check_menu_bar( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_MENU_BAR_NAME );
    return static_cast< Fl_Menu_Bar* >( p );
  }

} // anonymous namespace


F4L_DEF_DELETE( Fl_Menu_Bar )


F4L_LUA_LLINKAGE_BEGIN

static int new_menu_bar( lua_State* L ) {
  F4L_TRY( L ) {
    f4l_new_widget< Fl_Menu_Bar >( L, F4L_MENU_BAR_NAME,
                                   f4l_delete_Fl_Menu_Bar );
  } F4L_CATCH( L );
  return 1;
}


static int menu_bar_index( lua_State* L ) {
  Fl_Menu_Bar* mb = check_menu_bar( L, 1 );
  size_t n = 0;
  char const* key = luaL_checklstring( L, 2, &n );
  F4L_TRY( L ) {
    if( !f4l_menu_index_( L, mb, key, n ) &&
        !f4l_widget_index_( L, mb, key, n ) &&
        !f4l_bad_property( L, F4L_MENU_BAR_NAME, key ) )
      lua_pushnil( L );
  } F4L_CATCH( L );
  return 1;
}


static int menu_bar_newindex( lua_State* L ) {
  Fl_Menu_Bar* mb = check_menu_bar( L, 1 );
  size_t n = 0;
  char const* key = luaL_checklstring( L, 2, &n );
  F4L_TRY( L ) {
    (void)(f4l_menu_newindex_( L, mb, key, n ) ||
           f4l_widget_newindex_( L, mb, key, n ) ||
           f4l_bad_property( L, F4L_MENU_BAR_NAME, key ));
  } F4L_CATCH( L );
  return 0;
}

F4L_LUA_LLINKAGE_END


F4L_DEF_CAST( Fl_Menu_Bar, Fl_Menu_ )
F4L_DEF_CAST( Fl_Menu_Bar, Fl_Widget )


MOON_LOCAL void f4l_menu_bar_setup( lua_State* L ) {
  luaL_Reg const methods[] = {
    F4L_WIDGET_METHODS,
    F4L_MENU_METHODS,
    { "__index", menu_bar_index },
    { "__newindex", menu_bar_newindex },
    { NULL, NULL }
  };
  moon_defobject( L, F4L_MENU_BAR_NAME, 0, methods, 0 );
  moon_defcast( L, F4L_MENU_BAR_NAME, F4L_MENU_NAME,
                f4l_cast_Fl_Menu_Bar_Fl_Menu_ );
  moon_defcast( L, F4L_MENU_BAR_NAME, F4L_WIDGET_NAME,
                f4l_cast_Fl_Menu_Bar_Fl_Widget );
  f4l_new_class_table( L, "Menu_Bar", new_menu_bar );
}

