#include "fltk4lua.hxx"
#include "f4l_menu.hxx"
#include "f4l_widget.hxx"
#include "f4l_enums.hxx"
#include <cstring>
#include <climits>
#include <cstdio>


#define MENU_FLAG_LIST( _ ) \
  _( "MENU_REGULAR", 0 ) \
  _( "MENU_INACTIVE", FL_MENU_INACTIVE ) \
  _( "MENU_TOGGLE", FL_MENU_TOGGLE ) \
  _( "MENU_VALUE", FL_MENU_VALUE ) \
  _( "MENU_RADIO", FL_MENU_RADIO ) \
  _( "MENU_INVISIBLE", FL_MENU_INVISIBLE ) \
  _( "SUBMENU", FL_SUBMENU ) \
  _( "MENU_DIVIDER", FL_MENU_DIVIDER )

#define MOON_FLAG_NAME "flkt4lua.Menu_Flag"
#define MOON_FLAG_TYPE int
#define MOON_FLAG_SUFFIX menu
#define MOON_FLAG_USECACHE
#define MOON_FLAG_NORELOPS
#include "moon_flag.h"


namespace {

  inline Fl_Menu_* check_menu( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_MENU_NAME );
    return static_cast< Fl_Menu_* >( p );
  }

  /* during a menu callback the menu must not be modified! */
  Fl_Menu_* check_rw_menu( lua_State* L, int idx ) {
    Fl_Menu_* m = check_menu( L, idx );
    void* p = lua_touserdata( L, idx );
    moon_object_header* h = NULL;
    h = static_cast< moon_object_header* >( p );
    if( h->flags & F4L_CALLBACK_ACTIVE )
      luaL_error( L, "menu is temporarily readonly" );
    return m;
  }


  void f4l_menu_callback( Fl_Widget* w, void* ) {
    Fl_Menu_* menu = static_cast< Fl_Menu_* >( w );
    int v = menu->value();
    // we use the Menu_'s user_data instead of the Menu_Item's:
    f4l_active_L* th = static_cast< f4l_active_L* >( w->user_data() );
    if( th != NULL && th->cb_L != NULL && v >= 0 ) {
      lua_State* L = th->cb_L;
      luaL_checkstack( L, 6, "f4l_menu_callback" );
      int top = lua_gettop( L );
      lua_pushcfunction( L, f4l_backtrace );
      f4l_push_widget( L, w );
      lua_pushvalue( L, -1 ); // widget, widget
      moon_object_header* h = NULL;
      h = static_cast< moon_object_header* >( lua_touserdata( L, -2 ) );
      if( moon_getuvfield( L, -1, "menu" ) == LUA_TTABLE &&
          lua_rawgeti( L, -1, v+1 ) == LUA_TTABLE ) {
        lua_replace( L, -2 ); // widget, widget, menu-entry
        if( lua_getfield( L, -1, "callback" ) == LUA_TFUNCTION ) {
          lua_insert( L, -3 ); // widget, callback, widget, menu-entry
          lua_getfield( L, -1, "user_data" );
          lua_replace( L, -2 ); // widget, callback, widget, user_data
          int oldf = h->flags & F4L_CALLBACK_ACTIVE;
          h->flags |= F4L_CALLBACK_ACTIVE;
          int status = lua_pcall( L, 2, 0, top+1 );
          h->flags = (h->flags & ~F4L_CALLBACK_ACTIVE) | oldf;
          if( status != 0 ) {
            lua_replace( L, -3 );
            lua_pop( L, 1 );
            f4l_fix_backtrace( L );
            lua_error( L );
          }
        }
      }
      lua_settop( L, top );
    }
  }


  // helper function for table_rotate
  void table_reverse( lua_State* L, int idx, int a, int b ) {
    idx = lua_absindex( L, idx );
    for( ; a < b; ++a, --b ) {
      lua_rawgeti( L, idx, a );
      lua_rawgeti( L, idx, b );
      lua_rawseti( L, idx, a );
      lua_rawseti( L, idx, b );
    }
  }


  // similar to lua_rotate, but on table contents instead of stack!
  void table_rotate( lua_State* L, int idx, int i, int n ) {
    int n_elems = luaL_len( L, idx )-i+1;
    if( n < 0 )
      n += n_elems;
    if( n > 0 && n < n_elems ) {
      n = n_elems - n;
      table_reverse( L, idx, i, i+n-1 );
      table_reverse( L, idx, i+n, i+n_elems-1 );
      table_reverse( L, idx, i, i+n_elems-1 );
    }
  }


  void table_remove( lua_State* L, int idx, int i, int n ) {
    idx = lua_absindex( L, idx );
    int oldn = luaL_len( L, idx );
    while( i <= oldn ) {
      lua_rawgeti( L, idx, i+n );
      lua_rawseti( L, idx, i );
      ++i;
    }
  }


  void table_shrink( lua_State* L, int idx, int newn ) {
    idx = lua_absindex( L, idx );
    for( int oldn = luaL_len( L, idx ); oldn > newn; --oldn ) {
      lua_pushnil( L );
      lua_rawseti( L, idx, oldn );
    }
  }


#if 0
  // for debugging only; otherwise unused function
  void menu_array_dump( lua_State* L, int idx ) {
    using namespace std;
    idx = lua_absindex( L, idx );
    moon_checkobject( L, idx, F4L_MENU_NAME );
    int t = moon_getuvfield( L, idx, "menu" );
    if( t == LUA_TNIL ) {
      fprintf( stderr, "no menu item mirror table\n" );
    } else if( t != LUA_TTABLE ) {
      fprintf( stderr, "menu uservalue field has wrong type: %s\n",
               lua_typename( L, t ) );
      lua_pop( L, 1 );
    } else {
      luaL_checkstack( L, 5, "menu_array_dump" );
      int n = luaL_len( L, -1 );
      for( int i = 1; i <= n; ++i ) {
        int it = lua_rawgeti( L, -1, i );
        fprintf( stderr, "item %d, lua type: %s\n", i-1,
                 lua_typename( L, it ) );
        if( it == LUA_TTABLE ) {
          lua_getfield( L, -1, "callback" );
          lua_getfield( L, -2, "user_data" );
          char const* cb = luaL_tolstring( L, -2, NULL );
          char const* ud = luaL_tolstring( L, -2, NULL );
          fprintf( stderr, "  callback: %s, user_data: %s\n", cb, ud );
          lua_pop( L, 4 );
        }
        lua_pop( L, 1 );
      }
      lua_pop( L, 1 );
    }
  }
#endif


#undef MENU_SYNC_WARN
#define MENU_SYNC_ERROR

  // setup the menu item mirror table in the uservalue table
  void menu_array_sync( lua_State* L, int idx, Fl_Menu_* m, int msize ) {
    using namespace std;
    idx = lua_absindex( L, idx );
    lua_getuservalue( L, idx );
    if( lua_getfield( L, -1, "menu" ) != LUA_TTABLE ) {
      lua_pop( L, 1 );
      lua_createtable( L, msize, 0 );
      lua_pushvalue( L, -1 );
      lua_setfield( L, -3, "menu" );
    }
    lua_replace( L, -2 ); // remove uservalue table, keep mirror table
    Fl_Menu_Item const* p = m->menu();
    for( int i = 0; i < msize; ++i ) {
      char const* t = p[ i ].label();
      if( t == NULL ) { // sub-menu terminator
        if( lua_rawgeti( L, -1, i+1 ) != LUA_TBOOLEAN ) {
#ifdef MENU_SYNC_WARN
          fprintf( stderr, "menu out of sync (item: %d, Lua type: %s)!\n",
                   i, luaL_typename( L, -1 ) );
#endif
#ifdef MENU_SYNC_ERROR
          luaL_error( L, "menu out of sync (item %d)", i );
#endif
          lua_pushboolean( L, 0 ); // terminators are falses
          lua_rawseti( L, -3, i+1 );
        }
      } else { // normal menu element
        if( lua_rawgeti( L, -1, i+1 ) != LUA_TTABLE ) {
#ifdef MENU_SYNC_WARN
          fprintf( stderr, "menu out of sync (item: %d, Lua type: %s)!\n",
                   i, luaL_typename( L, -1 ) );
#endif
#ifdef MENU_SYNC_ERROR
          luaL_error( L, "menu out of sync (item %d)", i );
#endif
          lua_newtable( L );
          lua_rawseti( L, -3, i+1 );
        }
      }
      lua_pop( L, 1 );
    }
    table_shrink( L, -1, msize );
  }

} // anonymous namespace


MOON_LOCAL void f4l_prepare_menu_insert( lua_State* L, int midx,
                                         Fl_Menu_* m, int msize,
                                         char const* nlabel ) {
  menu_array_sync( L, midx, m, msize ); // pushes mirror table
  /* the number of slashes in the label gives an upper limit to the
   * number of submenus that will be added automatically */
  int n_slashes = 0;
  for( ; *nlabel != '\0'; ++nlabel )
    if( *nlabel == '/' )
      ++n_slashes;
  // preallocate memory for sub-menus + element to be inserted
  for( int i = 0; i < n_slashes+1; ++i ) {
    lua_newtable( L );
    lua_rawseti( L, -2, msize+i+1 );
  }
  // preallocate sub-menu terminators
  for( int i = n_slashes+1; i < 2*n_slashes+2; ++i ) {
    lua_pushboolean( L, 0 );
    lua_rawseti( L, -2, msize+i+1 );
  }
}


MOON_LOCAL void f4l_commit_menu_insert( lua_State* L, int midx,
                                        Fl_Menu_* m, int osize,
                                        int pos ) {
  (void)midx; // don't need it
  int newsize = m->size();
  /* update the mirror table by shifting preallocated items to the
   * correct positions. */
  if( newsize > osize ) {
    int tsize = luaL_len( L, -1 );
    int added = newsize-osize;
    int n_submenus = (added-1)/2, n_terminators = added/2;
    int n_pasubmenus = (tsize - osize)/2 - 1;
    // remove preallocated terminators we don't need
    table_shrink( L, -1, osize+n_pasubmenus+1+n_terminators );
    // move preallocated stuff to the right position
    table_rotate( L, -1, pos+1-n_submenus, n_submenus+1+n_terminators );
  }
  // remove preallocated leftovers
  table_shrink( L, -1, newsize );
  lua_rawgeti( L, -1, pos+1 );
  lua_replace( L, -2 ); // remove mirror, put item table on stack top
}


MOON_LOCAL int f4l_menu_index_( lua_State* L, Fl_Menu_* m,
                                char const* key, size_t n ) {
  using namespace std;
  switch( n ) {
    case 5:
      if( F4L_MEMCMP( key, "value", 5 ) == 0 ) {
        lua_pushinteger( L, m->value() );
        return 1;
      }
      break;
    case 8:
      if( F4L_MEMCMP( key, "down_box", 8 ) == 0 ) {
        f4l_push_boxtype( L, m->down_box() );
        return 1;
      } else if( F4L_MEMCMP( key, "textfont", 8 ) == 0 ) {
        f4l_push_font( L, m->textfont() );
        return 1;
      } else if( F4L_MEMCMP( key, "textsize", 8 ) == 0 ) {
        lua_pushinteger( L, m->textsize() );
        return 1;
      }
      break;
    case 9:
      if( F4L_MEMCMP( key, "menu_size", 9 ) == 0 ) {
        lua_pushinteger( L, m->size() );
        return 1;
      } else if( F4L_MEMCMP( key, "textcolor", 9 ) == 0 ) {
        f4l_push_color( L, m->textcolor() );
        return 1;
      }
      break;
  }
  return 0;
}


MOON_LOCAL int f4l_menu_newindex_( lua_State* L, Fl_Menu_* m,
                                   char const* key, size_t n ) {
  using namespace std;
  switch( n ) {
    case 5:
      if( F4L_MEMCMP( key, "value", 5 ) == 0 ) {
        int i = moon_checkint( L, 3, 0, INT_MAX );
        luaL_argcheck( L, 0 <= i && i < m->size(), 3,
                       "index out of range" );
        m->value( i );
        return 1;
      }
      break;
    case 8:
      if( F4L_MEMCMP( key, "down_box", 8 ) == 0 ) {
        m->down_box( f4l_check_boxtype( L, 3 ) );
        return 1;
      } else if( F4L_MEMCMP( key, "textfont", 8 ) == 0 ) {
        m->textfont( f4l_check_font( L, 3 ) );
        return 1;
      } else if( F4L_MEMCMP( key, "textsize", 8 ) == 0 ) {
        m->textsize( moon_checkint( L, 3, 0, INT_MAX ) );
        return 1;
      }
      break;
    case 9:
      if( F4L_MEMCMP( key, "textcolor", 9 ) == 0 ) {
        m->textcolor( f4l_check_color( L, 3 ) );
        return 1;
      }
      break;
  }
  return 0;
}


F4L_LUA_LLINKAGE_BEGIN

MOON_LOCAL int f4l_menu_add( lua_State* L ) {
  F4L_TRY( L ) {
    Fl_Menu_* m = check_rw_menu( L, 1 );
    size_t n = 0;
    char const* label = luaL_checklstring( L, 2, &n );
    luaL_argcheck( L, n < 1024, 2,
                   "menu label too long (FLTK limitation)" );
    lua_settop( L, 6 );
    Fl_Shortcut sc = luaL_opt( L, f4l_check_shortcut, 3, 0 );
    int have_cb = 0;
    if( !lua_isnil( L, 4 ) ) {
      luaL_checktype( L, 4, LUA_TFUNCTION );
      have_cb = 1;
    }
    int mflags = luaL_opt( L, moon_flag_get_menu, 6, 0 );
    luaL_argcheck( L, !(mflags & FL_SUBMENU), 6,
                   "FL_SUBMENU not allowed (FLTK bug)" );
    int msize = m->size();
    f4l_prepare_menu_insert( L, 1, m, msize, label );
    int pos = m->add( label, sc, have_cb ? f4l_menu_callback : 0,
                      NULL, mflags );
    f4l_commit_menu_insert( L, 1, m, msize, pos );
    // set callback and user_data fields
    lua_pushvalue( L, 4 );
    lua_setfield( L, -2, "callback" );
    lua_pushvalue( L, 5 );
    lua_setfield( L, -2, "user_data" );
    lua_pushinteger( L, pos );
  } F4L_CATCH( L );
  return 1;
}


MOON_LOCAL int f4l_menu_clear( lua_State* L ) {
  Fl_Menu_* m = check_rw_menu( L, 1 );
  F4L_TRY( L ) {
    m->clear();
  } F4L_CATCH( L );
  lua_pushnil( L );
  moon_setuvfield( L, 1, "menu" );
  return 0;
}


MOON_LOCAL int f4l_menu_clear_submenu( lua_State* L ) {
  Fl_Menu_* m = check_rw_menu( L, 1 );
  int idx = moon_checkint( L, 2, 0, INT_MAX );
  F4L_TRY( L ) {
    int oldsize = m->size();
    luaL_argcheck( L, idx < oldsize, 2, "index too large" );
    menu_array_sync( L, 1, m, oldsize ); // pushes mirror table
    if( m->clear_submenu( idx ) == 0 ) {
      int newsize = m->size();
      table_remove( L, -1, idx+1, oldsize-newsize );
      lua_pushboolean( L, 1 );
    } else
      lua_pushnil( L );
  } F4L_CATCH( L );
  return 1;
}


MOON_LOCAL int f4l_menu_find_index( lua_State* L ) {
  Fl_Menu_* m = check_menu( L, 1 );
  char const* name = luaL_checkstring( L, 2 );
  F4L_TRY( L ) {
    int v = m->find_index( name );
    if( v >= 0 )
      lua_pushinteger( L, v );
    else
      lua_pushnil( L );
  } F4L_CATCH( L );
  return 1;
}


MOON_LOCAL int f4l_menu_insert( lua_State* L ) {
  F4L_TRY( L ) {
    Fl_Menu_* m = check_rw_menu( L, 1 );
    int msize = m->size();
    int idx = moon_checkint( L, 2, -1, INT_MAX );
    luaL_argcheck( L, idx < msize, 2, "index too large" );
    size_t n = 0;
    char const* label = luaL_checklstring( L, 3, &n );
    luaL_argcheck( L, n < 1024, 3,
                   "menu label too long (FLTK limitation)" );
    lua_settop( L, 7 );
    Fl_Shortcut sc = luaL_opt( L, f4l_check_shortcut, 4, 0 );
    int have_cb = 0;
    if( !lua_isnil( L, 5 ) ) {
      luaL_checktype( L, 5, LUA_TFUNCTION );
      have_cb = 1;
    }
    int mflags = luaL_opt( L, moon_flag_get_menu, 7, 0 );
    luaL_argcheck( L, !(mflags & FL_SUBMENU), 7,
                   "FL_SUBMENU not allowed (FLTK bug)" );
    f4l_prepare_menu_insert( L, 1, m, msize, label );
    int pos = m->insert( idx, label, sc, have_cb ? f4l_menu_callback : 0,
                         NULL, mflags );
    f4l_commit_menu_insert( L, 1, m, msize, pos );
    // set callback and user_data fields
    lua_pushvalue( L, 5 );
    lua_setfield( L, -2, "callback" );
    lua_pushvalue( L, 6 );
    lua_setfield( L, -2, "user_data" );
    lua_pushinteger( L, pos );
  } F4L_CATCH( L );
  return 1;
}


MOON_LOCAL int f4l_menu_remove( lua_State* L ) {
  Fl_Menu_* m = check_rw_menu( L, 1 );
  int idx = moon_checkint( L, 2, 0, INT_MAX );
  F4L_TRY( L ) {
    int oldsize = m->size();
    luaL_argcheck( L, idx < oldsize, 2, "index too large" );
    if( m->text( idx ) != NULL ) { // don't remove terminators
      menu_array_sync( L, 1, m, oldsize ); // pushes mirror table
      m->remove( idx );
      int newsize = m->size();
      table_remove( L, -1, idx+1, oldsize-newsize );
    }
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_menu_size( lua_State* L ) {
  Fl_Menu_* m = check_menu( L, 1 );
  int w = moon_checkint( L, 2, 0, INT_MAX );
  int h = moon_checkint( L, 3, 0, INT_MAX );
  F4L_TRY( L ) {
    m->size( w, h );
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_menu_menuitem_getp( lua_State* L ) {
  Fl_Menu_* m = check_menu( L, 1 );
  int idx = moon_checkint( L, 2, 0, INT_MAX );
  F4L_TRY( L ) {
    int size = m->size();
    luaL_argcheck( L, idx < size, 2, "index too large" );
    size_t n = 0;
    char const* key = luaL_checklstring( L, 3, &n );
    using namespace std;
    switch( n ) {
      case 4:
        if( F4L_MEMCMP( key, "text", 4 ) == 0 ) {
          char const* v = m->text( idx );
          if( v != NULL )
            lua_pushstring( L, v );
          else
            lua_pushnil( L );
          return 1;
        }
        break;
      case 5:
        if( F4L_MEMCMP( key, "flags", 5 ) == 0 ) {
          moon_flag_new_menu( L, m->mode( idx ) );
          return 1;
        } else if( F4L_MEMCMP( key, "label", 5 ) == 0 ) {
          char const* v = m->text( idx );
          if( v != NULL )
            lua_pushstring( L, v );
          else
            lua_pushnil( L );
          return 1;
        }
        break;
      case 8:
        if( F4L_MEMCMP( key, "callback", 8 ) == 0 ) {
          if( moon_getuvfield( L, 1, "menu" ) == LUA_TTABLE &&
              lua_rawgeti( L, -1, idx+1 ) == LUA_TTABLE )
            lua_getfield( L, -1, "callback" );
          else
            lua_pushnil( L );
          return 1;
        } else if( F4L_MEMCMP( key, "shortcut", 8 ) == 0 ) {
          f4l_push_shortcut( L, m->menu()[ idx ].shortcut() );
          return 1;
        }
        break;
      case 9:
        if( F4L_MEMCMP( key, "labelfont", 9 ) == 0 ) {
          f4l_push_font( L, m->menu()[ idx ].labelfont() );
          return 1;
        } else if( F4L_MEMCMP( key, "labelsize", 9 ) == 0 ) {
          lua_pushinteger( L, m->menu()[ idx ].labelsize() );
          return 1;
        } else if( F4L_MEMCMP( key, "labeltype", 9 ) == 0 ) {
          f4l_push_labeltype( L, m->menu()[ idx ].labeltype() );
          return 1;
        } else if( F4L_MEMCMP( key, "user_data", 9 ) == 0 ) {
          if( moon_getuvfield( L, 1, "menu" ) == LUA_TTABLE &&
              lua_rawgeti( L, -1, idx+1 ) == LUA_TTABLE )
            lua_getfield( L, -1, "user_data" );
          else
            lua_pushnil( L );
          return 1;
        }
        break;
      case 10:
        if( F4L_MEMCMP( key, "labelcolor", 10 ) == 0 ) {
          f4l_push_color( L, m->menu()[ idx ].labelcolor() );
          return 1;
        }
        break;
    }
    if( f4l_bad_property( L, "fltk4lua.Menu_Item", key ) )
      return 1;
  } F4L_CATCH( L );
  lua_pushnil( L );
  return 1;
}


MOON_LOCAL int f4l_menu_menuitem_setp( lua_State* L ) {
  Fl_Menu_* m = check_menu( L, 1 );
  int idx = moon_checkint( L, 2, 0, INT_MAX );
  F4L_TRY( L ) {
    int size = m->size();
    luaL_argcheck( L, idx < size, 2, "index too large" );
    luaL_argcheck( L, m->menu()[ idx ].label() != NULL, 2,
                   "can't modify terminator Menu_Item" );
    size_t n = 0;
    char const* key = luaL_checklstring( L, 3, &n );
    lua_settop( L, 4 );
    using namespace std;
    switch( n ) {
      case 4:
        if( F4L_MEMCMP( key, "text", 4 ) == 0 ) {
          char const* v = luaL_checkstring( L, 4 );
          m->replace( idx, v );
          return 0;
        }
        break;
      case 5:
        if( F4L_MEMCMP( key, "flags", 5 ) == 0 ) {
          int oldf = m->mode( idx );
          int newf = moon_flag_get_menu( L, 4 );
          luaL_argcheck( L, (oldf & FL_SUBMENU) == (newf & FL_SUBMENU),
                         4, "cannot change FL_SUBMENU flag" );
          m->mode( idx, newf );
          return 0;
        } else if( F4L_MEMCMP( key, "label", 5 ) == 0 ) {
          char const* v = luaL_checkstring( L, 4 );
          m->replace( idx, v );
          return 0;
        }
        break;
      case 8:
        if( F4L_MEMCMP( key, "callback", 8 ) == 0 ) {
          int has_cb = 0;
          luaL_argcheck( L, f4l_our_widget( L, m ), 1,
                         "internal FLTK widget" );
          if( !lua_isnoneornil( L, 4 ) ) {
            luaL_checktype( L, 4, LUA_TFUNCTION );
            has_cb = 1;
          }
          if( moon_getuvfield( L, 1, "menu" ) == LUA_TTABLE &&
              lua_rawgeti( L, -1, idx+1 ) == LUA_TTABLE ) {
            lua_pushvalue( L, 4 );
            lua_setfield( L, -2, "callback" );
            const_cast< Fl_Menu_Item* >( m->menu() )[ idx ]
              .callback( has_cb ? f4l_menu_callback : 0 );
          } else
            luaL_error( L, "menu item %d doesn't have a uservalue table",
                        idx );
          return 0;
        } else if( F4L_MEMCMP( key, "shortcut", 8 ) == 0 ) {
          m->shortcut( idx, f4l_check_shortcut( L, 4 ) );
          return 0;
        }
        break;
      case 9:
        if( F4L_MEMCMP( key, "labelfont", 9 ) == 0 ) {
          const_cast< Fl_Menu_Item* >( m->menu() )[ idx ]
            .labelfont( f4l_check_font( L, 4 ) );
          return 0;
        } else if( F4L_MEMCMP( key, "labelsize", 9 ) == 0 ) {
          const_cast< Fl_Menu_Item* >( m->menu() )[ idx ]
            .labelsize( moon_checkint( L, 4, 0, INT_MAX ) );
          return 0;
        } else if( F4L_MEMCMP( key, "labeltype", 9 ) == 0 ) {
          Fl_Labeltype t = f4l_check_labeltype( L, 4 );
          luaL_argcheck( L, t != _FL_IMAGE_LABEL, 4,
                         "this labeltype is invalid here" );
          const_cast< Fl_Menu_Item* >( m->menu() )[ idx ]
            .labeltype( t );
          return 0;
        } else if( F4L_MEMCMP( key, "user_data", 9 ) == 0 ) {
          if( moon_getuvfield( L, 1, "menu" ) == LUA_TTABLE &&
              lua_rawgeti( L, -1, idx+1 ) == LUA_TTABLE ) {
            lua_pushvalue( L, 4 );
            lua_setfield( L, -2, "user_data" );
          } else
            luaL_error( L, "menu item %d doesn't have a uservalue table",
                        idx );
          return 0;
        }
        // we don't set labeltype for now, because it can cause memory
        // corruption when used with images!
        break;
      case 10:
        if( F4L_MEMCMP( key, "labelcolor", 10 ) == 0 ) {
          const_cast< Fl_Menu_Item* >( m->menu() )[ idx ]
            .labelcolor( f4l_check_color( L, 4 ) );
          return 0;
        }
        break;
    }
    f4l_bad_property( L, "fltk4lua.Menu_Item", key );
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_menu_menuitem_activate( lua_State* L ) {
  Fl_Menu_* m = check_menu( L, 1 );
  int idx = moon_checkint( L, 2, 0, INT_MAX );
  F4L_TRY( L ) {
    int size = m->size();
    luaL_argcheck( L, idx < size, 2, "index too large" );
    const_cast< Fl_Menu_Item* >( m->menu() )[ idx ]
      .activate();
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_menu_menuitem_active( lua_State* L ) {
  Fl_Menu_* m = check_menu( L, 1 );
  int idx = moon_checkint( L, 2, 0, INT_MAX );
  F4L_TRY( L ) {
    int size = m->size();
    luaL_argcheck( L, idx < size, 2, "index too large" );
    int v = const_cast< Fl_Menu_Item* >( m->menu() )[ idx ]
      .active();
    lua_pushboolean( L, v );
  } F4L_CATCH( L );
  return 1;
}


MOON_LOCAL int f4l_menu_menuitem_activevisible( lua_State* L ) {
  Fl_Menu_* m = check_menu( L, 1 );
  int idx = moon_checkint( L, 2, 0, INT_MAX );
  F4L_TRY( L ) {
    int size = m->size();
    luaL_argcheck( L, idx < size, 2, "index too large" );
    int v = const_cast< Fl_Menu_Item* >( m->menu() )[ idx ]
      .activevisible();
    lua_pushboolean( L, v );
  } F4L_CATCH( L );
  return 1;
}


MOON_LOCAL int f4l_menu_menuitem_checkbox( lua_State* L ) {
  Fl_Menu_* m = check_menu( L, 1 );
  int idx = moon_checkint( L, 2, 0, INT_MAX );
  F4L_TRY( L ) {
    int size = m->size();
    luaL_argcheck( L, idx < size, 2, "index too large" );
    int v = const_cast< Fl_Menu_Item* >( m->menu() )[ idx ]
      .checkbox();
    lua_pushboolean( L, v );
  } F4L_CATCH( L );
  return 1;
}


MOON_LOCAL int f4l_menu_menuitem_clear( lua_State* L ) {
  Fl_Menu_* m = check_menu( L, 1 );
  int idx = moon_checkint( L, 2, 0, INT_MAX );
  F4L_TRY( L ) {
    int size = m->size();
    luaL_argcheck( L, idx < size, 2, "index too large" );
    const_cast< Fl_Menu_Item* >( m->menu() )[ idx ]
      .clear();
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_menu_menuitem_deactivate( lua_State* L ) {
  Fl_Menu_* m = check_menu( L, 1 );
  int idx = moon_checkint( L, 2, 0, INT_MAX );
  F4L_TRY( L ) {
    int size = m->size();
    luaL_argcheck( L, idx < size, 2, "index too large" );
    const_cast< Fl_Menu_Item* >( m->menu() )[ idx ]
      .deactivate();
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_menu_menuitem_hide( lua_State* L ) {
  Fl_Menu_* m = check_menu( L, 1 );
  int idx = moon_checkint( L, 2, 0, INT_MAX );
  F4L_TRY( L ) {
    int size = m->size();
    luaL_argcheck( L, idx < size, 2, "index too large" );
    const_cast< Fl_Menu_Item* >( m->menu() )[ idx ]
      .hide();
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_menu_menuitem_radio( lua_State* L ) {
  Fl_Menu_* m = check_menu( L, 1 );
  int idx = moon_checkint( L, 2, 0, INT_MAX );
  F4L_TRY( L ) {
    int size = m->size();
    luaL_argcheck( L, idx < size, 2, "index too large" );
    int v = const_cast< Fl_Menu_Item* >( m->menu() )[ idx ]
      .radio();
    lua_pushboolean( L, v );
  } F4L_CATCH( L );
  return 1;
}


MOON_LOCAL int f4l_menu_menuitem_set( lua_State* L ) {
  Fl_Menu_* m = check_menu( L, 1 );
  int idx = moon_checkint( L, 2, 0, INT_MAX );
  F4L_TRY( L ) {
    int size = m->size();
    luaL_argcheck( L, idx < size, 2, "index too large" );
    const_cast< Fl_Menu_Item* >( m->menu() )[ idx ]
      .set();
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_menu_menuitem_setonly( lua_State* L ) {
  Fl_Menu_* m = check_menu( L, 1 );
  int idx = moon_checkint( L, 2, 0, INT_MAX );
  F4L_TRY( L ) {
    int size = m->size();
    luaL_argcheck( L, idx < size, 2, "index too large" );
    const_cast< Fl_Menu_Item* >( m->menu() )[ idx ]
      .setonly();
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_menu_menuitem_show( lua_State* L ) {
  Fl_Menu_* m = check_menu( L, 1 );
  int idx = moon_checkint( L, 2, 0, INT_MAX );
  F4L_TRY( L ) {
    int size = m->size();
    luaL_argcheck( L, idx < size, 2, "index too large" );
    const_cast< Fl_Menu_Item* >( m->menu() )[ idx ]
      .show();
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_menu_menuitem_submenu( lua_State* L ) {
  Fl_Menu_* m = check_menu( L, 1 );
  int idx = moon_checkint( L, 2, 0, INT_MAX );
  F4L_TRY( L ) {
    int size = m->size();
    luaL_argcheck( L, idx < size, 2, "index too large" );
    int v = const_cast< Fl_Menu_Item* >( m->menu() )[ idx ]
      .submenu();
    lua_pushboolean( L, v );
  } F4L_CATCH( L );
  return 1;
}


MOON_LOCAL int f4l_menu_menuitem_value( lua_State* L ) {
  Fl_Menu_* m = check_menu( L, 1 );
  int idx = moon_checkint( L, 2, 0, INT_MAX );
  F4L_TRY( L ) {
    int size = m->size();
    luaL_argcheck( L, idx < size, 2, "index too large" );
    int v = const_cast< Fl_Menu_Item* >( m->menu() )[ idx ]
      .value();
    lua_pushboolean( L, v );
  } F4L_CATCH( L );
  return 1;
}


MOON_LOCAL int f4l_menu_menuitem_visible( lua_State* L ) {
  Fl_Menu_* m = check_menu( L, 1 );
  int idx = moon_checkint( L, 2, 0, INT_MAX );
  F4L_TRY( L ) {
    int size = m->size();
    luaL_argcheck( L, idx < size, 2, "index too large" );
    int v = const_cast< Fl_Menu_Item* >( m->menu() )[ idx ]
      .visible();
    lua_pushboolean( L, v );
  } F4L_CATCH( L );
  return 1;
}

F4L_LUA_LLINKAGE_END


MOON_LOCAL void f4l_menu_setup( lua_State* L ) {
  moon_flag_def_menu( L );
#define GEN_UDATA( _a, _b ) \
  (moon_flag_new_menu( L, _b ), lua_setfield( L, -2, _a ));
  MENU_FLAG_LIST( GEN_UDATA )
#undef GEN_UDATA
}

