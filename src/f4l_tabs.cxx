#include "fltk4lua.hxx"
#include "f4l_group.hxx"
#include "f4l_widget.hxx"
#include <FL/Fl_Tabs.H>


namespace {

  inline Fl_Tabs* check_tabs( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_TABS_NAME );
    return static_cast< Fl_Tabs* >( p );
  }

  inline Fl_Widget* check_widget( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_WIDGET_NAME );
    return static_cast< Fl_Widget* >( p );
  }


  int tabs_index_( lua_State* L, Fl_Tabs* t,
                   char const* key, size_t n ) {
    using namespace std;
    switch( n ) {
      case 4:
        if( F4L_MEMCMP( key, "push", 4 ) == 0 ) {
          f4l_push_widget( L, t->push() );
          return 1;
        }
        break;
      case 5:
        if( F4L_MEMCMP( key, "value", 5 ) == 0 ) {
          f4l_push_widget( L, t->value() );
          return 1;
        }
        break;
    }
    return 0;
  }


  int tabs_newindex_( lua_State* L, Fl_Tabs* t,
                      char const* key, size_t n ) {
    using namespace std;
    switch( n ) {
      case 4:
        if( F4L_MEMCMP( key, "push", 4 ) == 0 ) {
          Fl_Widget* w = check_widget( L, 3 );
          lua_settop( L, 3 );
          moon_setuvfield( L, 1, "push" );
          t->push( w );
          return 1;
        }
        break;
      case 5:
        if( F4L_MEMCMP( key, "value", 5 ) == 0 ) {
          t->value( check_widget( L, 3 ) );
          return 1;
        }
        break;
    }
    return 0;
  }

} // anonymous namespace


F4L_DEF_DELETE( Fl_Tabs )


F4L_LUA_LLINKAGE_BEGIN

static int new_tabs( lua_State* L ) {
  F4L_TRY( L ) {
    f4l_new_widget< Fl_Tabs >( L, F4L_TABS_NAME,
                               f4l_delete_Fl_Tabs );
  } F4L_CATCH( L );
  return 1;
}


static int tabs_index( lua_State* L ) {
  Fl_Tabs* t = check_tabs( L, 1 );
  size_t n = 0;
  char const* key = luaL_checklstring( L, 2, &n );
  F4L_TRY( L ) {
    if( !tabs_index_( L, t, key, n ) &&
        !f4l_group_index_( L, t, key, n ) &&
        !f4l_widget_index_( L, t, key, n ) &&
        !f4l_bad_property( L, F4L_TABS_NAME, key ) )
      lua_pushnil( L );
  } F4L_CATCH( L );
  return 1;
}


static int tabs_newindex( lua_State* L ) {
  Fl_Tabs* t = check_tabs( L, 1 );
  size_t n = 0;
  char const* key = luaL_checklstring( L, 2, &n );
  F4L_TRY( L ) {
    (void)(tabs_newindex_( L, t, key, n ) ||
           f4l_group_newindex_( L, t, key, n ) ||
           f4l_widget_newindex_( L, t, key, n ) ||
           f4l_bad_property( L, F4L_TABS_NAME, key ));
  } F4L_CATCH( L );
  return 0;
}


static int tabs_client_area( lua_State* L ) {
  Fl_Tabs* t = check_tabs( L, 1 );
  int tabh = moon_optint( L, 2, INT_MIN, INT_MAX, 0 );
  int rx, ry, rw, rh;
  F4L_TRY( L ) {
    t->client_area( rx, ry, rw, rh, tabh );
    lua_pushinteger( L, rx );
    lua_pushinteger( L, ry );
    lua_pushinteger( L, rw );
    lua_pushinteger( L, rh );
  } F4L_CATCH( L );
  return 4;
}

F4L_LUA_LLINKAGE_END


F4L_DEF_CAST( Fl_Tabs, Fl_Group )
F4L_DEF_CAST( Fl_Tabs, Fl_Widget )


MOON_LOCAL void f4l_tabs_setup( lua_State* L ) {
  luaL_Reg const methods[] = {
    F4L_WIDGET_METHODS,
    F4L_GROUP_METHODS,
    { "client_area", tabs_client_area },
    { "__index", tabs_index },
    { "__newindex", tabs_newindex },
    { NULL, NULL }
  };
  moon_defobject( L, F4L_TABS_NAME, 0, methods, 0 );
  moon_defcast( L, F4L_TABS_NAME, F4L_GROUP_NAME,
                f4l_cast_Fl_Tabs_Fl_Group );
  moon_defcast( L, F4L_TABS_NAME, F4L_WIDGET_NAME,
                f4l_cast_Fl_Tabs_Fl_Widget );
  f4l_new_class_table( L, "Tabs", new_tabs );
}

