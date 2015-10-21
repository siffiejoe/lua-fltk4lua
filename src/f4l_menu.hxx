#ifndef F4L_MENU_HXX_
#define F4L_MENU_HXX_

#include "fltk4lua.hxx"
#include <FL/Fl_Menu_.H>


/* Functions for keeping the mirror table in the uservalue in sync
 * with the menu items array */
MOON_LOCAL void f4l_prepare_menu_insert( lua_State* L, int midx,
                                         Fl_Menu_* m, int msize,
                                         char const* nlabel );
MOON_LOCAL void f4l_commit_menu_insert( lua_State* L, int midx,
                                        Fl_Menu_* m, int msize,
                                        int pos );


/* (Meta-)methods for Fl_Menu_ widgets: */
MOON_LOCAL int f4l_menu_index_( lua_State* L, Fl_Menu_* m,
                                char const* key, size_t n );
MOON_LOCAL int f4l_menu_newindex_( lua_State* L, Fl_Menu_* m,
                                   char const* key, size_t n );

F4L_LUA_LLINKAGE_BEGIN
MOON_LOCAL int f4l_menu_add( lua_State* L );
MOON_LOCAL int f4l_menu_clear( lua_State* L );
MOON_LOCAL int f4l_menu_clear_submenu( lua_State* L );
MOON_LOCAL int f4l_menu_find_index( lua_State* L );
MOON_LOCAL int f4l_menu_insert( lua_State* L );
MOON_LOCAL int f4l_menu_remove( lua_State* L );
MOON_LOCAL int f4l_menu_size( lua_State* L );
MOON_LOCAL int f4l_menu_menuitem_getp( lua_State* L );
MOON_LOCAL int f4l_menu_menuitem_setp( lua_State* L );
MOON_LOCAL int f4l_menu_menuitem_activate( lua_State* L );
MOON_LOCAL int f4l_menu_menuitem_active( lua_State* L );
MOON_LOCAL int f4l_menu_menuitem_activevisible( lua_State* L );
MOON_LOCAL int f4l_menu_menuitem_checkbox( lua_State* L );
MOON_LOCAL int f4l_menu_menuitem_clear( lua_State* L );
MOON_LOCAL int f4l_menu_menuitem_deactivate( lua_State* L );
MOON_LOCAL int f4l_menu_menuitem_hide( lua_State* L );
MOON_LOCAL int f4l_menu_menuitem_radio( lua_State* L );
MOON_LOCAL int f4l_menu_menuitem_set( lua_State* L );
MOON_LOCAL int f4l_menu_menuitem_setonly( lua_State* L );
MOON_LOCAL int f4l_menu_menuitem_show( lua_State* L );
MOON_LOCAL int f4l_menu_menuitem_submenu( lua_State* L );
MOON_LOCAL int f4l_menu_menuitem_value( lua_State* L );
MOON_LOCAL int f4l_menu_menuitem_visible( lua_State* L );
F4L_LUA_LLINKAGE_END


#define F4L_MENU_METHODS \
  { "add", f4l_menu_add }, \
  { "clear", f4l_menu_clear }, \
  { "clear_submenu", f4l_menu_clear_submenu }, \
  { "find_index", f4l_menu_find_index }, \
  { "insert", f4l_menu_insert }, \
  { "remove", f4l_menu_remove }, \
  { "size", f4l_menu_size }, \
  { "menuitem_getp", f4l_menu_menuitem_getp }, \
  { "menuitem_setp", f4l_menu_menuitem_setp }, \
  { "menuitem_activate", f4l_menu_menuitem_activate }, \
  { "menuitem_active", f4l_menu_menuitem_active }, \
  { "menuitem_activevisible", f4l_menu_menuitem_activevisible }, \
  { "menuitem_checkbox", f4l_menu_menuitem_checkbox }, \
  { "menuitem_clear", f4l_menu_menuitem_clear }, \
  { "menuitem_deactivate", f4l_menu_menuitem_deactivate }, \
  { "menuitem_hide", f4l_menu_menuitem_hide }, \
  { "menuitem_radio", f4l_menu_menuitem_radio }, \
  { "menuitem_set", f4l_menu_menuitem_set }, \
  { "menuitem_setonly", f4l_menu_menuitem_setonly }, \
  { "menuitem_show", f4l_menu_menuitem_show }, \
  { "menuitem_submenu", f4l_menu_menuitem_submenu }, \
  { "menuitem_value", f4l_menu_menuitem_value }, \
  { "menuitem_visible", f4l_menu_menuitem_visible }


#endif /* F4L_MENU_HXX_ */

