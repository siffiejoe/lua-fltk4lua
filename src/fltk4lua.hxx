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
  inline void safe_delete( T* p ) { delete p; }
  /* Widgets must not be deleted during a callback, so the
   * Fl::delete_widget() function is used instead in case a
   * Fl::run()/Fl::wait()/Fl::check() is active (checked via a
   * non-NULL value in f4l_get_active_thread()). */
  template<>
  inline void safe_delete( Fl_Widget* w ) {
    lua_State** ud = static_cast< lua_State** >( w->user_data() );
    if( ud != NULL && *ud != NULL )
      Fl::delete_widget( w );
    else
      delete w;
  }

} // anonymous namespace for helper functions


/* Generic function for calling delete on an FLTK Widget pointer.
 * Since destructors are virtual anyway, you can save instantiations
 * by using f4l_deleta< Fl_Widget > for all objects derived from
 * Fl_Widget. Widgets derived from Fl_Group are an exception,
 * because they need special handling for the children -- use
 * f4l_delete< Fl_Group > for those instead! */
template< typename T >
MOON_LOCAL void f4l_delete( void* p ) {
  T* t1 = static_cast< T* >( p );
  clear_child_widgets( t1 );
  safe_delete( t1 );
}


/* the Lua callbacks need a lua_State pointer to run */
MOON_LOCAL lua_State** f4l_get_active_thread( lua_State* L );


/* metatable names for FLTK objects */
#define F4L_WIDGET_NAME "fltk4lua.Widget"
#define F4L_GROUP_NAME  "fltk4lua.Group"
#define F4L_WINDOW_NAME "fltk4lua.Window"
#define F4L_BOX_NAME    "fltk4lua.Box"
#define F4L_BUTTON_NAME "fltk4lua.Button"
// ...


#endif /* FLTK4LUA_HXX_ */

