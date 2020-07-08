#ifndef FLTK4LUA_H_
#define FLTK4LUA_H_

/* Lua include files */
extern "C" {
#include <lua.h>
#include <lauxlib.h>
/* toolkit for easier binding to C/C++ code */
#include "moon.h"
/* compatibility functions for older Lua versions */
#include "compat-5.3.h"
}
/* common C++ headers */
#include <exception> // for std::exception
#include <cstring>   // for std::strncpy and std::memcmp
/* basic FLTK headers */
#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Group.H>


/* version number of this binding */
#define F4L_VERSION_MAJOR 0
#define F4L_VERSION_MINOR 2


/* how to export the luaopen_ function */
#ifndef F4L_API
#  define F4L_API extern "C" MOON_EXPORT
#endif


/* language linkage decorations for various functions to be passed to
 * Lua or the moon toolkit */
#define F4L_MOON_LLINKAGE_BEGIN extern "C" {
#define F4L_MOON_LLINKAGE_END   }
#define F4L_LUA_LLINKAGE_BEGIN  extern "C" {
#define F4L_LUA_LLINKAGE_END    }


/* transform standard C++ exceptions to Lua errors */
#define F4L_TRY( L ) \
  do { \
    int _f4l_exception_thrown = 0; \
    char _f4l_exception_buffer[ 128 ]; \
    /* f4l_set_active_thread( L ); */ \
    try

#define F4L_CATCH( L ) \
    catch( std::exception const& e ) { \
      using namespace std; \
      size_t _sz = sizeof( _f4l_exception_buffer )-1; \
      _f4l_exception_thrown = 1; \
      std::strncpy( _f4l_exception_buffer, e.what(), _sz ); \
      _f4l_exception_buffer[ _sz ] = '\0'; \
    } \
    if( _f4l_exception_thrown ) \
      luaL_error( L, "C++ exception: \"%s\"", _f4l_exception_buffer ); \
  } while( 0 )


#if 0
/* macro that raises an error if _n doesn't match the length of the
 * string literal _s (only works if _n is a literal number) */
#define F4L_MEMCMP( _p, _s, _n ) \
  ((void)sizeof( char[ sizeof( _s )-1 == _n ? 1 : -1 ] ), \
   std::memcmp( _p, _s "", _n ))

#else
template <std::size_t N>
MOON_LOCAL inline int f4l_memcmp( char const* s, char const (&name)[ N+1 ] ) {
  return std::memcmp( s, name, N );
}
#define F4L_MEMCMP( _p, _s, _n ) (f4l_memcmp< _n >( _p, _s ))
#endif


/* Macro that pcalls a lua_CFunction to maintain the thread pointer
 * created by `f4l_get_active_thread()`. This thread pointer is not
 * just important for the callbacks to get a lua_State* to run with,
 * but also for the finalizers which use it to determine whether they
 * run inside a callback, so special care is taken that _sp->cb_L is
 * valid even if an error/exception is thrown! */
#define F4L_CALL_PROTECTED( L, _f, _r ) \
  do { \
    lua_State* _l = L; \
    int _n = lua_gettop( _l ); \
    luaL_checkstack( _l, 2*_n+2, NULL ); \
    f4l_active_L* _sp = f4l_get_active_thread( _l ); \
    lua_pushcfunction( _l, _f ); \
    for( int _i = 1; _i <= _n; ++_i ) \
      lua_pushvalue( _l, _i ); \
    lua_State* _oldL = _sp->cb_L; \
    _sp->cb_L = _l; \
    int _status = lua_pcall( _l, _n, _r, 0 ); \
    _sp->cb_L = _oldL; \
    if( _status != 0 ) /* re-raise Lua error */ \
      lua_error( _l ); \
  } while( 0 )


/* Userdata type to keep track of coroutines suitable for calling FLTK
 * callbacks. */
struct f4l_active_L {
  lua_State* L;    // currently running coroutine
  lua_State* cb_L; // L used for callbacks (strict stack discipline)
  int thread_ref;  // anchor for L in the Lua registry
};


/* Macro for generating cast functions used by the moon toolkit.
 * We can't use a template here, because the functions need to have
 * "C" linkage! */
#define F4L_DEF_CAST( _t1, _t2 ) \
  F4L_MOON_LLINKAGE_BEGIN \
  static void* f4l_cast_ ## _t1 ## _ ## _t2( void* p ) { \
    _t1* p1 = static_cast< _t1* >( p ); \
    _t2* p2 = p1; /* implicit conversion should be enough here */ \
    return static_cast< void* >( p2 ); \
  } \
  F4L_MOON_LLINKAGE_END


/* Macro to generate destructor functions for FLTK widgets. We can't
 * use templates, because those functions need to have "C" linkage! */
#define F4L_DEF_DELETE( _t ) \
  F4L_MOON_LLINKAGE_BEGIN \
  static void f4l_delete_ ## _t( void* p ) { \
    f4l_delete_widget( static_cast< _t* >( p ) ); \
  } \
  F4L_MOON_LLINKAGE_END


MOON_LOCAL void f4l_delete_widget( Fl_Widget* w );
MOON_LOCAL void f4l_delete_widget( Fl_Group* g );

/* type checking function for a single character/byte string */
MOON_LOCAL char f4l_check_char( lua_State* L, int idx );
MOON_LOCAL inline void f4l_push_char( lua_State* L, char c ) {
  lua_pushlstring( L, &c, 1 );
}

/* lua_pcall message handler that produces a standard back trace */
MOON_LOCAL int f4l_backtrace( lua_State* L );
MOON_LOCAL void f4l_fix_backtrace( lua_State* L );

/* the Lua callbacks need a lua_State pointer to run */
MOON_LOCAL f4l_active_L* f4l_get_active_thread( lua_State* L );
MOON_LOCAL void f4l_set_active_thread( lua_State* L );

/* make argc/argv pair from a Lua arg table */
MOON_LOCAL char** f4l_push_argv( lua_State* L, int idx, int* argc );

/* adds a class table to the table at the stack top */
MOON_LOCAL void f4l_new_class_table( lua_State* L, char const* name,
                                     lua_CFunction constructor,
                                     luaL_Reg const* smethods = NULL );

/* set the properties stored in the table on the userdata */
MOON_LOCAL void f4l_add_properties( lua_State* L, int udidx, int tidx );

/* fallback function if a property could not be found */
MOON_LOCAL int f4l_bad_property( lua_State* L, char const* tname,
                                 char const* pname );
#if 0
/* disable errors for unknown properties */
#define f4l_bad_property( _a, _b, _c ) (0)
#endif


/* metatable names for FLTK objects */
#define F4L_IMAGE_NAME              "fltk4lua.Image"
#define F4L_SHARED_IMAGE_NAME       "fltk4lua.Shared_Image"
#define F4L_WIDGET_NAME             "fltk4lua.Widget"
#define F4L_BOX_NAME                "fltk4lua.Box"
#define F4L_BUTTON_NAME             "fltk4lua.Button"
#define F4L_LIGHT_BUTTON_NAME       "fltk4lua.Light_Button"
#define F4L_CHECK_BUTTON_NAME       "fltk4lua.Check_Button"
#define F4L_REPEAT_BUTTON_NAME      "fltk4lua.Repeat_Button"
#define F4L_RETURN_BUTTON_NAME      "fltk4lua.Return_Button"
#define F4L_ROUND_BUTTON_NAME       "fltk4lua.Round_Button"
#define F4L_CHART_NAME              "fltk4lua.Chart"
#define F4L_CLOCK_OUTPUT_NAME       "fltk4lua.Clock_Output"
#define F4L_CLOCK_NAME              "fltk4lua.Clock"
#define F4L_GROUP_NAME              "fltk4lua.Group"
#define F4L_BROWSERX_NAME           "fltk4lua.Browser_"
#define F4L_BROWSER_NAME            "fltk4lua.Browser"
#define F4L_FILE_BROWSER_NAME       "fltk4lua.File_Browser"
#define F4L_CHECK_BROWSER_NAME      "fltk4lua.Check_Browser"
#define F4L_COLOR_CHOOSER_NAME      "fltk4lua.Color_Chooser"
#define F4L_INPUT_CHOICE_NAME       "fltk4lua.Input_Choice"
#define F4L_PACK_NAME               "fltk4lua.Pack"
#define F4L_SCROLL_NAME             "fltk4lua.Scroll"
#define F4L_SPINNER_NAME            "fltk4lua.Spinner"
#define F4L_TABS_NAME               "fltk4lua.Tabs"
#define F4L_TILE_NAME               "fltk4lua.Tile"
#define F4L_WINDOW_NAME             "fltk4lua.Window"
#define F4L_WIZARD_NAME             "fltk4lua.Wizard"
#define F4L_INPUT_NAME              "fltk4lua.Input"
#define F4L_FILE_INPUT_NAME         "fltk4lua.File_Input"
#define F4L_MENU_NAME               "fltk4lua.Menu"
#define F4L_CHOICE_NAME             "fltk4lua.Choice"
#define F4L_MENU_BAR_NAME           "fltk4lua.Menu_Bar"
#define F4L_MENU_BUTTON_NAME        "fltk4lua.Menu_Button"
#define F4L_PROGRESS_NAME           "fltk4lua.Progress"
#define F4L_VALUATOR_NAME           "fltk4lua.Valuator"
#define F4L_ADJUSTER_NAME           "fltk4lua.Adjuster"
#define F4L_COUNTER_NAME            "fltk4lua.Counter"
#define F4L_DIAL_NAME               "fltk4lua.Dial"
#define F4L_ROLLER_NAME             "fltk4lua.Roller"
#define F4L_SLIDER_NAME             "fltk4lua.Slider"
#define F4L_SCROLLBAR_NAME          "fltk4lua.Scrollbar"
#define F4L_VALUE_SLIDER_NAME       "fltk4lua.Value_Slider"
#define F4L_VALUE_INPUT_NAME        "fltk4lua.Value_Input"
#define F4L_VALUE_OUTPUT_NAME       "fltk4lua.Value_Output"


#endif /* FLTK4LUA_HXX_ */

