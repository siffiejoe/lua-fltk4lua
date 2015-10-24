#include "fltk4lua.hxx"
#include "f4l_widget.hxx"
#include <FL/Fl_Progress.H>


namespace {

  inline Fl_Progress* check_progress( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_PROGRESS_NAME );
    return static_cast< Fl_Progress* >( p );
  }


  int progress_index_( lua_State* L, Fl_Progress* p,
                       char const* key, size_t n ) {
    using namespace std;
    switch( n ) {
      case 5:
        if( F4L_MEMCMP( key, "value", 5 ) == 0 ) {
          lua_pushnumber( L, p->value() );
          return 1;
        }
        break;
      case 7:
        if( F4L_MEMCMP( key, "maximum", 7 ) == 0 ) {
          lua_pushnumber( L, p->maximum() );
          return 1;
        } else if( F4L_MEMCMP( key, "minimum", 7 ) == 0 ) {
          lua_pushnumber( L, p->minimum() );
          return 1;
        }
        break;
    }
    return 0;
  }


  int progress_newindex_( lua_State* L, Fl_Progress* p,
                          char const* key, size_t n ) {
    using namespace std;
    switch( n ) {
      case 5:
        if( F4L_MEMCMP( key, "value", 5 ) == 0 ) {
          p->value( luaL_checknumber( L, 3 ) );
          return 1;
        }
        break;
      case 7:
        if( F4L_MEMCMP( key, "maximum", 7 ) == 0 ) {
          p->maximum( luaL_checknumber( L, 3 ) );
          return 1;
        } else if( F4L_MEMCMP( key, "minimum", 7 ) == 0 ) {
          p->minimum( luaL_checknumber( L, 3 ) );
          return 1;
        }
        break;
    }
    return 0;
  }

} // anonymous namespace


F4L_DEF_DELETE( Fl_Progress )


F4L_LUA_LLINKAGE_BEGIN

static int new_progress( lua_State* L ) {
  F4L_TRY( L ) {
    f4l_new_widget< Fl_Progress >( L, F4L_PROGRESS_NAME,
                                   f4l_delete_Fl_Progress );
  } F4L_CATCH( L );
  return 1;
}


static int progress_index( lua_State* L ) {
  Fl_Progress* p = check_progress( L, 1 );
  size_t n = 0;
  char const* key = luaL_checklstring( L, 2, &n );
  F4L_TRY( L ) {
    if( !progress_index_( L, p, key, n ) &&
        !f4l_widget_index_( L, p, key, n ) &&
        !f4l_bad_property( L, F4L_PROGRESS_NAME, key ) )
      lua_pushnil( L );
  } F4L_CATCH( L );
  return 1;
}


static int progress_newindex( lua_State* L ) {
  Fl_Progress* p = check_progress( L, 1 );
  size_t n = 0;
  char const* key = luaL_checklstring( L, 2, &n );
  F4L_TRY( L ) {
    (void)(progress_newindex_( L, p, key, n ) ||
           f4l_widget_newindex_( L, p, key, n ) ||
           f4l_bad_property( L, F4L_PROGRESS_NAME, key ));
  } F4L_CATCH( L );
  return 0;
}

F4L_LUA_LLINKAGE_END


F4L_DEF_CAST( Fl_Progress, Fl_Widget )


MOON_LOCAL void f4l_progress_setup( lua_State* L ) {
  luaL_Reg const methods[] = {
    F4L_WIDGET_METHODS,
    { "__index", progress_index },
    { "__newindex", progress_newindex },
    { NULL, NULL }
  };
  moon_defobject( L, F4L_PROGRESS_NAME, 0, methods, 0 );
  moon_defcast( L, F4L_PROGRESS_NAME, F4L_WIDGET_NAME,
                f4l_cast_Fl_Progress_Fl_Widget );
  f4l_new_class_table( L, "Progress", new_progress );
}

