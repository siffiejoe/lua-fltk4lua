#ifndef F4L_WIDGET_HXX_
#define F4L_WIDGET_HXX_

#include "fltk4lua.hxx"
#include <FL/Fl_Widget.H>
#include <climits>


/* Custom flag to use in moon_object_headers to indicate that the
 * widget is running a callback (this is used by the menu code,
 * which prevents you from modifying the menu items during the
 * callback). */
#define F4L_CALLBACK_ACTIVE (0x80u)


/* Inside a FLTK callback the Fl_Widget pointer must be mapped to
 * a real userdata. This is done using a weak table in the registry.
 */
MOON_LOCAL void f4l_register_widget( lua_State* L, Fl_Widget* w,
                                     int setud = 1);
MOON_LOCAL void f4l_push_widget( lua_State* L, Fl_Widget* w );

/* Detect whether we created a given widget */
MOON_LOCAL int f4l_our_widget( lua_State* L, Fl_Widget* w );


/* Most widgets take the same arguments for their constructors, so
 * it makes sense to refactor creation of the widget userdata into
 * a helper function: */
template< typename T >
MOON_LOCAL T* f4l_new_widget( lua_State* L, char const* tname,
                              moon_object_destructor destructor ) {
  int has_properties = 0;
  if( lua_gettop( L ) == 2 && lua_istable( L, 2 ) ) {
    has_properties = 1;
    lua_replace( L, 1 );
    for( int i = 1; i <= 5; ++i )
      lua_rawgeti( L, 1, i );
  }
  lua_settop( L, 6 );
  lua_rotate( L, 1, -1 );
  int x = moon_checkint( L, 1, 0, INT_MAX );
  int y = moon_checkint( L, 2, 0, INT_MAX );
  int w = moon_checkint( L, 3, 0, INT_MAX );
  int h = moon_checkint( L, 4, 0, INT_MAX );
  char const* label = luaL_optstring( L, 5, NULL );
  void** p = moon_newpointer( L, tname, destructor );
  /* widgets need a uservalue table to store the callback function
   * and for keeping references to child widgets */
  lua_newtable( L );
  if( label != NULL ) {
    lua_pushvalue( L, 5 );
    lua_setfield( L, -2, "label" );
  }
  lua_setuservalue( L, -2 );
  /* all widgets are allocated via `new` because FLTK uses `delete`
   * internally */
  T* widget = new T( x, y, w, h, label );
  *p = static_cast< void* >( widget );
  /* add the new widget to the lightuserdata -> full userdata mapping
   * in the registry, set the Lua thread pointer as (FLTK) user data
   * for the callbacks, and put a reference to this widget into the
   * (Lua) uservalue table of the parent group widget (if any) */
  f4l_register_widget( L, widget );
  /* in case a table was used to pass constructor arguments, there
   * might be more properties to set on the userdata */
  if( has_properties )
    f4l_add_properties( L, 7, 6 );
  return widget;
}

/* Sometimes we want access to widgets that are members of another
 * object: */
template< typename T >
MOON_LOCAL void f4l_new_member( lua_State* L, char const* tname, T* w,
                                int pindex, int (*checkfn)( void* ) = 0,
                                void* ptr = NULL ) {
  void** p = moon_newfield( L, tname, pindex, checkfn, ptr );
  if( pindex == 0 ) {
    lua_newtable( L );
    lua_setuservalue( L, -2 );
  }
  *p = static_cast< void* >( w );
  f4l_register_widget( L, w, 0 );
}


/* (Meta-)methods for Fl_Widgets: */
MOON_LOCAL int f4l_widget_index_( lua_State* L, Fl_Widget* w,
                                  char const* key, size_t n );
MOON_LOCAL int f4l_widget_newindex_( lua_State* L, Fl_Widget* w,
                                     char const* key, size_t n );

F4L_LUA_LLINKAGE_BEGIN
MOON_LOCAL int f4l_widget_activate( lua_State* L );
MOON_LOCAL int f4l_widget_clear_changed( lua_State* L );
MOON_LOCAL int f4l_widget_clear_damage( lua_State* L );
MOON_LOCAL int f4l_widget_clear_output( lua_State* L );
MOON_LOCAL int f4l_widget_clear_visible( lua_State* L );
MOON_LOCAL int f4l_widget_clear_visible_focus( lua_State* L );
MOON_LOCAL int f4l_widget_contains( lua_State* L );
MOON_LOCAL int f4l_widget_deactivate( lua_State* L );
MOON_LOCAL int f4l_widget_hide( lua_State* L );
MOON_LOCAL int f4l_widget_inside( lua_State* L );
MOON_LOCAL int f4l_widget_measure_label( lua_State* L );
MOON_LOCAL int f4l_widget_position( lua_State* L );
MOON_LOCAL int f4l_widget_redraw( lua_State* L );
MOON_LOCAL int f4l_widget_redraw_label( lua_State* L );
MOON_LOCAL int f4l_widget_resize( lua_State* L );
MOON_LOCAL int f4l_widget_set_changed( lua_State* L );
MOON_LOCAL int f4l_widget_set_output( lua_State* L );
MOON_LOCAL int f4l_widget_set_visible( lua_State* L );
MOON_LOCAL int f4l_widget_set_visible_focus( lua_State* L );
MOON_LOCAL int f4l_widget_show( lua_State* L );
MOON_LOCAL int f4l_widget_size( lua_State* L );
MOON_LOCAL int f4l_widget_take_focus( lua_State* L );
F4L_LUA_LLINKAGE_END


#define F4L_WIDGET_METHODS \
  { "activate", f4l_widget_activate }, \
  { "clear_changed", f4l_widget_clear_changed }, \
  { "clear_damage", f4l_widget_clear_damage }, \
  { "clear_output", f4l_widget_clear_output }, \
  { "clear_visible", f4l_widget_clear_visible }, \
  { "clear_visible_focus", f4l_widget_clear_visible_focus }, \
  { "contains", f4l_widget_contains }, \
  { "deactivate", f4l_widget_deactivate }, \
  { "hide", f4l_widget_hide }, \
  { "inside", f4l_widget_inside }, \
  { "measure_label", f4l_widget_measure_label }, \
  { "position", f4l_widget_position }, \
  { "redraw", f4l_widget_redraw }, \
  { "redraw_label", f4l_widget_redraw_label }, \
  { "resize", f4l_widget_resize }, \
  { "set_changed", f4l_widget_set_changed }, \
  { "set_output", f4l_widget_set_output }, \
  { "set_visible", f4l_widget_set_visible }, \
  { "set_visible_focus", f4l_widget_set_visible_focus }, \
  { "show", f4l_widget_show }, \
  { "size", f4l_widget_size }, \
  { "take_focus", f4l_widget_take_focus }


#endif /* F4L_WIDGET_HXX_ */

