#include "fltk4lua.hxx"
#include "f4l_browser.hxx"
#include "f4l_browserx.hxx"
#include "f4l_widget.hxx"
#include "f4l_enums.hxx"
#include <cstring>
#include <climits>


#define TYPE_LIST( _ ) \
  _( "FL_NORMAL_BROWSER", FL_NORMAL_BROWSER ) \
  _( "FL_SELECT_BROWSER", FL_SELECT_BROWSER ) \
  _( "FL_HOLD_BROWSER", FL_HOLD_BROWSER ) \
  _( "FL_MULTI_BROWSER", FL_MULTI_BROWSER )

  F4L_GEN_TYPE_ENUM( TYPE_LIST, browser )


namespace {

  inline Fl_Browser* check_browser( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_BROWSER_NAME );
    return static_cast< Fl_Browser* >( p );
  }

} // anonymous namespace


F4L_DEF_DELETE( Fl_Browser )


F4L_LUA_LLINKAGE_BEGIN

static int new_browser( lua_State* L ) {
  F4L_TRY( L ) {
    f4l_new_widget< Fl_Browser >( L, F4L_BROWSER_NAME,
                                  f4l_delete_Fl_Browser );
  } F4L_CATCH( L );
  return 1;
}


static int browser_index( lua_State* L ) {
  Fl_Browser* b = check_browser( L, 1 );
  size_t n = 0;
  char const* key = luaL_checklstring( L, 2, &n );
  F4L_TRY( L ) {
    if( !f4l_browser_index_( L, b, key, n ) &&
        !f4l_browserx_index_( L, b, key, n ) &&
        !f4l_widget_index_( L, b, key, n ) &&
        !f4l_bad_property( L, F4L_BROWSER_NAME, key ) )
      lua_pushnil( L );
  } F4L_CATCH( L );
  return 1;
}


static int browser_newindex( lua_State* L ) {
  Fl_Browser* b = check_browser( L, 1 );
  size_t n = 0;
  char const* key = luaL_checklstring( L, 2, &n );
  F4L_TRY( L ) {
    (void)(f4l_browser_newindex_( L, b, key, n ) ||
           f4l_browserx_newindex_( L, b, key, n ) ||
           f4l_widget_newindex_( L, b, key, n ) ||
           f4l_bad_property( L, F4L_BROWSER_NAME, key ));
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_browser_add( lua_State* L ) {
  Fl_Browser* b = check_browser( L, 1 );
  char const* s = luaL_optstring( L, 2, NULL );
  F4L_TRY( L ) {
    b->add( s );
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_browser_clear( lua_State* L ) {
  Fl_Browser* b = check_browser( L, 1 );
  F4L_TRY( L ) {
    b->clear();
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_browser_displayed( lua_State* L ) {
  Fl_Browser* b = check_browser( L, 1 );
  int line = moon_checkint( L, 2, 1, INT_MAX );
  F4L_TRY( L ) {
    luaL_argcheck( L, line <= b->size(), 2, "index too large" );
    lua_pushboolean( L, b->displayed( line ) );
  } F4L_CATCH( L );
  return 1;
}


MOON_LOCAL int f4l_browser_hide( lua_State* L ) {
  Fl_Browser* b = check_browser( L, 1 );
  F4L_TRY( L ) {
    if( lua_gettop( L ) > 1 ) {
      int line = moon_checkint( L, 2, 1, INT_MAX );
      luaL_argcheck( L, line <= b->size(), 2, "index too large" );
      b->hide( line );
    } else
      b->hide();
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_browser_insert( lua_State* L ) {
  Fl_Browser* b = check_browser( L, 1 );
  int line = moon_checkint( L, 2, INT_MIN, INT_MAX );
  char const* s = luaL_optstring( L, 2, NULL );
  F4L_TRY( L ) {
    b->insert( line, s );
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_browser_load( lua_State* L ) {
  Fl_Browser* b = check_browser( L, 1 );
  char const* fname = luaL_checkstring( L, 2 );
  F4L_TRY( L ) {
    return luaL_fileresult( L, b->load( fname ), fname );
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_browser_make_visible( lua_State* L ) {
  Fl_Browser* b = check_browser( L, 1 );
  int line = moon_checkint( L, 2, INT_MIN, INT_MAX );
  F4L_TRY( L ) {
    b->make_visible( line );
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_browser_move( lua_State* L ) {
  Fl_Browser* b = check_browser( L, 1 );
  F4L_TRY( L ) {
    int nitems = b->size();
    int line1 = moon_checkint( L, 2, INT_MIN, INT_MAX );
    int line2 = moon_checkint( L, 3, 1, INT_MAX );
    luaL_argcheck( L, line2 <= nitems, 3, "index too large" );
    b->move( line1, line2 );
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_browser_remove( lua_State* L ) {
  Fl_Browser* b = check_browser( L, 1 );
  int line = moon_checkint( L, 2, 1, INT_MAX );
  F4L_TRY( L ) {
    luaL_argcheck( L, line <= b->size(), 2, "index too large" );
    b->remove( line );
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_browser_select( lua_State* L ) {
  Fl_Browser* b = check_browser( L, 1 );
  int line = moon_checkint( L, 2, 1, INT_MAX );
  F4L_TRY( L ) {
    luaL_argcheck( L, line <= b->size(), 2, "index too large" );
    int v = luaL_opt( L, lua_toboolean, 3, 1 );
    lua_pushboolean( L, b->select( line, v ) );
  } F4L_CATCH( L );
  return 1;
}


MOON_LOCAL int f4l_browser_selected( lua_State* L ) {
  Fl_Browser* b = check_browser( L, 1 );
  int line = moon_checkint( L, 2, 1, INT_MAX );
  F4L_TRY( L ) {
    luaL_argcheck( L, line <= b->size(), 2, "index too large" );
    lua_pushboolean( L, b->selected( line ) );
  } F4L_CATCH( L );
  return 1;
}


MOON_LOCAL int f4l_browser_show( lua_State* L ) {
  Fl_Browser* b = check_browser( L, 1 );
  F4L_TRY( L ) {
    if( lua_gettop( L ) > 1 ) {
      int line = moon_checkint( L, 2, 1, INT_MAX );
      luaL_argcheck( L, line <= b->size(), 2, "index too large" );
      b->show( line );
    } else
      b->show();
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_browser_size( lua_State* L ) {
  Fl_Browser* b = check_browser( L, 1 );
  int w = moon_checkint( L, 2, 0, INT_MAX );
  int h = moon_checkint( L, 3, 0, INT_MAX );
  F4L_TRY( L ) {
    b->size( w, h );
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_browser_swap( lua_State* L ) {
  Fl_Browser* b = check_browser( L, 1 );
  F4L_TRY( L ) {
    int nitems = b->size();
    int line1 = moon_checkint( L, 2, 1, INT_MAX );
    luaL_argcheck( L, line1 <= nitems, 2, "index too large" );
    int line2 = moon_checkint( L, 3, 1, INT_MAX );
    luaL_argcheck( L, line2 <= nitems, 3, "index too large" );
    b->swap( line1, line2 );
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_browser_text( lua_State* L ) {
  Fl_Browser* b = check_browser( L, 1 );
  int line = moon_checkint( L, 2, 1, INT_MAX );
  F4L_TRY( L ) {
    luaL_argcheck( L, line <= b->size(), 2, "index too large" );
    if( lua_gettop( L ) > 2 ) {
      b->text( line, luaL_checkstring( L, 3 ) );
      return 0;
    } else {
      char const* s = b->text( line );
      if( s != NULL )
        lua_pushstring( L, s );
      else
        lua_pushnil( L );
      return 1;
    }
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_browser_line_visible( lua_State* L ) {
  Fl_Browser* b = check_browser( L, 1 );
  int line = moon_checkint( L, 2, 1, INT_MAX );
  F4L_TRY( L ) {
    luaL_argcheck( L, line <= b->size(), 2, "index too large" );
    lua_pushboolean( L, b->visible( line ) );
  } F4L_CATCH( L );
  return 1;
}

F4L_LUA_LLINKAGE_END


MOON_LOCAL int f4l_browser_index_( lua_State* L, Fl_Browser* b,
                                   char const* key, size_t n ) {
  using namespace std;
  switch( n ) {
    case 4:
      if( F4L_MEMCMP( key, "type", 4 ) == 0 ) {
        f4l_push_type_browser( L, b->type() );
        return 1;
      }
      break;
    case 5:
      if( F4L_MEMCMP( key, "value", 5 ) == 0 ) {
        lua_pushinteger( L, b->value() );
        return 1;
      }
      break;
    case 6:
      if( F4L_MEMCMP( key, "nitems", 6 ) == 0 ) {
        lua_pushinteger( L, b->size() );
        return 1;
      }
      break;
    case 7:
      if( F4L_MEMCMP( key, "topline", 7 ) == 0 ) {
        lua_pushinteger( L, b->topline() );
        return 1;
      }
      break;
    case 11:
      if( F4L_MEMCMP( key, "column_char", 11 ) == 0 ) {
        f4l_push_char( L, b->column_char() );
        return 1;
      } else if( F4L_MEMCMP( key, "format_char", 11 ) == 0 ) {
        f4l_push_char( L, b->format_char() );
        return 1;
      }
      break;
    case 13:
      if( F4L_MEMCMP( key, "column_widths", 13 ) == 0 ) {
        int const* wds = b->column_widths();
        lua_newtable( L );
        int i = 1;
        while( *wds != 0 ) {
          lua_pushinteger( L, *wds );
          lua_rawseti( L, -2, i );
          ++wds; ++i;
        }
        return 1;
      }
      break;
  }
  return 0;
}


MOON_LOCAL int f4l_browser_newindex_( lua_State* L, Fl_Browser* b,
                                      char const* key, size_t n ) {
  using namespace std;
  switch( n ) {
    case 4:
      if( F4L_MEMCMP( key, "type", 4 ) == 0 ) {
        b->type( f4l_check_type_browser( L, 3 ) );
        return 1;
      }
      break;
    case 5:
      if( F4L_MEMCMP( key, "value", 5 ) == 0 ) {
        int line = moon_checkint( L, 3, 1, INT_MAX );
        luaL_argcheck( L, line <= b->size(), 3, "index too large" );
        b->value( line );
        return 1;
      }
      break;
    case 7:
      if( F4L_MEMCMP( key, "topline", 7 ) == 0 ) {
        int line = moon_checkint( L, 3, 1, INT_MAX );
        luaL_argcheck( L, line <= b->size(), 3, "index too large" );
        b->topline( line );
        return 1;
      }
      break;
    case 10:
      if( F4L_MEMCMP( key, "bottomline", 10 ) == 0 ) {
        int line = moon_checkint( L, 3, 1, INT_MAX );
        luaL_argcheck( L, line <= b->size(), 3, "index too large" );
        b->bottomline( line );
        return 1;
      } else if( F4L_MEMCMP( key, "middleline", 10 ) == 0 ) {
        int line = moon_checkint( L, 3, 1, INT_MAX );
        luaL_argcheck( L, line <= b->size(), 3, "index too large" );
        b->middleline( line );
        return 1;
      }
      break;
    case 11:
      if( F4L_MEMCMP( key, "column_char", 11 ) == 0 ) {
        b->column_char( f4l_check_char( L, 3 ) );
        return 1;
      } else if( F4L_MEMCMP( key, "format_char", 11 ) == 0 ) {
        b->format_char( f4l_check_char( L, 3 ) );
        return 1;
      }
      break;
    case 13:
      if( F4L_MEMCMP( key, "column_widths", 13 ) == 0 ) {
        luaL_checktype( L, 3, LUA_TTABLE );
        int len = luaL_len( L, 3 );
        void* mem = lua_newuserdata( L, (len+1)* sizeof( int ) );
        int* wds = static_cast< int* >( mem );
        wds[ len ] = 0;
        for( int i = 0; i < len; ++i ) {
          lua_geti( L, 3, i+1 );
          wds[ i ] = lua_tointeger( L, -1 ); // ignore type errors
          lua_pop( L, 1 );
        }
        lua_pushvalue( L, -1 );
        moon_setuvfield( L, 1, "column_widths" ); // keep array alive
        b->column_widths( wds );
        return 1;
      }
      break;
  }
  return 0;
}


F4L_DEF_CAST( Fl_Browser, Fl_Browser_ )
F4L_DEF_CAST( Fl_Browser, Fl_Widget )


MOON_LOCAL void f4l_browser_setup( lua_State* L ) {
  luaL_Reg const methods[] = {
    F4L_WIDGET_METHODS,
    F4L_BROWSERX_METHODS,
    F4L_BROWSER_METHODS,
    { "__index", browser_index },
    { "__newindex", browser_newindex },
    { NULL, NULL }
  };
  moon_defobject( L, F4L_BROWSER_NAME, 0, methods, 0 );
  moon_defcast( L, F4L_BROWSER_NAME, F4L_BROWSERX_NAME,
                f4l_cast_Fl_Browser_Fl_Browser_ );
  moon_defcast( L, F4L_BROWSER_NAME, F4L_WIDGET_NAME,
                f4l_cast_Fl_Browser_Fl_Widget );
  f4l_new_class_table( L, "Browser", new_browser );
}

