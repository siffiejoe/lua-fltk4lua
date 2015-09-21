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
#include <exception> // for std::exception
/* basic FLTK headers */
#include <FL/Fl.H>
#include <FL/Fl_Group.H>


/* version number of this binding */
#define F4L_VERSION_MAJOR 0
#define F4L_VERSION_MINOR 1


/* how to export the luaopen_ function */
#ifndef F4L_API
#  define F4L_API extern "C" MOON_EXPORT
#endif


/* transform standard C++ exceptions to Lua errors */
#define F4L_TRY \
  do { try
#define F4L_CATCH( L ) \
  catch( std::exception const& e ) { \
    return luaL_error( L, "%s", e.what() ); \
  } } while( 0 )


/* macro that raises an error if _n doesn't match the length of the
 * string literal _s (only works if _n is a literal number) */
#define F4L_MEMCMP( _p, _s, _n ) \
  ((void)sizeof( char[ sizeof( _s )-1 == _n ? 1 : -1 ] ), \
   memcmp( _p, _s "", _n ))


/* Macro that pcalls a lua_CFunction to maintain the thread pointer
 * created by `f4l_get_active_thread()`. This thread pointer is not
 * just important for the callbacks to get a lua_State* to run with,
 * but also for the finalizers which use it to determine whether they
 * run inside a callback, so special care is taken that *_sp is valid
 * even if an error/exception is thrown! */
#define F4L_CALL_PROTECTED( L, _f, _r ) \
  do { \
    lua_State* _l = L; \
    int _n = lua_gettop( _l ); \
    luaL_checkstack( _l, 2*_n+2, NULL ); \
    lua_State** _sp = f4l_get_active_thread( _l ); \
    lua_pushcfunction( _l, _f ); \
    for( int _i = 1; _i <= _n; ++_i ) \
      lua_pushvalue( _l, _i ); \
    lua_State* _oldL = *_sp; \
    *_sp = _l; \
    int _status = lua_pcall( _l, _n, _r, 0 ); \
    *_sp = _oldL; \
    if( _status != 0 ) /* reraise Lua error */ \
      lua_error( _l ); \
  } while( 0 )


/* generic function for casting a pointer to sub-type to a pointer
 * to a super-type */
template< typename T1, typename T2 >
MOON_LOCAL void* f4l_cast( void* p ) {
  T1* t1 = static_cast< T1* >( p );
  T2* t2 = t1; // implicit conversion should be enough here
  return static_cast< void* >( t2 );
}


/* groups need special attention during destruction */
namespace {
  /* FLTK does some automatic memory management for the children
   * of an Fl_Group which interferes with the finalizers used in
   * Lua, so an Fl_Group-derived object is cleared before its
   * destructor runs, and the child widgets are deleted in their
   * respective finalizers! */
  inline void clear_child_widgets( Fl_Group* g ) {
    for( int i = g->children(); i > 0; --i )
      g->remove( i-1 );
  }
  inline void clear_child_widgets( ... ) {} // for non-Fl_Groups

  template< typename T >
  inline void safe_delete( void* p, ... ) {
    delete static_cast< T* >( p );
  }
  /* Widgets must not be deleted during a callback, so the
   * Fl::delete_widget() function is used instead in case a
   * Fl::run()/Fl::wait()/Fl::check() is active (checked via a
   * non-NULL value in f4l_get_active_thread()). */
  template< typename T >
  inline void safe_delete( void*, Fl_Widget* w ) {
    lua_State** ud = static_cast< lua_State** >( w->user_data() );
    if( ud != NULL && *ud != NULL )
      Fl::delete_widget( w );
    else
      delete w;
  }

} // anonymous namespace for helper functions


/* Generic function for calling delete on an FLTK Widget pointer. */
template< typename T >
MOON_LOCAL void f4l_delete( void* p ) {
  T* t1 = static_cast< T* >( p );
  clear_child_widgets( t1 );
  /* This is a hack to select an overload based on whether T is
   * derived from Fl_Widget: */
  safe_delete< T >( static_cast< void* >( t1 ), t1 );
}


/* the Lua callbacks need a lua_State pointer to run */
MOON_LOCAL lua_State** f4l_get_active_thread( lua_State* L );

/* make argc/argv pair from a Lua arg table */
MOON_LOCAL char** f4l_push_argv( lua_State* L, int idx, int* argc );

/* adds a class table to the table at the stack top */
MOON_LOCAL void f4l_new_class_table( lua_State* L, char const* name,
                                     lua_CFunction constructor,
                                     luaL_Reg const* smethods = NULL );

/* set the properties stored in the table on the userdata */
MOON_LOCAL void f4l_add_properties( lua_State* L, int udidx, int tidx );


/* metatable names for FLTK objects */
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
#define F4L_COLOR_CHOOSER_NAME      "fltk4lua.Color_Chooser"
#define F4L_PACK_NAME               "fltk4lua.Pack"
#define F4L_SCROLL_NAME             "fltk4lua.Scroll"
#define F4L_TABS_NAME               "fltk4lua.Tabs"
#define F4L_TILE_NAME               "fltk4lua.Tile"
#define F4L_WINDOW_NAME             "fltk4lua.Window"
#define F4L_WIZARD_NAME             "fltk4lua.Wizard"
#define F4L_INPUT_NAME              "fltk4lua.Input"
#define F4L_FILE_INPUT_NAME         "fltk4lua.File_Input"
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

