#include "fltk4lua.hxx"
#include "f4l_enums.hxx"


namespace {

  int f4l_run_( lua_State* L ) {
    F4L_TRY {
      lua_pushinteger( L, Fl::run() );
    } F4L_CATCH( L );
    return 1;
  }

  int f4l_run( lua_State* L ) {
    F4L_CALL_PROTECTED( L, f4l_run_, 1 );
    return 1;
  }


  int f4l_wait_( lua_State* L ) {
    lua_Number timeout = luaL_optnumber( L, 1, 0 );
    luaL_argcheck( L, timeout >= 0, 1, "timeout must be positive" );
    F4L_TRY {
      lua_pushboolean( L, Fl::wait( timeout ) );
    } F4L_CATCH( L );
    return 1;
  }

  int f4l_wait( lua_State* L ) {
    F4L_CALL_PROTECTED( L, f4l_wait_, 1 );
    return 1;
  }


  int f4l_check_( lua_State* L ) {
    F4L_TRY {
      lua_pushboolean( L, Fl::check() );
    } F4L_CATCH( L );
    return 1;
  }

  int f4l_check( lua_State* L ) {
    F4L_CALL_PROTECTED( L, f4l_check_, 1 );
    return 1;
  }


  int f4l_args( lua_State* L ) {
    int argc = 0;
    luaL_checktype( L, 1, LUA_TTABLE );
    char** argv = f4l_push_argv( L, 1, &argc );
    F4L_TRY {
      Fl::args( argc, argv );
    } F4L_CATCH( L );
    return 0;
  }


  int f4l_get_system_colors( lua_State* L ) {
    F4L_TRY {
      Fl::get_system_colors();
    } F4L_CATCH( L );
    return 0;
  }


  /* registered via moon_atexit to make sure that all widgets
   * are deleted, even those collected during a callback */
  int delete_remaining_widgets( lua_State* L ) {
    int* v = static_cast< int* >( lua_touserdata( L, 1 ) );
    if( *v > 0 ) {
      F4L_TRY {
        Fl::check();
      } F4L_CATCH( L );
    }
    return 0;
  }

} // anonymous namespace


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


MOON_LOCAL lua_State** f4l_get_active_thread( lua_State* L ) {
  static char xyz = 0; /* used as a unique key */
  luaL_checkstack( L, 3, "f4l_get_active_thread" );
  lua_pushlightuserdata( L, static_cast< void* >( &xyz ) );
  lua_rawget( L, LUA_REGISTRYINDEX );
  if( lua_type( L, -1 ) != LUA_TUSERDATA ) {
    lua_pop( L, 1 );
    void* p = lua_newuserdata( L, sizeof( lua_State* ) );
    lua_State** sp = static_cast< lua_State** >( p );
    *sp = NULL;
    lua_pushlightuserdata( L, static_cast< void* >( &xyz ) );
    lua_pushvalue( L, -2 );
    lua_rawset( L, LUA_REGISTRYINDEX );
    return sp;
  } else
    return static_cast< lua_State** >( lua_touserdata( L, -1 ) );
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
    { "run", f4l_run },
    { "wait", f4l_wait },
    { "check", f4l_check },
    { "args", f4l_args },
    { "get_system_colors", f4l_get_system_colors },
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

