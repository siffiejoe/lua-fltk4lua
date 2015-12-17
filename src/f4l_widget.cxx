#include "fltk4lua.hxx"
#include "f4l_widget.hxx"
#include "f4l_enums.hxx"
#include <cstring>
#include <climits>


namespace {

  inline Fl_Widget* check_widget( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_WIDGET_NAME );
    return static_cast< Fl_Widget* >( p );
  }

  inline Fl_Image* check_image( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_IMAGE_NAME );
    return static_cast< Fl_Image* >( p );
  }


  void f4l_widget_callback( Fl_Widget* w, void* ud ) {
    f4l_active_L* th = static_cast< f4l_active_L* >( ud );
    if( th != NULL && th->cb_L != NULL ) {
      lua_State* L = th->cb_L;
      luaL_checkstack( L, 5, "f4l_widget_callback" );
      int top = lua_gettop( L );
      lua_pushcfunction( L, f4l_backtrace );
      f4l_push_widget( L, w );
      lua_pushvalue( L, -1 ); // widget, widget
      moon_object_header* h = NULL;
      h = static_cast< moon_object_header* >( lua_touserdata( L, -2 ) );
      if( moon_getuvfield( L, -1, "callback" ) == LUA_TFUNCTION ) {
        lua_insert( L, -2 ); // widget, callback, widget
        if( moon_getuvfield( L, -1, "user_data" ) == LUA_TNIL )
          lua_pushnil( L );
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
      lua_settop( L, top );
    }
  }

} // anonymous namespace


F4L_LUA_LLINKAGE_BEGIN

static int widget_label_shortcut( lua_State* L ) {
  char const* t = luaL_checkstring( L, 1 );
  F4L_TRY( L ) {
    lua_pushinteger( L, Fl_Widget::label_shortcut( t ) );
  } F4L_CATCH( L );
  return 1;
}


MOON_LOCAL int f4l_widget_activate( lua_State* L ) {
  Fl_Widget* widget = check_widget( L, 1 );
  F4L_TRY( L ) {
    widget->activate();
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_widget_clear_changed( lua_State* L ) {
  Fl_Widget* widget = check_widget( L, 1 );
  F4L_TRY( L ) {
    widget->clear_changed();
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_widget_clear_damage( lua_State* L ) {
  Fl_Widget* widget = check_widget( L, 1 );
  F4L_TRY( L ) {
    widget->clear_damage();
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_widget_clear_output( lua_State* L ) {
  Fl_Widget* widget = check_widget( L, 1 );
  F4L_TRY( L ) {
    widget->clear_output();
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_widget_clear_visible( lua_State* L ) {
  Fl_Widget* widget = check_widget( L, 1 );
  F4L_TRY( L ) {
    widget->clear_visible();
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_widget_clear_visible_focus( lua_State* L ) {
  Fl_Widget* widget = check_widget( L, 1 );
  F4L_TRY( L ) {
    widget->clear_visible_focus();
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_widget_contains( lua_State* L ) {
  Fl_Widget* widget = check_widget( L, 1 );
  Fl_Widget* widget2 = check_widget( L, 2 );
  F4L_TRY( L ) {
    lua_pushboolean( L, widget->contains( widget2 ) );
  } F4L_CATCH( L );
  return 1;
}


MOON_LOCAL int f4l_widget_deactivate( lua_State* L ) {
  Fl_Widget* widget = check_widget( L, 1 );
  F4L_TRY( L ) {
    widget->deactivate();
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_widget_hide( lua_State* L ) {
  Fl_Widget* widget = check_widget( L, 1 );
  F4L_TRY( L ) {
    widget->hide();
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_widget_inside( lua_State* L ) {
  Fl_Widget* widget = check_widget( L, 1 );
  Fl_Widget* widget2 = luaL_opt( L, check_widget, 2, NULL );
  F4L_TRY( L ) {
    lua_pushboolean( L, widget->inside( widget2 ) );
  } F4L_CATCH( L );
  return 1;
}


MOON_LOCAL int f4l_widget_measure_label( lua_State* L ) {
  Fl_Widget* widget = check_widget( L, 1 );
  int x = moon_optint( L, 2, 0, INT_MAX, 0 ), y = 0;
  F4L_TRY( L ) {
    widget->measure_label( x, y );
  } F4L_CATCH( L );
  lua_pushinteger( L, x );
  lua_pushinteger( L, y );
  return 2;
}


MOON_LOCAL int f4l_widget_position( lua_State* L ) {
  Fl_Widget* widget = check_widget( L, 1 );
  int x = moon_checkint( L, 2, 0, INT_MAX );
  int y = moon_checkint( L, 3, 0, INT_MAX );
  F4L_TRY( L ) {
    widget->position( x, y );
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_widget_redraw( lua_State* L ) {
  Fl_Widget* widget = check_widget( L, 1 );
  F4L_TRY( L ) {
    widget->redraw();
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_widget_redraw_label( lua_State* L ) {
  Fl_Widget* widget = check_widget( L, 1 );
  F4L_TRY( L ) {
    widget->redraw_label();
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_widget_resize( lua_State* L ) {
  Fl_Widget* widget = check_widget( L, 1 );
  int x = moon_checkint( L, 2, 0, INT_MAX );
  int y = moon_checkint( L, 3, 0, INT_MAX );
  int w = moon_checkint( L, 4, 0, INT_MAX );
  int h = moon_checkint( L, 5, 0, INT_MAX );
  F4L_TRY( L ) {
    widget->resize( x, y, w, h );
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_widget_set_changed( lua_State* L ) {
  Fl_Widget* widget = check_widget( L, 1 );
  F4L_TRY( L ) {
    widget->set_changed();
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_widget_set_output( lua_State* L ) {
  Fl_Widget* widget = check_widget( L, 1 );
  F4L_TRY( L ) {
    widget->set_output();
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_widget_set_visible( lua_State* L ) {
  Fl_Widget* widget = check_widget( L, 1 );
  F4L_TRY( L ) {
    widget->set_visible();
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_widget_set_visible_focus( lua_State* L ) {
  Fl_Widget* widget = check_widget( L, 1 );
  F4L_TRY( L ) {
    widget->set_visible_focus();
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_widget_show( lua_State* L ) {
  Fl_Widget* widget = check_widget( L, 1 );
  F4L_TRY( L ) {
    widget->show();
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_widget_size( lua_State* L ) {
  Fl_Widget* widget = check_widget( L, 1 );
  int w = moon_checkint( L, 2, 0, INT_MAX );
  int h = moon_checkint( L, 3, 0, INT_MAX );
  F4L_TRY( L ) {
    widget->size( w, h );
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_widget_take_focus( lua_State* L ) {
  Fl_Widget* widget = check_widget( L, 1 );
  F4L_TRY( L ) {
    lua_pushboolean( L, widget->take_focus() );
  } F4L_CATCH( L );
  return 1;
}

F4L_LUA_LLINKAGE_END


MOON_LOCAL void f4l_register_widget( lua_State* L, Fl_Widget* w,
                                     int setud ) {
  luaL_checkstack( L, 3, "f4l_register_widget" );
  moon_getcache( L, LUA_REGISTRYINDEX );
  lua_pushvalue( L, -2 ); // duplicate widget userdata on stack top
  lua_rawsetp( L, -2, static_cast< void* >( w ) );
  /* add the widget to the parent's uservalue table as a convenience,
   * so that you don't have to keep all created widgets in variables
   * to prevent them from being garbage collected */
  Fl_Widget* parent = w->parent();
  if( parent != NULL ) {
    lua_rawgetp( L, -1, static_cast< void* >( parent ) );
    lua_replace( L, -2 );
    if( lua_type( L, -1 ) == LUA_TUSERDATA ) {
      lua_getuservalue( L, -1 );
      lua_replace( L, -2 );
      lua_pushvalue( L, -2 ); // duplicate widget userdata
      lua_rawsetp( L, -2, static_cast< void* >( w ) );
    }
  }
  lua_pop( L, 1 ); // pop cache *or* parent *or* uservalue
  /* all widgets created directly by fltk4lua have the active thread
   * pointer stored as (FLTK) user_data for use in callbacks */
  if( setud ) {
    w->user_data( static_cast< void* >( f4l_get_active_thread( L ) ) );
    lua_pop( L, 1 ); // pop active thread pointer
  }
}


MOON_LOCAL void f4l_push_widget( lua_State* L, Fl_Widget* w ) {
  if( w == NULL )
    lua_pushnil( L );
  else {
    luaL_checkstack( L, 2, "f4l_push_widget" );
    moon_getcache( L, LUA_REGISTRYINDEX );
    lua_rawgetp( L, -1, static_cast< void* >( w ) );
    lua_replace( L, -2 );
    if( lua_type( L, -1 ) != LUA_TUSERDATA ) {
      lua_pop( L, 1 );
      luaL_error( L, "unknown Fl_Widget pointer" );
    }
  }
}


MOON_LOCAL int f4l_our_widget( lua_State* L, Fl_Widget* w ) {
  void* p1 = static_cast< void* >( f4l_get_active_thread( L ) );
  void* ud = w->user_data();
  int v = p1 == ud;
  lua_pop( L, 1 );
  return v;
}


MOON_LOCAL int f4l_widget_index_( lua_State* L, Fl_Widget* w,
                                  char const* key, size_t n ) {
  using namespace std;
  switch( n ) {
    case 1:
      switch( *key ) {
        case 'x':
          lua_pushinteger( L, w->x() );
          return 1;
        case 'y':
          lua_pushinteger( L, w->y() );
          return 1;
        case 'w':
          lua_pushinteger( L, w->w() );
          return 1;
        case 'h':
          lua_pushinteger( L, w->h() );
          return 1;
      }
      break;
    case 3:
      if( F4L_MEMCMP( key, "box", 3 ) == 0 ) {
        f4l_push_boxtype( L, w->box() );
        return 1;
      }
      break;
    case 4:
      if( F4L_MEMCMP( key, "when", 4 ) == 0 ) {
        f4l_push_when( L, w->when() );
        return 1;
      }
      break;
    case 5:
      if( F4L_MEMCMP( key, "align", 5 ) == 0 ) {
        f4l_push_align( L, w->align() );
        return 1;
      } else if( F4L_MEMCMP( key, "color", 5 ) == 0 ) {
        f4l_push_color( L, w->color() );
        return 1;
      } else if( F4L_MEMCMP( key, "image", 5 ) == 0 ) {
        if( moon_getuvfield( L, 1, "image" ) == LUA_TNIL )
          lua_pushnil( L );
        return 1;
      } else if( F4L_MEMCMP( key, "label", 5 ) == 0 ) {
        char const* l = w->label();
        if( l )
          lua_pushstring( L, l );
        else
          lua_pushliteral( L, "" );
        return 1;
      }
      break;
    case 6:
      if( F4L_MEMCMP( key, "active", 6 ) == 0 ) {
        lua_pushboolean( L, w->active() );
        return 1;
      } else if( F4L_MEMCMP( key, "output", 6 ) == 0 ) {
        lua_pushboolean( L, w->output() );
        return 1;
      } else if( F4L_MEMCMP( key, "parent", 6 ) == 0 ) {
        f4l_push_widget( L, w->parent() );
        return 1;
      }
      break;
    case 7:
      if( F4L_MEMCMP( key, "changed", 7 ) == 0 ) {
        lua_pushboolean( L, w->changed() );
        return 1;
      } else if( F4L_MEMCMP( key, "deimage", 7 ) == 0 ) {
        if( moon_getuvfield( L, 1, "deimage" ) == LUA_TNIL )
          lua_pushnil( L );
        return 1;
      } else if( F4L_MEMCMP( key, "tooltip", 7 ) == 0 ) {
        char const* t = w->tooltip();
        if( t )
          lua_pushstring( L, t );
        else
          lua_pushliteral( L, "" );
        return 1;
      } else if( F4L_MEMCMP( key, "visible", 7 ) == 0 ) {
        lua_pushboolean( L, w->visible() );
        return 1;
      }
      break;
    case 8:
      if( F4L_MEMCMP( key, "active_r", 8 ) == 0 ) {
        lua_pushboolean( L, w->active_r() );
        return 1;
      } else if( F4L_MEMCMP( key, "callback", 8 ) == 0 ) {
        if( moon_getuvfield( L, 1, "callback" ) == LUA_TNIL )
          lua_pushnil( L );
        return 1;
      }
      break;
    case 9:
      if( F4L_MEMCMP( key, "labelfont", 9 ) == 0 ) {
        f4l_push_font( L, w->labelfont() );
        return 1;
      } else if( F4L_MEMCMP( key, "labelsize", 9 ) == 0 ) {
        lua_pushinteger( L, w->labelsize() );
        return 1;
      } else if( F4L_MEMCMP( key, "labeltype", 9 ) == 0 ) {
        f4l_push_labeltype( L, w->labeltype() );
        return 1;
      } else if( F4L_MEMCMP( key, "user_data", 9 ) == 0 ) {
        if( moon_getuvfield( L, 1, "user_data" ) == LUA_TNIL )
          lua_pushnil( L );
        return 1;
      } else if( F4L_MEMCMP( key, "visible_r", 9 ) == 0 ) {
        lua_pushboolean( L, w->visible_r() );
        return 1;
      }
      break;
    case 10:
      if( F4L_MEMCMP( key, "labelcolor", 10 ) == 0 ) {
        f4l_push_color( L, w->labelcolor() );
        return 1;
      }
      break;
    case 11:
      if( F4L_MEMCMP( key, "takesevents", 11 ) == 0 ) {
        lua_pushboolean( L, w->takesevents() );
        return 1;
      }
      break;
    case 13:
      if( F4L_MEMCMP( key, "visible_focus", 13 ) == 0 ) {
        lua_pushboolean( L, w->visible_focus() );
        return 1;
      }
      break;
    case 15:
      if( F4L_MEMCMP( key, "selection_color", 15 ) == 0 ) {
        f4l_push_color( L, w->selection_color() );
        return 1;
      }
      break;
  }
  return 0;
}


MOON_LOCAL int f4l_widget_newindex_( lua_State* L, Fl_Widget* w,
                                     char const* key, size_t n ) {
  using namespace std;
  switch( n ) {
    case 3:
      if( F4L_MEMCMP( key, "box", 3 ) == 0 ) {
        w->box( f4l_check_boxtype( L, 3 ) );
        return 1;
      }
      break;
    case 4:
      if( F4L_MEMCMP( key, "when", 4 ) == 0 ) {
        w->when( f4l_check_when( L, 3 ) );
        return 1;
      }
      break;
    case 5:
      if( F4L_MEMCMP( key, "align", 5 ) == 0 ) {
        w->align( f4l_check_align( L, 3 ) );
        return 1;
      } else if( F4L_MEMCMP( key, "color", 5 ) == 0 ) {
        w->color( f4l_check_color( L, 3 ) );
        return 1;
      } else if( F4L_MEMCMP( key, "image", 5 ) == 0 ) {
        Fl_Image* img = luaL_opt( L, check_image, 3, NULL );
        lua_settop( L, 3 );
        moon_setuvfield( L, 1, "image" );
        w->image( img );
        return 1;
      } else if( F4L_MEMCMP( key, "label", 5 ) == 0 ) {
        char const* s = luaL_checkstring( L, 3 );
        lua_pushvalue( L, 3 );
        moon_setuvfield( L, 1, "label" );
        w->label( s );
        return 1;
      }
      break;
    case 7:
      if( F4L_MEMCMP( key, "deimage", 7 ) == 0 ) {
        Fl_Image* img = luaL_opt( L, check_image, 3, NULL );
        lua_settop( L, 3 );
        moon_setuvfield( L, 1, "deimage" );
        w->deimage( img );
        return 1;
      } else if( F4L_MEMCMP( key, "tooltip", 7 ) == 0 ) {
        char const* s = luaL_checkstring( L, 3 );
        lua_pushvalue( L, 3 );
        moon_setuvfield( L, 1, "tooltip" );
        w->tooltip( s );
        return 1;
      }
      break;
    case 8:
      if( F4L_MEMCMP( key, "callback", 8 ) == 0 ) {
        luaL_argcheck( L, f4l_our_widget( L, w ), 1,
                       "internal FLTK widget" );
        if( !lua_isnoneornil( L, 3 ) )
          luaL_checktype( L, 3, LUA_TFUNCTION );
        lua_settop( L, 3 );
        moon_setuvfield( L, 1, "callback" );
        w->callback( f4l_widget_callback );
        return 1;
      }
      break;
    case 9:
      if( F4L_MEMCMP( key, "labelfont", 9 ) == 0 ) {
        w->labelfont( f4l_check_font( L, 3 ) );
        return 1;
      } else if( F4L_MEMCMP( key, "labelsize", 9 ) == 0 ) {
        w->labelsize( (Fl_Fontsize)moon_checkint( L, 3, 0, INT_MAX ) );
        return 1;
      } else if( F4L_MEMCMP( key, "labeltype", 9 ) == 0 ) {
        w->labeltype( f4l_check_labeltype( L, 3 ) );
        return 1;
      } else if( F4L_MEMCMP( key, "user_data", 9 ) == 0 ) {
        lua_settop( L, 3 );
        moon_setuvfield( L, 1, "user_data" );
        return 1;
      }
      break;
    case 10:
      if( F4L_MEMCMP( key, "labelcolor", 10 ) == 0 ) {
        w->labelcolor( f4l_check_color( L, 3 ) );
        return 1;
      }
      break;
    case 13:
      if( F4L_MEMCMP( key, "visible_focus", 13 ) == 0 ) {
        w->visible_focus( lua_toboolean( L, 3 ) );
        return 1;
      }
      break;
    case 15:
      if( F4L_MEMCMP( key, "selection_color", 15 ) == 0 ) {
        w->selection_color( f4l_check_color( L, 3 ) );
        return 1;
      }
      break;
  }
  return 0;
}


MOON_LOCAL void f4l_widget_setup( lua_State* L ) {
  luaL_Reg const classmethods[] = {
    { "label_shortcut", widget_label_shortcut },
    { NULL, NULL }
  };
  f4l_new_class_table( L, "Widget", 0, classmethods );
}

