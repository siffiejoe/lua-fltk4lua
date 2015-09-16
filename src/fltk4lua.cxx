#include "fltk4lua.hxx"


namespace {

  int f4l_run_( lua_State* L ) {
    F4L_TRY {
      lua_pushinteger( L, Fl::run() );
    } F4L_CATCH( L );
    return 1;
  }

  int f4l_run( lua_State* L ) {
    lua_State** sp = f4l_get_active_thread( L );
    lua_pushcfunction( L, f4l_run_ );
    /* sp is not just important for the callbacks to get a lua_State*
     * to run with, but also for the finalizers which use it to
     * determine whether they run inside a callback, so special care
     * is taken that *sp is valid even if an error/exception is
     * thrown! */
    lua_State* oldL = *sp;
    *sp = L;
    int status = lua_pcall( L, 0, 1, 0 );
    *sp = oldL;
    if( status != 0 ) /* re-raise Lua error */
      lua_error( L );
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
    lua_State** sp = f4l_get_active_thread( L );
    lua_pushcfunction( L, f4l_wait_ );
    if( lua_gettop( L ) > 2 )
      lua_pushvalue( L, 1 );
    else
      lua_pushnil( L );
    /* see comment in f4l_run */
    lua_State* oldL = *sp;
    *sp = L;
    int status = lua_pcall( L, 1, 1, 0 );
    *sp = oldL;
    if( status != 0 ) /* re-raise Lua error */
      lua_error( L );
    return 1;
  }


  int f4l_check_( lua_State* L ) {
    F4L_TRY {
      lua_pushboolean( L, Fl::check() );
    } F4L_CATCH( L );
    return 1;
  }

  int f4l_check( lua_State* L ) {
    lua_State** sp = f4l_get_active_thread( L );
    lua_pushcfunction( L, f4l_check_ );
    /* see comment in f4l_run */
    lua_State* oldL = *sp;
    *sp = L;
    int status = lua_pcall( L, 0, 1, 0 );
    *sp = oldL;
    if( status != 0 ) /* re-raise Lua error */
      lua_error( L );
    return 1;
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


MOON_LOCAL lua_State** f4l_get_active_thread( lua_State* L ) {
  static char xyz = 0; /* used as a unique key */
  luaL_checkstack( L, 3, NULL );
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



/* setup functions declared in other files */
MOON_LOCAL void f4l_enums_setup( lua_State* L );
MOON_LOCAL void f4l_group_setup( lua_State* L );
MOON_LOCAL void f4l_window_setup( lua_State* L );
MOON_LOCAL void f4l_box_setup( lua_State* L );
// ...


F4L_API int luaopen_fltk4lua( lua_State* L ) {
  luaL_Reg const functions[] = {
    { "run", f4l_run },
    { "wait", f4l_wait },
    { "check", f4l_check },
    { NULL, NULL }
  };
  luaL_newlib( L, functions );
  lua_pushfstring( L, "fltk4lua v%d.%d using FLTK %d.%d.%d",
                   (int)F4L_VERSION_MAJOR, (int)F4L_VERSION_MINOR,
                   (int)FL_MAJOR_VERSION, (int)FL_MINOR_VERSION,
                   (int)FL_PATCH_VERSION );
  lua_setfield( L, -2, "_VERSION" );
  *moon_atexit( L, delete_remaining_widgets ) = 1;
  lua_pop( L, 1 ); // remove atexit userdata from stack
  f4l_enums_setup( L );
  f4l_group_setup( L );
  f4l_window_setup( L );
  f4l_box_setup( L );
  // ...
  return 1;
}

