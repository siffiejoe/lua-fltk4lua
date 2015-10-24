#include "fltk4lua.hxx"
#include "f4l_menu.hxx"
#include "f4l_widget.hxx"
#include <FL/Fl_Choice.H>


namespace {

  inline Fl_Choice* check_choice( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_CHOICE_NAME );
    return static_cast< Fl_Choice* >( p );
  }


  int choice_index_( lua_State* L, Fl_Choice* c,
                     char const* key, size_t n ) {
    using namespace std;
    if( n == 5 && F4L_MEMCMP( key, "value", 5 ) == 0 ) {
      lua_pushinteger( L, c->value() );
      return 1;
    }
    return 0;
  }


  int choice_newindex_( lua_State* L, Fl_Choice* c,
                        char const* key, size_t n ) {
    using namespace std;
    if( n == 5 && F4L_MEMCMP( key, "value", 5 ) == 0 ) {
      int v = moon_checkint( L, 3, 0, INT_MAX );
      int sz = c->size();
      luaL_argcheck( L, v < sz, 3, "index too large" );
      c->value( v );
      return 1;
    }
    return 0;
  }

} // anonymous namespace


F4L_DEF_DELETE( Fl_Choice )


F4L_LUA_LLINKAGE_BEGIN

static int new_choice( lua_State* L ) {
  F4L_TRY( L ) {
    f4l_new_widget< Fl_Choice >( L, F4L_CHOICE_NAME,
                                 f4l_delete_Fl_Choice );
  } F4L_CATCH( L );
  return 1;
}


static int choice_index( lua_State* L ) {
  Fl_Choice* c = check_choice( L, 1 );
  size_t n = 0;
  char const* key = luaL_checklstring( L, 2, &n );
  F4L_TRY( L ) {
    if( !choice_index_( L, c, key, n ) &&
        !f4l_menu_index_( L, c, key, n ) &&
        !f4l_widget_index_( L, c, key, n ) &&
        !f4l_bad_property( L, F4L_CHOICE_NAME, key ) )
      lua_pushnil( L );
  } F4L_CATCH( L );
  return 1;
}


static int choice_newindex( lua_State* L ) {
  Fl_Choice* c = check_choice( L, 1 );
  size_t n = 0;
  char const* key = luaL_checklstring( L, 2, &n );
  F4L_TRY( L ) {
    (void)(choice_newindex_( L, c, key, n ) ||
           f4l_menu_newindex_( L, c, key, n ) ||
           f4l_widget_newindex_( L, c, key, n ) ||
           f4l_bad_property( L, F4L_CHOICE_NAME, key ));
  } F4L_CATCH( L );
  return 0;
}

F4L_LUA_LLINKAGE_END


F4L_DEF_CAST( Fl_Choice, Fl_Menu_ )
F4L_DEF_CAST( Fl_Choice, Fl_Widget )


MOON_LOCAL void f4l_choice_setup( lua_State* L ) {
  luaL_Reg const methods[] = {
    F4L_WIDGET_METHODS,
    F4L_MENU_METHODS,
    { "__index", choice_index },
    { "__newindex", choice_newindex },
    { NULL, NULL }
  };
  moon_defobject( L, F4L_CHOICE_NAME, 0, methods, 0 );
  moon_defcast( L, F4L_CHOICE_NAME, F4L_MENU_NAME,
                f4l_cast_Fl_Choice_Fl_Menu_ );
  moon_defcast( L, F4L_CHOICE_NAME, F4L_WIDGET_NAME,
                f4l_cast_Fl_Choice_Fl_Widget );
  f4l_new_class_table( L, "Choice", new_choice );
}

