#ifndef FLTK4LUA_H_
#define FLTK4LUA_H_

/* Lua include files */
extern "C" {
#include <lua.h>
#include <lauxlib.h>
}
/* toolkit for easier binding to C/C++ code */
#include "moon.h"
/* compatibility functions for older Lua versions */
#include "compat-5.3.h"
/* common C++ headers */
#include <stdexcept>
/* basic FLTK headers */
#include <FL/Fl.H>


/* how to export the luaopen_ function */
#ifndef F4L_API
#  define F4L_API extern "C" MOON_EXPORT
#endif


/* transform C++ exceptions to Lua errors */
#define F4L_TRY \
  try
#define F4L_CATCH( L ) \
  catch( std::exception& e ) { \
    luaL_error( L, "%s", e.what() ); \
  } catch( ... ) { \
    luaL_error( L, "exception raised" ); \
  } return 0


#endif /* FLTK4LUA_H_ */

