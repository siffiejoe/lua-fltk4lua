#include "fltk4lua.hxx"
#include "f4l_enums.hxx"
#include <FL/fl_ask.H>
#include <FL/Fl_Color_Chooser.H>
#include <FL/Fl_File_Chooser.H>


namespace {

#define BEEP_LIST( _ ) \
  _( FL_BEEP_DEFAULT ) \
  _( FL_BEEP_MESSAGE ) \
  _( FL_BEEP_ERROR ) \
  _( FL_BEEP_QUESTION ) \
  _( FL_BEEP_PASSWORD ) \
  _( FL_BEEP_NOTIFICATION )

  int check_beep( lua_State* L, int idx ) {
    static char const* const names[] = {
#define GEN_NAME( _a ) #_a,
      BEEP_LIST( GEN_NAME )
#undef GEN_NAME
      NULL
    };
    static int const values[] = {
#define GEN_VALUE( _a ) _a,
      BEEP_LIST( GEN_VALUE )
#undef GEN_VALUE
      0 // dummy value
    };
    return values[ luaL_checkoption( L, idx, NULL, names ) ];
  }

} // anonymous namespace


F4L_LUA_LLINKAGE_BEGIN

static int f4l_alert_( lua_State* L ) {
  char const* s = luaL_checkstring( L, 1);
  F4L_TRY( L ) {
    fl_alert( "%s", s );
  } F4L_CATCH( L );
  return 0;
}

static int f4l_alert( lua_State* L ) {
  F4L_CALL_PROTECTED( L, f4l_alert_, 0 );
  return 0;
}


static int f4l_beep( lua_State* L ) {
  int b = luaL_opt( L, check_beep, 1, FL_BEEP_DEFAULT );
  F4L_TRY( L ) {
    fl_beep( b );
  } F4L_CATCH( L );
  return 0;
}


static int f4l_choice_( lua_State* L ) {
  char const* s = luaL_checkstring( L, 1 );
  char const* b0 = luaL_optstring( L, 2, NULL );
  char const* b1 = luaL_optstring( L, 3, NULL );
  char const* b2 = luaL_optstring( L, 4, NULL );
  lua_settop( L, 4 );
  F4L_TRY( L ) {
    lua_pushvalue( L, 2+fl_choice( "%s", b0, b1, b2, s ) );
  } F4L_CATCH( L );
  return 1;
}

static int f4l_choice( lua_State* L ) {
  F4L_CALL_PROTECTED( L, f4l_choice_, 1 );
  return 1;
}


static int f4l_color_chooser_( lua_State* L ) {
  char const* s = luaL_optstring( L, 1, NULL );
  uchar r = moon_optint( L, 2, 0, 255, 0 );
  uchar g = moon_optint( L, 3, 0, 255, 0 );
  uchar b = moon_optint( L, 4, 0, 255, 0 );
  int mode = moon_optint( L, 5, -1, 3, -1 );
  F4L_TRY( L ) {
    if( fl_color_chooser( s, r, g, b, mode ) )
      f4l_push_color( L, fl_rgb_color( r, g, b ) );
    else
      lua_pushnil( L );
  } F4L_CATCH( L );
  return 1;
}

static int f4l_color_chooser( lua_State* L ) {
  F4L_CALL_PROTECTED( L, f4l_color_chooser_, 1 );
  return 1;
}


static int f4l_dir_chooser_( lua_State* L ) {
  char const* msg = luaL_checkstring( L, 1 );
  char const* fname = luaL_checkstring( L, 2 );
  int relative = lua_toboolean( L, 3 );
  F4L_TRY( L ) {
    char const* p = fl_dir_chooser( msg, fname, relative );
    if( p != NULL )
      lua_pushstring( L, p );
    else
      lua_pushnil( L );
  } F4L_CATCH( L );
  return 1;
}

static int f4l_dir_chooser( lua_State* L ) {
  F4L_CALL_PROTECTED( L, f4l_dir_chooser_, 1 );
  return 1;
}


static int f4l_file_chooser_( lua_State* L ) {
  char const* msg = luaL_checkstring( L, 1 );
  char const* pat = luaL_checkstring( L, 2 );
  char const* fname = luaL_checkstring( L, 3 );
  int relative = lua_toboolean( L, 4 );
  F4L_TRY( L ) {
    char const* p = fl_file_chooser( msg, pat, fname, relative );
    if( p != NULL )
      lua_pushstring( L, p );
    else
      lua_pushnil( L );
  } F4L_CATCH( L );
  return 1;
}

static int f4l_file_chooser( lua_State* L ) {
  F4L_CALL_PROTECTED( L, f4l_file_chooser_, 1 );
  return 1;
}


static int f4l_input_( lua_State* L ) {
  char const* msg = luaL_checkstring( L, 1 );
  char const* def = luaL_optstring( L, 2, NULL );
  F4L_TRY( L ) {
    char const* r = fl_input( "%s", def, msg );
    if( r == NULL )
      lua_pushnil( L );
    else if( r == def )
      lua_settop( L, 2 );
    else
      lua_pushstring( L, r );
  } F4L_CATCH( L );
  return 1;
}

static int f4l_input( lua_State* L ) {
  F4L_CALL_PROTECTED( L, f4l_input_, 1 );
  return 1;
}


static int f4l_message_( lua_State* L ) {
  char const* msg = luaL_checkstring( L, 1 );
  F4L_TRY( L ) {
    fl_message( "%s", msg );
  } F4L_CATCH( L );
  return 0;
}

static int f4l_message( lua_State* L ) {
  F4L_CALL_PROTECTED( L, f4l_message_, 0 );
  return 0;
}


static int f4l_password_( lua_State* L ) {
  char const* msg = luaL_checkstring( L, 1 );
  char const* def = luaL_optstring( L, 2, NULL );
  F4L_TRY( L ) {
    char const* r = fl_password( "%s", def, msg );
    if( r == NULL )
      lua_pushnil( L );
    else if( r == def )
      lua_settop( L, 2 );
    else
      lua_pushstring( L, r );
  } F4L_CATCH( L );
  return 1;
}

static int f4l_password( lua_State* L ) {
  F4L_CALL_PROTECTED( L, f4l_password_, 1 );
  return 1;
}


static int f4l_message_hotspot( lua_State* L ) {
  F4L_TRY( L ) {
    if( lua_gettop( L ) > 0 ) {
      fl_message_hotspot( lua_toboolean( L, 1 ) );
      return 0;
    } else {
      lua_pushboolean( L, fl_message_hotspot() );
      return 1;
    }
  } F4L_CATCH( L );
  return 0;
}

F4L_LUA_LLINKAGE_END


MOON_LOCAL void f4l_ask_setup( lua_State* L ) {
  luaL_Reg const functions[] = {
    { "alert", f4l_alert },
    { "beep", f4l_beep },
    { "choice", f4l_choice },
    { "color_chooser", f4l_color_chooser },
    { "dir_chooser", f4l_dir_chooser },
    { "file_chooser", f4l_file_chooser },
    { "input", f4l_input },
    { "message", f4l_message },
    { "password", f4l_password },
    { "message_hotspot", f4l_message_hotspot },
    { NULL, NULL }
  };
  luaL_setfuncs( L, functions, 0 );
}

