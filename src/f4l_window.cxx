#include "fltk4lua.hxx"
#include "f4l_window.hxx"
#include "f4l_group.hxx"
#include "f4l_widget.hxx"
#include "f4l_enums.hxx"
#include <cstring>
#include <climits>

namespace {

  inline Fl_Window* check_window( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_WINDOW_NAME );
    return static_cast< Fl_Window* >( p );
  }

  int window_index( lua_State* L ) {
    Fl_Window* w = check_window( L, 1 );
    size_t n = 0;
    char const* key = luaL_checklstring( L, 2, &n );
    F4L_TRY {
      if( !f4l_window_index_( L, w, key, n ) &&
          !f4l_group_index_( L, w, key, n ) &&
          !f4l_widget_index_( L, w, key, n ) )
        lua_pushnil( L );
    } F4L_CATCH( L );
    return 1;
  }

  int window_newindex( lua_State* L ) {
    Fl_Window* w = check_window( L, 1 );
    size_t n = 0;
    char const* key = luaL_checklstring( L, 2, &n );
    F4L_TRY {
      (void)(f4l_window_newindex_( L, w, key, n ) ||
             f4l_group_newindex_( L, w, key, n ) ||
             f4l_widget_newindex_( L, w, key, n ));
    } F4L_CATCH( L );
    return 0;
  }

  int new_window( lua_State* L ) {
    F4L_TRY {
      if( lua_gettop( L ) < 4 ) {
        int w = moon_checkint( L, 1, 0, INT_MAX );
        int h = moon_checkint( L, 2, 0, INT_MAX );
        char const* label = luaL_optstring( L, 3, NULL );
        void** p = moon_newpointer( L, F4L_WINDOW_NAME, f4l_delete< Fl_Window > );
        lua_newtable( L );
        if( label != NULL ) {
          lua_pushvalue( L, 3 );
          lua_setfield( L, -2, "label" );
        }
        lua_setuservalue( L, -2 );
        Fl_Window* window = new Fl_Window( w, h, label );
        *p = static_cast< void* >( window );
        f4l_register_widget( L, window );
      } else
        f4l_new_widget< Fl_Window >( L, F4L_WINDOW_NAME );
    } F4L_CATCH( L );
    return 1;
  }

} // anonymous namespace


MOON_LOCAL int f4l_window_index_( lua_State* L, Fl_Window* w,
                                  char const* key, size_t n ) {
  switch( n ) {
    case 5:
      if( F4L_MEMCMP( key, "label", 5 ) == 0 ) {
        char const* label = w->label();
        if( label != NULL )
          lua_pushstring( L, label );
        else
          lua_pushliteral( L, "" );
        return 1;
      } else if( F4L_MEMCMP( key, "modal", 5 ) == 0 ) {
        lua_pushboolean( L, w->modal() );
        return 1;
      } else if( F4L_MEMCMP( key, "shown", 5 ) == 0 ) {
        lua_pushboolean( L, w->shown() );
        return 1;
      }
      break;
    case 6:
      if( F4L_MEMCMP( key, "border", 6 ) == 0 ) {
        lua_pushboolean( L, w->border() );
        return 1;
      } else if( F4L_MEMCMP( key, "x_root", 6 ) == 0 ) {
        lua_pushinteger( L, w->x_root() );
        return 1;
      } else if( F4L_MEMCMP( key, "y_root", 6 ) == 0 ) {
        lua_pushinteger( L, w->y_root() );
        return 1;
      } else if( F4L_MEMCMP( key, "xclass", 6 ) == 0 ) {
        char const* c = w->xclass();
        if( c != NULL )
          lua_pushstring( L, c );
        else
          lua_pushliteral( L, "" );
        return 1;
      }
      break;
    case 8:
      if( F4L_MEMCMP( key, "override", 8 ) == 0 ) {
        lua_pushboolean( L, w->override() );
        return 1;
      }
      break;
    case 9:
      if( F4L_MEMCMP( key, "iconlabel", 9 ) == 0 ) {
        char const* label = w->iconlabel();
        if( label != NULL )
          lua_pushstring( L, label );
        else
          lua_pushliteral( L, "" );
        return 1;
      } else if( F4L_MEMCMP( key, "non_modal", 9 ) == 0 ) {
        lua_pushboolean( L, w->non_modal() );
        return 1;
      }
      break;
    case 11:
      if( F4L_MEMCMP( key, "decorated_h", 11 ) == 0 ) {
        lua_pushinteger( L, w->decorated_h() );
        return 1;
      } else if( F4L_MEMCMP( key, "decorated_w", 11 ) == 0 ) {
        lua_pushinteger( L, w->decorated_w() );
        return 1;
      } else if( F4L_MEMCMP( key, "menu_window", 11 ) == 0 ) {
        lua_pushboolean( L, w->menu_window() );
        return 1;
      }
      break;
    case 14:
      if( F4L_MEMCMP( key, "tooltip_window", 14 ) == 0 ) {
        lua_pushboolean( L, w->tooltip_window() );
        return 1;
      }
      break;
    case 17:
      if( F4L_MEMCMP( key, "fullscreen_active", 17 ) == 0 ) {
        lua_pushboolean( L, w->fullscreen_active() );
        return 1;
      }
      break;
  }
  return 0;
}

MOON_LOCAL int f4l_window_newindex_( lua_State* L, Fl_Window* w,
                                     char const* key, size_t n ) {
  switch( n ) {
    case 5:
      if( F4L_MEMCMP( key, "label", 5 ) == 0 ) {
        char const* s = luaL_checkstring( L, 3 );
        lua_pushvalue( L, 3 );
        moon_setuvfield( L, 1, "label" );
        w->label( s );
        return 1;
      }
      break;
    case 6:
      if( F4L_MEMCMP( key, "border", 6 ) == 0 ) {
        w->border( lua_toboolean( L, 3 ) );
        return 1;
      } else if( F4L_MEMCMP( key, "xclass", 6 ) == 0 ) {
        char const* c = luaL_checkstring( L, 3 );
        lua_pushvalue( L, 3 );
        moon_setuvfield( L, 1, "xclass" );
        w->xclass( c );
        return 1;
      }
      break;
    case 9:
      if( F4L_MEMCMP( key, "iconlabel", 9 ) == 0 ) {
        char const* label = luaL_checkstring( L, 3 );
        lua_pushvalue( L, 3 );
        moon_setuvfield( L, 1, "iconlabel" );
        w->iconlabel( label );
        return 1;
      }
      break;
  }
  return 0;
}


MOON_LOCAL int f4l_window_clear_border( lua_State* L ) {
  Fl_Window* window = check_window( L, 1 );
  F4L_TRY {
    window->clear_border();
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_window_cursor( lua_State* L ) {
  Fl_Window* window = check_window( L, 1 );
  Fl_Cursor cursor = f4l_check_cursor( L, 2 );
  Fl_Color fg = luaL_opt( L, f4l_check_color, 3, FL_BLACK );
  Fl_Color bg = luaL_opt( L, f4l_check_color, 4, FL_WHITE );
  F4L_TRY {
    window->cursor( cursor, fg, bg );
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_window_default_cursor( lua_State* L ) {
  Fl_Window* window = check_window( L, 1 );
  Fl_Cursor cursor = f4l_check_cursor( L, 2 );
  Fl_Color fg = luaL_opt( L, f4l_check_color, 3, FL_BLACK );
  Fl_Color bg = luaL_opt( L, f4l_check_color, 4, FL_WHITE );
  F4L_TRY {
    window->default_cursor( cursor, fg, bg );
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_window_free_position( lua_State* L ) {
  Fl_Window* window = check_window( L, 1 );
  F4L_TRY {
    window->free_position();
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_window_fullscreen( lua_State* L ) {
  Fl_Window* window = check_window( L, 1 );
  F4L_TRY {
    window->fullscreen();
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_window_fullscreen_off( lua_State* L ) {
  Fl_Window* window = check_window( L, 1 );
  F4L_TRY {
    if( lua_gettop( L ) > 1 ) {
      int x = moon_checkint( L, 2, 0, INT_MAX );
      int y = moon_checkint( L, 3, 0, INT_MAX );
      int w = moon_checkint( L, 4, 0, INT_MAX );
      int h = moon_checkint( L, 5, 0, INT_MAX );
      window->fullscreen_off( x, y, w, h );
    } else
      window->fullscreen_off();
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_window_iconize( lua_State* L ) {
  Fl_Window* window = check_window( L, 1 );
  F4L_TRY {
    window->iconize();
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_window_make_current( lua_State* L ) {
  Fl_Window* window = check_window( L, 1 );
  F4L_TRY {
    window->make_current();
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_window_resize( lua_State* L ) {
  Fl_Window* window = check_window( L, 1 );
  int x = moon_checkint( L, 2, 0, INT_MAX );
  int y = moon_checkint( L, 3, 0, INT_MAX );
  int w = moon_checkint( L, 4, 0, INT_MAX );
  int h = moon_checkint( L, 5, 0, INT_MAX );
  F4L_TRY {
    window->resize( x, y, w, h );
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_window_set_modal( lua_State* L ) {
  Fl_Window* window = check_window( L, 1 );
  F4L_TRY {
    window->set_modal();
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_window_set_non_modal( lua_State* L ) {
  Fl_Window* window = check_window( L, 1 );
  F4L_TRY {
    window->set_non_modal();
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_window_set_override( lua_State* L ) {
  Fl_Window* window = check_window( L, 1 );
  F4L_TRY {
    window->set_override();
  } F4L_CATCH( L );
  return 0;
}


/* the following function exploits implementation details in FLTK
 * (that Fl_Window::show( int, char** ) does not modify the arguments)
 * and in Lua (that strings stored in a table cannot move in memory)!
 */
MOON_LOCAL int f4l_window_show( lua_State* L ) {
  Fl_Window* window = check_window( L, 1 );
  F4L_TRY {
    if( lua_isnoneornil( L, 2 ) ) {
      window->show();
    } else {
      luaL_checktype( L, 2, LUA_TTABLE );
      int n = luaL_len( L, 2 );
      char** argv = (char**)lua_newuserdata( L, sizeof( char* ) * (n+2) );
      if( lua_rawgeti( L, 2, 0 ) == LUA_TSTRING ) {
        argv[ 0 ] = const_cast< char* >( lua_tostring( L, -1 ) );
      } else
        argv[ 0 ] = const_cast< char* >( "fltk4lua" );
      lua_pop( L, 1 );
      argv[ n+1 ] = NULL;
      int i = 1;
      for( ; i <= n; ++i ) {
        if( lua_rawgeti( L, 2, i ) == LUA_TSTRING ) {
          argv[ i ] = const_cast< char* >( lua_tostring( L, -1 ) );
          lua_pop( L, 1 );
        } else {
          argv[ i ] = NULL;
          lua_pop( L, 1 );
          break;
        }
      }
      window->show( i, argv );
    }
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_window_size_range( lua_State* L ) {
  Fl_Window* window = check_window( L, 1 );
  int minw = moon_checkint( L, 2, 1, INT_MAX );
  int minh = moon_checkint( L, 3, 1, INT_MAX );
  int maxw = moon_optint( L, 4, 0, INT_MAX, 0 );
  int maxh = moon_optint( L, 5, 0, INT_MAX, 0 );
  int dw = moon_optint( L, 6, 0, INT_MAX, 0 );
  int dh = moon_optint( L, 7, 0, INT_MAX, 0 );
  int aspect = lua_toboolean( L, 8 );
  F4L_TRY {
    window->size_range( minw, minh, maxw, maxh, dw, dh, aspect );
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL void f4l_window_setup( lua_State* L ) {
  luaL_Reg const functions[] = {
    { "Window", new_window },
    { NULL, NULL }
  };
  luaL_Reg const methods[] = {
    F4L_WIDGET_METHODS,
    F4L_GROUP_METHODS,
    F4L_WINDOW_METHODS,
    { "__index", window_index },
    { "__newindex", window_newindex },
    { NULL, NULL }
  };
  moon_defobject( L, F4L_WINDOW_NAME, 0, methods, 0 );
  moon_defcast( L, F4L_WINDOW_NAME, F4L_GROUP_NAME,
                f4l_cast< Fl_Window, Fl_Group > );
  moon_defcast( L, F4L_WINDOW_NAME, F4L_WIDGET_NAME,
                f4l_cast< Fl_Window, Fl_Widget > );
  luaL_setfuncs( L, functions, 0 );
}

