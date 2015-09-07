#include "fltk4lua.hxx"

static int f4l_run( lua_State* L ) {
  F4L_TRY {
    lua_pushinteger( L, Fl::run() );
    return 1;
  } F4L_CATCH( L );
}


F4L_API int luaopen_fltk4lua( lua_State* L ) {
  luaL_Reg const funcs[] = {
    { "run", f4l_run },
    { NULL, NULL }
  };
  luaL_newlib( L, funcs );
  // register functions/objects/methods defined in the other files
  return 1;
}

