#ifndef F4L_GROUP_HXX_
#define F4L_GROUP_HXX_

#include "fltk4lua.hxx"
#include <FL/Fl_Group.H>


/* (Meta-)methods for Fl_Groups: */
MOON_LOCAL int f4l_group_index_( lua_State* L, Fl_Group* g,
                                 char const* key, size_t n );
MOON_LOCAL int f4l_group_newindex_( lua_State* L, Fl_Group* g,
                                    char const* key, size_t n );

F4L_LUA_LLINKAGE_BEGIN
MOON_LOCAL int f4l_group_add( lua_State* L );
MOON_LOCAL int f4l_group_add_resizable( lua_State* L );
MOON_LOCAL int f4l_group_begin( lua_State* L );
MOON_LOCAL int f4l_group_child( lua_State* L );
MOON_LOCAL int f4l_group_clear( lua_State* L );
MOON_LOCAL int f4l_group_end( lua_State* L );
MOON_LOCAL int f4l_group_find( lua_State* L );
MOON_LOCAL int f4l_group_insert( lua_State* L );
MOON_LOCAL int f4l_group_remove( lua_State* L );
F4L_LUA_LLINKAGE_END


#define F4L_GROUP_METHODS \
  { "add", f4l_group_add }, \
  { "add_resizable", f4l_group_add_resizable }, \
  { "begin", f4l_group_begin }, \
  { "begin_group", f4l_group_begin }, \
  { "child", f4l_group_child }, \
  { "clear", f4l_group_clear }, \
  { "end_group", f4l_group_end }, \
  { "find", f4l_group_find }, \
  { "insert", f4l_group_insert }, \
  { "remove", f4l_group_remove }


#endif /* F4L_GROUP_HXX_ */

