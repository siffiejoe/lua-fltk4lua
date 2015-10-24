#include "fltk4lua.hxx"
#include "f4l_browserx.hxx"
#include "f4l_widget.hxx"
#include <FL/Fl_Check_Browser.H>
#include <cstring>
#include <climits>


namespace {

  inline Fl_Check_Browser* check_check_browser( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_CHECK_BROWSER_NAME );
    return static_cast< Fl_Check_Browser* >( p );
  }


  int check_browser_index_( lua_State* L, Fl_Check_Browser* b,
                            char const* key, size_t n ) {
    using namespace std;
    switch( n ) {
      case 5:
        if( F4L_MEMCMP( key, "value", 5 ) == 0 ) {
          lua_pushinteger( L, b->value() );
          return 1;
        }
        break;
      case 6:
        if( F4L_MEMCMP( key, "nitems", 6 ) == 0 ) {
          lua_pushinteger( L, b->nitems() );
          return 1;
        }
        break;
      case 8:
        if( F4L_MEMCMP( key, "nchecked", 8 ) == 0 ) {
          lua_pushinteger( L, b->nchecked() );
          return 1;
        }
        break;
    }
    return 0;
  }

} // anonymous namespace


F4L_DEF_DELETE( Fl_Check_Browser )


F4L_LUA_LLINKAGE_BEGIN

static int new_check_browser( lua_State* L ) {
  F4L_TRY( L ) {
    f4l_new_widget< Fl_Check_Browser >( L, F4L_CHECK_BROWSER_NAME,
                                        f4l_delete_Fl_Check_Browser );
  } F4L_CATCH( L );
  return 1;
}


static int check_browser_index( lua_State* L ) {
  Fl_Check_Browser* b = check_check_browser( L, 1 );
  size_t n = 0;
  char const* key = luaL_checklstring( L, 2, &n );
  F4L_TRY( L ) {
    if( !check_browser_index_( L, b, key, n ) &&
        !f4l_browserx_index_( L, b, key, n ) &&
        !f4l_widget_index_( L, b, key, n ) &&
        !f4l_bad_property( L, F4L_CHECK_BROWSER_NAME, key ) )
      lua_pushnil( L );
  } F4L_CATCH( L );
  return 1;
}


static int check_browser_newindex( lua_State* L ) {
  Fl_Check_Browser* b = check_check_browser( L, 1 );
  size_t n = 0;
  char const* key = luaL_checklstring( L, 2, &n );
  F4L_TRY( L ) {
    (void)(f4l_browserx_newindex_( L, b, key, n ) ||
           f4l_widget_newindex_( L, b, key, n ) ||
           f4l_bad_property( L, F4L_CHECK_BROWSER_NAME, key ));
  } F4L_CATCH( L );
  return 0;
}


static int check_browser_add( lua_State* L ) {
  Fl_Check_Browser* b = check_check_browser( L, 1 );
  char const* s = luaL_optstring( L, 2, NULL );
  F4L_TRY( L ) {
    lua_pushinteger( L, b->add( s, lua_toboolean( L, 3 ) ) );
  } F4L_CATCH( L );
  return 1;
}


static int check_browser_check_all( lua_State* L ) {
  Fl_Check_Browser* b = check_check_browser( L, 1 );
  F4L_TRY( L ) {
    b->check_all();
  } F4L_CATCH( L );
  return 0;
}


static int check_browser_check_none( lua_State* L ) {
  Fl_Check_Browser* b = check_check_browser( L, 1 );
  F4L_TRY( L ) {
    b->check_none();
  } F4L_CATCH( L );
  return 0;
}


static int check_browser_checked( lua_State* L ) {
  Fl_Check_Browser* b = check_check_browser( L, 1 );
  int i = moon_checkint( L, 2, 1, INT_MAX );
  F4L_TRY( L ) {
    int nitems = b->nitems();
    luaL_argcheck( L, i <= nitems, 2, "index too large" );
    if( lua_gettop( L ) > 2 ) {
      b->checked( i, lua_toboolean( L, 3 ) );
      return 0;
    } else {
      lua_pushboolean( L, b->checked( i ) );
      return 1;
    }
  } F4L_CATCH( L );
  return 0;
}


static int check_browser_clear( lua_State* L ) {
  Fl_Check_Browser* b = check_check_browser( L, 1 );
  F4L_TRY( L ) {
    b->clear();
  } F4L_CATCH( L );
  return 0;
}


static int check_browser_remove( lua_State* L ) {
  Fl_Check_Browser* b = check_check_browser( L, 1 );
  int i = moon_checkint( L, 2, 1, INT_MAX );
  F4L_TRY( L ) {
    int nitems = b->nitems();
    luaL_argcheck( L, i <= nitems, 2, "index too large" );
    lua_pushinteger( L, b->remove( i ) );
  } F4L_CATCH( L );
  return 1;
}


static int check_browser_set_checked( lua_State* L ) {
  Fl_Check_Browser* b = check_check_browser( L, 1 );
  int i = moon_checkint( L, 2, 1, INT_MAX );
  F4L_TRY( L ) {
    int nitems = b->nitems();
    luaL_argcheck( L, i <= nitems, 2, "index too large" );
    b->set_checked( i );
  } F4L_CATCH( L );
  return 0;
}


static int check_browser_text( lua_State* L ) {
  Fl_Check_Browser* b = check_check_browser( L, 1 );
  int i = moon_checkint( L, 2, 1, INT_MAX );
  F4L_TRY( L ) {
    int nitems = b->nitems();
    luaL_argcheck( L, i <= nitems, 2, "index too large" );
    char const* t = b->text( i );
    if( t != NULL )
      lua_pushstring( L, t );
    else
      lua_pushnil( L );
  } F4L_CATCH( L );
  return 1;
}

F4L_LUA_LLINKAGE_END


F4L_DEF_CAST( Fl_Check_Browser, Fl_Browser_ )
F4L_DEF_CAST( Fl_Check_Browser, Fl_Widget )


MOON_LOCAL void f4l_check_browser_setup( lua_State* L ) {
  luaL_Reg const methods[] = {
    F4L_WIDGET_METHODS,
    F4L_BROWSERX_METHODS,
    { "add", check_browser_add },
    { "check_all", check_browser_check_all },
    { "check_none", check_browser_check_none },
    { "checked", check_browser_checked },
    { "clear", check_browser_clear },
    { "remove", check_browser_remove },
    { "set_checked", check_browser_set_checked },
    { "text", check_browser_text },
    { "__index", check_browser_index },
    { "__newindex", check_browser_newindex },
    { NULL, NULL }
  };
  moon_defobject( L, F4L_CHECK_BROWSER_NAME, 0, methods, 0 );
  moon_defcast( L, F4L_CHECK_BROWSER_NAME, F4L_BROWSERX_NAME,
                f4l_cast_Fl_Check_Browser_Fl_Browser_ );
  moon_defcast( L, F4L_CHECK_BROWSER_NAME, F4L_WIDGET_NAME,
                f4l_cast_Fl_Check_Browser_Fl_Widget );
  f4l_new_class_table( L, "Check_Browser", new_check_browser );
}

