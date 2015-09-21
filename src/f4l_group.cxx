#include "fltk4lua.hxx"
#include "f4l_group.hxx"
#include "f4l_widget.hxx"
#include <cstring>
#include <climits>

namespace {

  inline Fl_Group* check_group( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_GROUP_NAME );
    return static_cast< Fl_Group* >( p );
  }

  inline Fl_Widget* check_widget( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_WIDGET_NAME );
    return static_cast< Fl_Widget* >( p );
  }

  int group_index( lua_State* L ) {
    Fl_Group* g = check_group( L, 1 );
    size_t n = 0;
    char const* key = luaL_checklstring( L, 2, &n );
    F4L_TRY {
      if( !f4l_group_index_( L, g, key, n ) &&
          !f4l_widget_index_( L, g, key, n ) &&
          !f4l_bad_property( L, F4L_GROUP_NAME, key ) )
        lua_pushnil( L );
    } F4L_CATCH( L );
    return 1;
  }

  int group_newindex( lua_State* L ) {
    Fl_Group* g = check_group( L, 1 );
    size_t n = 0;
    char const* key = luaL_checklstring( L, 2, &n );
    F4L_TRY {
      (void)(f4l_group_newindex_( L, g, key, n ) ||
             f4l_widget_newindex_( L, g, key, n ) ||
             f4l_bad_property( L, F4L_GROUP_NAME, key ));
    } F4L_CATCH( L );
    return 0;
  }

  int new_group( lua_State* L ) {
    F4L_TRY {
      f4l_new_widget< Fl_Group >( L, F4L_GROUP_NAME );
    } F4L_CATCH( L );
    return 1;
  }

} // anonymous namespace


MOON_LOCAL int f4l_group_index_( lua_State* L, Fl_Group* g,
                                 char const* key, size_t n ) {
  using namespace std;
  switch( n ) {
    case 8:
      if( F4L_MEMCMP( key, "children", 8 ) == 0 ) {
        lua_pushinteger( L, g->children() );
        return 1;
      }
      break;
    case 9:
      if( F4L_MEMCMP( key, "resizable", 9 ) == 0 ) {
        f4l_push_widget( L, g->resizable() );
        return 1;
      }
      break;
    case 13:
      if( F4L_MEMCMP( key, "clip_children", 13 ) == 0 ) {
        lua_pushboolean( L, g->clip_children() );
        return 1;
      }
      break;
  }
  return 0;
}

MOON_LOCAL int f4l_group_newindex_( lua_State* L, Fl_Group* g,
                                    char const* key, size_t n ) {
  using namespace std;
  switch( n ) {
    case 9:
      if( F4L_MEMCMP( key, "resizable", 9 ) == 0 ) {
        Fl_Widget* w = luaL_opt( L, check_widget, 3, NULL );
        if( w != NULL )
          lua_pushvalue( L, 3 );
        else
          lua_pushnil( L );
        moon_setuvfield( L, 1, "resizable" );
        g->resizable( w );
        return 1;
      }
      break;
    case 13:
      if( F4L_MEMCMP( key, "clip_children", 13 ) == 0 ) {
        g->clip_children( lua_toboolean( L, 3 ) );
        return 1;
      }
    break;
  }
  return 0;
}


MOON_LOCAL int f4l_group_add( lua_State* L ) {
  Fl_Group* group = check_group( L, 1 );
  Fl_Widget* widget = check_widget( L, 2 );
  Fl_Widget* parent = NULL;
  F4L_TRY {
    parent = widget->parent();
  } F4L_CATCH( L );
  int has_parent = parent != NULL && parent != group;
  if( has_parent ) {
    f4l_push_widget( L, parent );
    lua_getuservalue( L, -1 );
    lua_replace( L, -2 );
  }
  lua_getuservalue( L, 1 );
  lua_pushlightuserdata( L, static_cast< void* >( widget ) );
  lua_pushvalue( L, 2 );
  lua_rawset( L, -3 );
  lua_pop( L, 1 );
  F4L_TRY {
    group->add( widget );
  } F4L_CATCH( L );
  if( has_parent ) {
    lua_pushlightuserdata( L, static_cast< void* >( widget ) );
    lua_pushnil( L );
    lua_rawset( L, -3 );
    lua_pop( L, 1 );
  }
  return 0;
}


MOON_LOCAL int f4l_group_add_resizable( lua_State* L ) {
  Fl_Group* group = check_group( L, 1 );
  Fl_Widget* widget = check_widget( L, 2 );
  Fl_Widget* parent = NULL;
  F4L_TRY {
    parent= widget->parent();
  } F4L_CATCH( L );
  int has_parent = parent != NULL && parent != group;
  if( has_parent ) {
    f4l_push_widget( L, parent );
    lua_getuservalue( L, -1 );
    lua_replace( L, -2 );
  }
  lua_getuservalue( L, 1 );
  lua_pushlightuserdata( L, static_cast< void* >( widget ) );
  lua_pushvalue( L, 2 );
  lua_rawset( L, -3 );
  lua_pop( L, 1 );
  F4L_TRY {
    group->add_resizable( *widget );
  } F4L_CATCH( L );
  if( has_parent ) {
    lua_pushlightuserdata( L, static_cast< void* >( widget ) );
    lua_pushnil( L );
    lua_rawset( L, -3 );
    lua_pop( L, 1 );
  }
  return 0;
}


MOON_LOCAL int f4l_group_begin( lua_State* L ) {
  Fl_Group* group = check_group( L, 1 );
  F4L_TRY {
    group->begin();
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_group_child( lua_State* L ) {
  Fl_Group* group = check_group( L, 1 );
  F4L_TRY {
    int i = moon_checkint( L, 2, 0, group->children()-1 );
    f4l_push_widget( L, group->child( i ) );
  } F4L_CATCH( L );
  return 1;
}


MOON_LOCAL int f4l_group_clear( lua_State* L ) {
  Fl_Group* group = check_group( L, 1 );
  lua_getuservalue( L, 1 );
  F4L_TRY {
    int n = group->children();
    for( int i = n; i > 0; --i ) {
      Fl_Widget* w = group->child( i-1 );
      group->remove( i-1 );
      lua_pushlightuserdata( L, static_cast< void* >( w ) );
      lua_pushnil( L );
      lua_rawset( L, -3 );
    }
  } F4L_CATCH( L );
  lua_pop( L, 1 );
  return 0;
}


MOON_LOCAL int f4l_group_end( lua_State* L ) {
  Fl_Group* group = check_group( L, 1 );
  F4L_TRY {
    group->end();
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_group_find( lua_State* L ) {
  Fl_Group* group = check_group( L, 1 );
  Fl_Widget* widget = check_widget( L, 2 );
  F4L_TRY {
    lua_pushinteger( L, group->find( widget ) );
  } F4L_CATCH( L );
  return 1;
}


MOON_LOCAL int f4l_group_insert( lua_State* L ) {
  Fl_Group* group = check_group( L, 1 );
  Fl_Widget* widget = check_widget( L, 2 );
  int index = moon_checkint( L, 3, 0, INT_MAX );
  Fl_Widget* parent = NULL;
  F4L_TRY {
    parent= widget->parent();
  } F4L_CATCH( L );
  int has_parent = parent != NULL && parent != group;
  if( has_parent ) {
    f4l_push_widget( L, parent );
    lua_getuservalue( L, -1 );
    lua_replace( L, -2 );
  }
  lua_getuservalue( L, 1 );
  lua_pushlightuserdata( L, static_cast< void* >( widget ) );
  lua_pushvalue( L, 2 );
  lua_rawset( L, -3 );
  lua_pop( L, 1 );
  F4L_TRY {
    group->insert( *widget, index );
  } F4L_CATCH( L );
  if( has_parent ) {
    lua_pushlightuserdata( L, static_cast< void* >( widget ) );
    lua_pushnil( L );
    lua_rawset( L, -3 );
    lua_pop( L, 1 );
  }
  return 0;
}


MOON_LOCAL int f4l_group_remove( lua_State* L ) {
  Fl_Group* group = check_group( L, 1 );
  int index = moon_checkint( L, 2, 0, INT_MAX );
  Fl_Widget* w = NULL;
  F4L_TRY {
    if( index < group->children() )
      w = group->child( index );
    group->remove( index );
  } F4L_CATCH( L );
  if( w != NULL ) {
    lua_getuservalue( L, 1 );
    lua_pushlightuserdata( L, static_cast< void* >( w ) );
    lua_pushnil( L );
    lua_rawset( L, -3 );
    lua_pop( L, 1 );
  }
  return 0;
}


MOON_LOCAL void f4l_group_setup( lua_State* L ) {
  luaL_Reg const methods[] = {
    F4L_WIDGET_METHODS,
    F4L_GROUP_METHODS,
    { "__index", group_index },
    { "__newindex", group_newindex },
    { NULL, NULL }
  };
  moon_defobject( L, F4L_GROUP_NAME, 0, methods, 0 );
  moon_defcast( L, F4L_GROUP_NAME, F4L_WIDGET_NAME,
                f4l_cast< Fl_Group, Fl_Widget > );
  f4l_new_class_table( L, "Group", new_group );
}

