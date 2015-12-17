#include "fltk4lua.hxx"
#include "f4l_group.hxx"
#include "f4l_widget.hxx"
#include "f4l_enums.hxx"
#include <FL/Fl_Scroll.H>


#define TYPE_LIST( _ ) \
  _( "NO_SCROLLBARS", 0 ) \
  _( "HORIZONTAL", Fl_Scroll::HORIZONTAL ) \
  _( "VERTICAL", Fl_Scroll::VERTICAL ) \
  _( "BOTH", Fl_Scroll::BOTH ) \
  _( "HORIZONTAL_ALWAYS", Fl_Scroll::HORIZONTAL_ALWAYS ) \
  _( "VERTICAL_ALWAYS", Fl_Scroll::VERTICAL_ALWAYS ) \
  _( "BOTH_ALWAYS", Fl_Scroll::BOTH_ALWAYS )

  F4L_GEN_TYPE_ENUM( TYPE_LIST, scroll )


namespace {

  inline Fl_Scroll* check_scroll( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_SCROLL_NAME );
    return static_cast< Fl_Scroll* >( p );
  }


  int scroll_index_( lua_State* L, Fl_Scroll* s,
                     char const* key, size_t n ) {
    using namespace std;
    switch( n ) {
      case 4:
        if( F4L_MEMCMP( key, "type", 4 ) == 0 ) {
          f4l_push_type_scroll( L, s->type() );
          return 1;
        }
        break;
      case 9:
        if( F4L_MEMCMP( key, "scrollbar", 9 ) == 0 ) {
          if( moon_getuvfield( L, 1, "scrollbar" ) == LUA_TNIL ) {
            f4l_new_member< Fl_Scrollbar >( L, F4L_SCROLLBAR_NAME,
                                            &s->scrollbar, 1 );
            lua_pushvalue( L, -1 );
            moon_setuvfield( L, 1, "scrollbar" );
          }
          return 1;
        } else if( F4L_MEMCMP( key, "xposition", 9 ) == 0 ) {
          lua_pushinteger( L, s->xposition() );
          return 1;
        } else if( F4L_MEMCMP( key, "yposition", 9 ) == 0 ) {
          lua_pushinteger( L, s->yposition() );
          return 1;
        }
        break;
      case 10:
        if( F4L_MEMCMP( key, "hscrollbar", 10 ) == 0 ) {
          if( moon_getuvfield( L, 1, "hscrollbar" ) == LUA_TNIL ) {
            f4l_new_member< Fl_Scrollbar >( L, F4L_SCROLLBAR_NAME,
                                            &s->hscrollbar, 1 );
            lua_pushvalue( L, -1 );
            moon_setuvfield( L, 1, "hscrollbar" );
          }
          return 1;
        }
        break;
      case 14:
        if( F4L_MEMCMP( key, "scrollbar_size", 14 ) == 0 ) {
          lua_pushinteger( L, s->scrollbar_size() );
          return 1;
        }
        break;
    }
    return 0;
  }


  int scroll_newindex_( lua_State* L, Fl_Scroll* s,
                        char const* key, size_t n ) {
    using namespace std;
    switch( n ) {
      case 4:
        if( F4L_MEMCMP( key, "type", 4 ) == 0 ) {
          s->type( f4l_check_type_scroll( L, 3 ) );
          return 1;
        }
        break;
      case 14:
        if( F4L_MEMCMP( key, "scrollbar_size", 14 ) == 0 ) {
          s->scrollbar_size( moon_checkint( L, 3, 0, INT_MAX ) );
          return 1;
        }
        break;
    }
    return 0;
  }

} // anonymous namespace


F4L_DEF_DELETE( Fl_Scroll )


F4L_LUA_LLINKAGE_BEGIN

static int new_scroll( lua_State* L ) {
  F4L_TRY( L ) {
    Fl_Scroll* s = f4l_new_widget< Fl_Scroll >( L, F4L_SCROLL_NAME,
                                                f4l_delete_Fl_Scroll );
    /* The __index handler would create those objects on demand,
     * but the scrollbars are stored in the group's children, so an
     * error could be thrown if they are encountered there before
     * having a corresponding userdata registered! */
    f4l_new_member< Fl_Scrollbar >( L, F4L_SCROLLBAR_NAME,
                                    &s->hscrollbar, -1 );
    moon_setuvfield( L, -2, "hscrollbar" );
    f4l_new_member< Fl_Scrollbar >( L, F4L_SCROLLBAR_NAME,
                                    &s->scrollbar, -1 );
    moon_setuvfield( L, -2, "scrollbar" );
  } F4L_CATCH( L );
  return 1;
}


static int scroll_index( lua_State* L ) {
  Fl_Scroll* s = check_scroll( L, 1 );
  size_t n = 0;
  char const* key = luaL_checklstring( L, 2, &n );
  F4L_TRY( L ) {
    if( !scroll_index_( L, s, key, n ) &&
        !f4l_group_index_( L, s, key, n ) &&
        !f4l_widget_index_( L, s, key, n ) &&
        !f4l_bad_property( L, F4L_SCROLL_NAME, key ) )
      lua_pushnil( L );
  } F4L_CATCH( L );
  return 1;
}


static int scroll_newindex( lua_State* L ) {
  Fl_Scroll* s = check_scroll( L, 1 );
  size_t n = 0;
  char const* key = luaL_checklstring( L, 2, &n );
  F4L_TRY( L ) {
    (void)(scroll_newindex_( L, s, key, n ) ||
           f4l_group_newindex_( L, s, key, n ) ||
           f4l_widget_newindex_( L, s, key, n ) ||
           f4l_bad_property( L, F4L_SCROLL_NAME, key ));
  } F4L_CATCH( L );
  return 0;
}


static int scroll_clear( lua_State* L ) {
  Fl_Scroll* s = check_scroll( L, 1 );
  lua_getuservalue( L, 1 );
  F4L_TRY( L ) {
    int n = s->children();
    for( int i = n; i > 0; --i ) {
      Fl_Widget* w = s->child( i-1 );
      s->remove( i-1 );
      lua_pushnil( L );
      lua_rawsetp( L, -2, static_cast< void* >( w ) );
    }
    s->add( s->hscrollbar );
    s->add( s->scrollbar );
  } F4L_CATCH( L );
  lua_pop( L, 1 );
  return 0;
}


static int scroll_scroll_to( lua_State* L ) {
  Fl_Scroll* s = check_scroll( L, 1 );
  int w = moon_checkint( L, 2, 0, INT_MAX );
  int h = moon_checkint( L, 3, 0, INT_MAX );
  F4L_TRY( L ) {
    s->scroll_to( w, h );
  } F4L_CATCH( L );
  return 0;
}
F4L_LUA_LLINKAGE_END


F4L_DEF_CAST( Fl_Scroll, Fl_Group )
F4L_DEF_CAST( Fl_Scroll, Fl_Widget )


MOON_LOCAL void f4l_scroll_setup( lua_State* L ) {
  luaL_Reg const methods[] = {
    F4L_WIDGET_METHODS,
    F4L_GROUP_METHODS,
    { "clear", scroll_clear },
    { "scroll_to", scroll_scroll_to },
    { "__index", scroll_index },
    { "__newindex", scroll_newindex },
    { NULL, NULL }
  };
  moon_defobject( L, F4L_SCROLL_NAME, 0, methods, 0 );
  moon_defcast( L, F4L_SCROLL_NAME, F4L_GROUP_NAME,
                f4l_cast_Fl_Scroll_Fl_Group );
  moon_defcast( L, F4L_SCROLL_NAME, F4L_WIDGET_NAME,
                f4l_cast_Fl_Scroll_Fl_Widget );
  f4l_new_class_table( L, "Scroll", new_scroll );
}

