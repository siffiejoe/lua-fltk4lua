#include "fltk4lua.hxx"
#include "f4l_enums.hxx"
#include <FL/filename.H>
#include <climits>


namespace {

  void get_fd_cache( lua_State * L ) {
    static int xyz = 0;
    lua_rawgetp( L, LUA_REGISTRYINDEX, static_cast< void* >( &xyz ) );
    if( lua_isnil( L, -1 ) ) {
      lua_pop( L, 1 );
      lua_newtable( L );
      lua_pushvalue( L, -1 );
      lua_rawsetp( L, LUA_REGISTRYINDEX, static_cast< void* >( &xyz ) );
    }
  }


  void f4l_fd_cb( FL_SOCKET fd, void* ud, int when ) {
    f4l_active_L* th = static_cast< f4l_active_L* >( ud );
    if( th != NULL && th->cb_L != NULL ) {
      lua_State* L = th->cb_L;
      luaL_checkstack( L, 4, "f4l_fd_cb" );
      int top = lua_gettop( L );
      lua_pushcfunction( L, f4l_backtrace ); // top+1: f4l_backtrace
      get_fd_cache( L ); // top+2: cache
      lua_rawgeti( L, -1, static_cast< int >( fd ) ); // top+3: fd callbacks table
      lua_remove( L, -2 ); // remove cache, top+1: f4l_backtrace, fd callbacks table
      lua_rawgeti( L, -1, when ); // top+3: lua callback
      lua_remove( L, -2 ); // remove fd callbacks table, top+1: f4l_backtrace, lua callback

      lua_pushinteger( L, static_cast< int >( fd ) ); // top+3: fd
      lua_pushinteger( L, when ); // top+4: when XXX not very useful to the Lua function!

      // top+1: f4l_backtrace, lua callback, fd, when
      int status = lua_pcall( L, 2, 0, top + 1 );
      // top+1: f4l_backtrace, err msg or nil
      if( status != 0 ) {
        lua_remove( L, -2 );
        f4l_fix_backtrace( L );
        lua_error( L );
      }

      lua_settop( L, top );
    }
  }


  void f4l_fd_cb_read( FL_SOCKET fd, void* ud ) {
    f4l_fd_cb( fd, ud, FL_READ );
  }

  void f4l_fd_cb_write( FL_SOCKET fd, void* ud ) {
    f4l_fd_cb( fd, ud, FL_WRITE );
  }

  void f4l_fd_cb_except( FL_SOCKET fd, void* ud ) {
    f4l_fd_cb( fd, ud, FL_EXCEPT );
  }

} // anonymous namespace



F4L_LUA_LLINKAGE_BEGIN

static int f4l_screen_width( lua_State* L) {
  F4L_TRY( L ) {
    lua_pushinteger( L, Fl::w() );
  } F4L_CATCH( L );
  return 1;
}

static int f4l_screen_height( lua_State* L) {
  F4L_TRY( L ) {
    lua_pushinteger( L, Fl::h() );
  } F4L_CATCH( L );
  return 1;
}

static int f4l_run_( lua_State* L ) {
  F4L_TRY( L ) {
    lua_pushinteger( L, Fl::run() );
  } F4L_CATCH( L );
  return 1;
}

static int f4l_run( lua_State* L ) {
  F4L_CALL_PROTECTED( L, f4l_run_, 1 );
  return 1;
}


static int f4l_wait_( lua_State* L ) {
  lua_Number timeout = luaL_optnumber( L, 1, -1 );
  luaL_argcheck( L, timeout >= -1, 1, "timeout must be positive" );
  F4L_TRY( L ) {
    lua_pushboolean( L, timeout < 0 ? Fl::wait() : Fl::wait( timeout ) );
  } F4L_CATCH( L );
  return 1;
}

static int f4l_wait( lua_State* L ) {
  F4L_CALL_PROTECTED( L, f4l_wait_, 1 );
  return 1;
}


static int f4l_check_( lua_State* L ) {
  F4L_TRY( L ) {
    lua_pushboolean( L, Fl::check() );
  } F4L_CATCH( L );
  return 1;
}

static int f4l_check( lua_State* L ) {
  F4L_CALL_PROTECTED( L, f4l_check_, 1 );
  return 1;
}


static int f4l_args( lua_State* L ) {
  int argc = 0;
  luaL_checktype( L, 1, LUA_TTABLE );
  char** argv = f4l_push_argv( L, 1, &argc );
  F4L_TRY( L ) {
    Fl::args( argc, argv );
  } F4L_CATCH( L );
  return 0;
}


static int f4l_get_system_colors( lua_State* L ) {
  F4L_TRY( L ) {
    Fl::get_system_colors();
  } F4L_CATCH( L );
  return 0;
}


static int f4l_scheme( lua_State* L ) {
  F4L_TRY( L ) {
    if( lua_gettop( L ) > 0 ) {
      size_t len = 0;
      char const* s = luaL_optlstring( L, 1, NULL, &len );
      luaL_argcheck( L, len < 1024, 1, "scheme name too long" );
      Fl::scheme( s );
      return 0;
    } else {
      char const* s = Fl::scheme();
      if( s != NULL )
        lua_pushstring( L, s );
      else
        lua_pushnil( L );
      return 1;
    }
  } F4L_CATCH( L );
  return 0;
}


static int f4l_redraw( lua_State* L ) {
  F4L_TRY( L ) {
    Fl::redraw();
  } F4L_CATCH( L );
  return 0;
}


static int f4l_option( lua_State* L ) {
  Fl::Fl_Option o = f4l_check_option( L, 1 );
  F4L_TRY( L ) {
    if( lua_gettop( L ) > 1 ) {
      Fl::option( o, lua_toboolean( L, 2 ) );
      return 0;
    } else {
      lua_pushboolean( L, Fl::option( o ) );
      return 1;
    }
  } F4L_CATCH( L );
  return 0;
}


static int f4l_open_uri( lua_State* L ) {
  char const* uri = luaL_checkstring( L, 1 );
  F4L_TRY( L ) {
    lua_pushboolean( L, fl_open_uri( uri, NULL, 0 ) );
  } F4L_CATCH( L );
  return 1;
}


static int f4l_add_fd( lua_State* L ) {
  static int whens[] = { FL_READ, FL_WRITE, FL_EXCEPT };
  static Fl_FD_Handler when_cbs[] = {
    f4l_fd_cb_read, f4l_fd_cb_write, f4l_fd_cb_except
  };
  int fd = moon_checkint( L, 1, 0, INT_MAX );
  luaL_checktype( L, 2, LUA_TFUNCTION );
  int when = luaL_opt( L, f4l_check_fd_when, 3, FL_READ );

  get_fd_cache( L );
  if( lua_rawgeti( L, -1, fd ) == LUA_TNIL ) {
    lua_pop( L, 1 );
    lua_newtable( L );
    lua_pushvalue( L, -1 );
    lua_rawseti( L, -3, fd );
  }
  lua_replace( L, -2 ); // fd cache no longer needed
  // Stack top contains callbacks table for this fd
  void* fd_cb_user_data = static_cast< void* >( f4l_get_active_thread( L ) );
  // Discard the userdata produced by f4l_get_active_thread
  lua_pop( L, 1 );
  F4L_TRY( L ) {
    for( int i = 0; i < 3; i++ ) {
      if ( when & whens[i] ) {
        lua_pushvalue( L, 2 );
        lua_rawseti( L, -2, whens[i] );
        Fl::add_fd( fd, whens[i], when_cbs[i], fd_cb_user_data );
      }
    }
  } F4L_CATCH( L );
  return 0;
}


static int f4l_remove_fd( lua_State* L ) {
  static int whens[] = { FL_READ, FL_WRITE, FL_EXCEPT };
  int fd = moon_checkint( L, 1, 0, INT_MAX );
  int when = luaL_opt( L, f4l_check_fd_when, 2, 0 );

  // The code here is pretty protective since FL::remove_fd() crashes when
  // removing callbacks of events that were not set. FL::add_fd() doesn’t
  // seem picky at all, though.
  F4L_TRY( L ) {
    get_fd_cache( L );
    if( lua_rawgeti( L, -1, fd ) == LUA_TNIL ) {
      // No event set for this FD at all, do nothing.
    } else if( when == 0 ) {
      // Remove all events
      lua_pop( L, 1 );
      lua_pushnil( L );
      lua_rawseti( L, -2, fd );
      Fl::remove_fd( fd );
    } else {
      bool empty = true;
      for( int i = 0; i < 3; i++ ) {
        // Is there a cb for this event?
        if( lua_rawgeti( L, -1, whens[i] ) != LUA_TNIL ) {
          // Are we removing this cb?
          if( when & whens[i] ) {
            lua_pushnil( L );
            lua_rawseti( L, -3, whens[i] );
            Fl::remove_fd( fd, whens[i] );
          } else {
            // This cb stays, so there’s at least one cb left for this fd
            empty = false;
          }
        }
        lua_pop( L, 1 ); // remove callback (or nil)
      }
      lua_pop( L, 1 ); // remove table of callbacks for this fd
      if( empty ) {
        // No more cb for this fd, remove the table of this fd from cache
        lua_pushnil( L );
        lua_rawseti( L, -2, fd );
      }
    }
  } F4L_CATCH( L );
  return 0;
}


/* registered via moon_atexit to make sure that all widgets
 * are deleted, even those collected during a callback */
static int delete_remaining_widgets( lua_State* L ) {
  int* v = static_cast< int* >( lua_touserdata( L, 1 ) );
  if( *v > 0 ) {
    F4L_TRY( L ) {
      Fl::check();
    } F4L_CATCH( L );
  }
  return 0;
}

F4L_LUA_LLINKAGE_END


MOON_LOCAL void f4l_delete_widget( Fl_Widget* w ) {
  f4l_active_L* ud = static_cast< f4l_active_L* >( w->user_data() );
  if( ud != NULL && ud->cb_L != NULL )
    Fl::delete_widget( w );
  else
    delete w;
}

MOON_LOCAL void f4l_delete_widget( Fl_Group* g ) {
  for( int i = g->children(); i > 0; --i )
    g->remove( i-1 );
  f4l_delete_widget( static_cast< Fl_Widget* >( g ) );
}


MOON_LOCAL char f4l_check_char( lua_State* L, int idx ) {
  size_t len = 0;
  char const* s = luaL_checklstring( L, idx, &len );
  luaL_argcheck( L, len == 1, idx, "single character expected" );
  return *s;
}


MOON_LOCAL int f4l_backtrace( lua_State* L ) {
  char const* msg = lua_tostring( L, 1 );
  if( msg != NULL )
    luaL_traceback( L, L, msg, 1 );
  return 1;
}

MOON_LOCAL void f4l_fix_backtrace( lua_State* L ) {
  size_t n = 0;
  char const* msg = lua_tolstring( L, -1, &n );
  if( msg != NULL && n > 0 ) {
    /* figure out our current stack level */
    int lvl = 0;
    lua_Debug d;
    while( lua_getstack( L, lvl, &d ) )
      ++lvl;
    /* remove the last lines of the stack trace that belongs to the
     * levels below us */
    char const* p = msg + n - 1;
    int cnt = 2;
    while( p != msg && (*p != '\n' || cnt < lvl) ) {
      if( *p == '\n' )
        ++cnt;
      --p;
    }
    if( p != msg ) {
      lua_pushlstring( L, msg, p-msg );
      lua_replace( L, -2 );
    }
  }
}


MOON_LOCAL f4l_active_L* f4l_get_active_thread( lua_State* L ) {
  static char xyz = 0; // used as a unique key
  luaL_checkstack( L, 3, "f4l_get_active_thread" );
  lua_rawgetp( L, LUA_REGISTRYINDEX, static_cast< void* >( &xyz ) );
  if( lua_type( L, -1 ) != LUA_TUSERDATA ) {
    lua_pop( L, 1 );
    void* p = lua_newuserdata( L, sizeof( f4l_active_L ) );
    f4l_active_L* sp = static_cast< f4l_active_L* >( p );
    sp->L = NULL;
    sp->cb_L = NULL;
    lua_pushvalue( L, -1 );
    lua_rawsetp( L, LUA_REGISTRYINDEX, static_cast< void* >( &xyz ) );
    lua_pushvalue( L, -1 ); // used as a place holder, since L is NULL
    sp->thread_ref = luaL_ref( L, LUA_REGISTRYINDEX );
    return sp;
  } else
    return static_cast< f4l_active_L* >( lua_touserdata( L, -1 ) );
}


MOON_LOCAL void f4l_set_active_thread( lua_State* L ) {
  f4l_active_L* th = f4l_get_active_thread( L );
  lua_pushthread( L );
  lua_rawseti( L, LUA_REGISTRYINDEX, th->thread_ref );
  lua_pop( L, 1 );
}


/* the following function exploits implementation details in FLTK
 * (that Fl_Window::show( int, char** ) does not modify the arguments)
 * and in Lua (that strings stored in a table cannot move in memory)!
 */
MOON_LOCAL char** f4l_push_argv( lua_State* L, int idx, int* argc ) {
  int n = luaL_len( L, idx );
  char** argv = (char**)lua_newuserdata( L, sizeof( char* ) * (n+2) );
  if( lua_rawgeti( L, idx, 0 ) == LUA_TSTRING ) {
    argv[ 0 ] = const_cast< char* >( lua_tostring( L, -1 ) );
  } else
    argv[ 0 ] = const_cast< char* >( "fltk4lua" );
  lua_pop( L, 1 );
  argv[ n+1 ] = NULL;
  int i = 1;
  for( ; i <= n; ++i ) {
    if( lua_rawgeti( L, idx, i ) == LUA_TSTRING ) {
      argv[ i ] = const_cast< char* >( lua_tostring( L, -1 ) );
      lua_pop( L, 1 );
    } else {
      argv[ i ] = NULL;
      lua_pop( L, 1 );
      break;
    }
  }
  *argc = i;
  return argv;
}


MOON_LOCAL void f4l_new_class_table( lua_State* L, char const* name,
                                     lua_CFunction constructor,
                                     luaL_Reg const* smethods ) {
  luaL_checkstack( L, 3, "f4l_new_class_table" );
  lua_newtable( L );
  if( smethods != NULL )
    luaL_setfuncs( L, smethods, 0 );
  if( constructor != 0 ) {
    lua_createtable( L, 0, 1 );
    lua_pushcfunction( L, constructor );
    lua_setfield( L, -2, "__call" );
    lua_setmetatable( L, -2 );
  }
  lua_setfield( L, -2, name );
}


MOON_LOCAL void f4l_add_properties( lua_State* L, int udidx, int tidx ) {
  udidx = lua_absindex( L, udidx );
  tidx = lua_absindex( L, tidx );
  lua_pushnil( L );
  while( lua_next( L, tidx ) != 0 ) {
    if( lua_type( L, -2 ) != LUA_TSTRING )
      lua_pop( L, 1 ); // ignore non-string keys
    else {
      lua_pushvalue( L, -2 );
      lua_insert( L, -2 );
      lua_settable( L, udidx );
    }
  }
}


MOON_LOCAL int (f4l_bad_property)( lua_State* L, char const* tname,
                                   char const* pname ) {
  /* raise an error when unknown properties are encountered */
  return luaL_error( L, "bad property '%s' for '%s' object",
                     pname, tname );
}


/* setup functions defined in the other source files */
MOON_LOCAL void f4l_enums_setup( lua_State* L );
MOON_LOCAL void f4l_ask_setup( lua_State* L );
MOON_LOCAL void f4l_shared_image_setup( lua_State* L );
MOON_LOCAL void f4l_widget_setup( lua_State* L );
MOON_LOCAL void f4l_box_setup( lua_State* L );
MOON_LOCAL void f4l_button_setup( lua_State* L );
MOON_LOCAL void f4l_chart_setup( lua_State* L );
MOON_LOCAL void f4l_clock_setup( lua_State* L );
MOON_LOCAL void f4l_group_setup( lua_State* L );
MOON_LOCAL void f4l_browser_setup( lua_State* L );
MOON_LOCAL void f4l_file_browser_setup( lua_State* L );
MOON_LOCAL void f4l_check_browser_setup( lua_State* L );
MOON_LOCAL void f4l_color_chooser_setup( lua_State* L );
MOON_LOCAL void f4l_input_choice_setup( lua_State* L );
MOON_LOCAL void f4l_pack_setup( lua_State* L );
MOON_LOCAL void f4l_scroll_setup( lua_State* L );
MOON_LOCAL void f4l_spinner_setup( lua_State* L );
MOON_LOCAL void f4l_tabs_setup( lua_State* L );
MOON_LOCAL void f4l_tile_setup( lua_State* L );
MOON_LOCAL void f4l_window_setup( lua_State* L );
MOON_LOCAL void f4l_wizard_setup( lua_State* L );
MOON_LOCAL void f4l_input_setup( lua_State* L );
MOON_LOCAL void f4l_menu_setup( lua_State* L );
MOON_LOCAL void f4l_choice_setup( lua_State* L );
MOON_LOCAL void f4l_menu_bar_setup( lua_State* L );
MOON_LOCAL void f4l_menu_button_setup( lua_State* L );
MOON_LOCAL void f4l_progress_setup( lua_State* L );
MOON_LOCAL void f4l_adjuster_setup( lua_State* L );
MOON_LOCAL void f4l_counter_setup( lua_State* L );
MOON_LOCAL void f4l_dial_setup( lua_State* L );
MOON_LOCAL void f4l_roller_setup( lua_State* L );
MOON_LOCAL void f4l_slider_setup( lua_State* L );
MOON_LOCAL void f4l_value_input_setup( lua_State* L );
MOON_LOCAL void f4l_value_output_setup( lua_State* L );


F4L_API int luaopen_fltk4lua( lua_State* L ) {
  luaL_Reg const functions[] = {
    { "w", f4l_screen_width },
    { "h", f4l_screen_height },
    { "run", f4l_run },
    { "wait", f4l_wait },
    { "check", f4l_check },
    { "args", f4l_args },
    { "get_system_colors", f4l_get_system_colors },
    { "scheme", f4l_scheme },
    { "redraw", f4l_redraw },
    { "option", f4l_option },
    { "open_uri", f4l_open_uri },
    { "add_fd", f4l_add_fd },
    { "remove_fd", f4l_remove_fd },
    { NULL, NULL }
  };
  luaL_newlib( L, functions );
  lua_pushfstring( L, "fltk4lua v%d.%d using FLTK %d.%d.%d",
                   (int)F4L_VERSION_MAJOR, (int)F4L_VERSION_MINOR,
                   (int)FL_MAJOR_VERSION, (int)FL_MINOR_VERSION,
                   (int)FL_PATCH_VERSION );
  lua_setfield( L, -2, "_VERSION" );
  lua_pushstring( L, Fl::help );
  lua_setfield( L, -2, "help" );
  *moon_atexit( L, delete_remaining_widgets ) = 1;
  lua_pop( L, 1 ); // remove atexit userdata from stack
  f4l_enums_setup( L );
  f4l_ask_setup( L );
  f4l_shared_image_setup( L );
  f4l_widget_setup( L );
  f4l_box_setup( L );
  f4l_button_setup( L );
  f4l_chart_setup( L );
  f4l_clock_setup( L );
  f4l_group_setup( L );
  f4l_browser_setup( L );
  f4l_file_browser_setup( L );
  f4l_check_browser_setup( L );
  f4l_color_chooser_setup( L );
  f4l_input_choice_setup( L );
  f4l_pack_setup( L );
  f4l_scroll_setup( L );
  f4l_spinner_setup( L );
  f4l_tabs_setup( L );
  f4l_tile_setup( L );
  f4l_window_setup( L );
  f4l_wizard_setup( L );
  f4l_input_setup( L );
  f4l_menu_setup( L );
  f4l_choice_setup( L );
  f4l_menu_bar_setup( L );
  f4l_menu_button_setup( L );
  f4l_progress_setup( L );
  f4l_adjuster_setup( L );
  f4l_counter_setup( L );
  f4l_dial_setup( L );
  f4l_roller_setup( L );
  f4l_slider_setup( L );
  f4l_value_input_setup( L );
  f4l_value_output_setup( L );
  return 1;
}

