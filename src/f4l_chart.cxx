#include "fltk4lua.hxx"
#include "f4l_widget.hxx"
#include "f4l_enums.hxx"
#include <FL/Fl_Chart.H>


#define TYPE_LIST( _ ) \
  _( "FL_BAR_CHART", FL_BAR_CHART ) \
  _( "FL_FILLED_CHART", FL_FILLED_CHART ) \
  _( "FL_HORBAR_CHART", FL_HORBAR_CHART ) \
  _( "FL_LINE_CHART", FL_LINE_CHART ) \
  _( "FL_PIE_CHART", FL_PIE_CHART ) \
  _( "FL_SPECIALPIE_CHART", FL_SPECIALPIE_CHART ) \
  _( "FL_SPIKE_CHART", FL_SPIKE_CHART )

  F4L_GEN_TYPE_ENUM( TYPE_LIST, chart )


namespace {

  inline Fl_Chart* check_chart( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_CHART_NAME );
    return static_cast< Fl_Chart* >( p );
  }


  int chart_index_( lua_State* L, Fl_Chart* c,
                    char const* key, size_t n ) {
    using namespace std;
    switch( n ) {
      case 4:
        if( F4L_MEMCMP( key, "type", 4 ) == 0 ) {
          f4l_push_type_chart( L, c->type() );
          return 1;
        }
        break;
      case 7:
        if( F4L_MEMCMP( key, "maxsize", 7 ) == 0 ) {
          lua_pushinteger( L, c->maxsize() );
          return 1;
        }
        break;
      case 8:
        if( F4L_MEMCMP( key, "autosize", 8 ) == 0 ) {
          lua_pushboolean( L, c->autosize() );
          return 1;
        } else if( F4L_MEMCMP( key, "textfont", 8 ) == 0 ) {
          f4l_push_font( L, c->textfont() );
          return 1;
        } else if( F4L_MEMCMP( key, "textsize", 8 ) == 0 ) {
          lua_pushinteger( L, c->textsize() );
          return 1;
        }
        break;
      case 9:
        if( F4L_MEMCMP( key, "textcolor", 9 ) == 0 ) {
          f4l_push_color( L, c->textcolor() );
          return 1;
        }
        break;
      case 10:
        if( F4L_MEMCMP( key, "chart_size", 10 ) == 0 ) {
          lua_pushinteger( L, c->size() );
          return 1;
        }
        break;
    }
    return 0;
  }


  int chart_newindex_( lua_State* L, Fl_Chart* c,
                       char const* key, size_t n ) {
    using namespace std;
    switch( n ) {
      case 4:
        if( F4L_MEMCMP( key, "type", 4 ) == 0 ) {
          c->type( f4l_check_type_chart( L, 3 ) );
          return 1;
        }
        break;
      case 7:
        if( F4L_MEMCMP( key, "maxsize", 7 ) == 0 ) {
          c->maxsize( moon_checkint( L, 3, 0, INT_MAX ) );
          return 1;
        }
        break;
      case 8:
        if( F4L_MEMCMP( key, "autosize", 8 ) == 0 ) {
          c->autosize( lua_toboolean( L, 3 ) );
          return 1;
        } else if( F4L_MEMCMP( key, "textfont", 8 ) == 0 ) {
          c->textfont( f4l_check_font( L, 3 ) );
          return 1;
        } else if( F4L_MEMCMP( key, "textsize", 8 ) == 0 ) {
          c->textsize( moon_checkint( L, 3, 0, INT_MAX ) );
          return 1;
        }
        break;
      case 9:
        if( F4L_MEMCMP( key, "textcolor", 9 ) == 0 ) {
          c->textcolor( f4l_check_color( L, 3 ) );
          return 1;
        }
        break;
    }
    return 0;
  }

} // anonymous namespace


F4L_DEF_DELETE( Fl_Chart )


F4L_LUA_LLINKAGE_BEGIN

static int new_chart( lua_State* L ) {
  F4L_TRY( L ) {
    f4l_new_widget< Fl_Chart >( L, F4L_CHART_NAME,
                                f4l_delete_Fl_Chart );
  } F4L_CATCH( L );
  return 1;
}


static int chart_index( lua_State* L ) {
  Fl_Chart* c = check_chart( L, 1 );
  size_t n = 0;
  char const* key = luaL_checklstring( L, 2, &n );
  F4L_TRY( L ) {
    if( !chart_index_( L, c, key, n ) &&
        !f4l_widget_index_( L, c, key, n ) &&
        !f4l_bad_property( L, F4L_CHART_NAME, key ) )
      lua_pushnil( L );
  } F4L_CATCH( L );
  return 1;
}


static int chart_newindex( lua_State* L ) {
  Fl_Chart* c = check_chart( L, 1 );
  size_t n = 0;
  char const* key = luaL_checklstring( L, 2, &n );
  F4L_TRY( L ) {
    (void)(chart_newindex_( L, c, key, n ) ||
           f4l_widget_newindex_( L, c, key, n ) ||
           f4l_bad_property( L, F4L_CHART_NAME, key ));
  } F4L_CATCH( L );
  return 0;
}


static int chart_add( lua_State* L ) {
  Fl_Chart* c = check_chart( L, 1 );
  double v = luaL_checknumber( L, 2 );
  char const* l = luaL_optstring( L, 3, NULL );
  Fl_Color co = luaL_opt( L, f4l_check_color, 4, FL_FOREGROUND_COLOR );
  F4L_TRY( L ) {
    c->add( v, l, co );
  } F4L_CATCH( L );
  return 0;
}


static int chart_bounds( lua_State* L ) {
  Fl_Chart* c = check_chart( L, 1 );
  double a, b;
  F4L_TRY( L ) {
    if( lua_gettop( L ) < 3 ) {
      c->bounds( &a, &b );
      lua_pushnumber( L, a );
      lua_pushnumber( L, b );
      return 2;
    } else {
      a = luaL_checknumber( L, 2 );
      b = luaL_checknumber( L, 3 );
      c->bounds( a, b );
      return 0;
    }
  } F4L_CATCH( L );
  return 0;
}


static int chart_clear( lua_State* L ) {
  Fl_Chart* c = check_chart( L, 1 );
  F4L_TRY( L ) {
    c->clear();
  } F4L_CATCH( L );
  return 0;
}


static int chart_insert( lua_State* L ) {
  Fl_Chart* c = check_chart( L, 1 );
  F4L_TRY( L ) {
    int ind = moon_checkint( L, 2, 1, c->size()+1 );
    double v = luaL_checknumber( L, 3 );
    char const* l = luaL_optstring( L, 4, NULL );
    Fl_Color co = luaL_opt( L, f4l_check_color, 5, FL_FOREGROUND_COLOR );
    c->insert( ind, v, l, co );
  } F4L_CATCH( L );
  return 0;
}


static int chart_replace( lua_State* L ) {
  Fl_Chart* c = check_chart( L, 1 );
  F4L_TRY( L ) {
    int ind = moon_checkint( L, 2, 1, c->size() );
    double v = luaL_checknumber( L, 3 );
    char const* l = luaL_optstring( L, 4, NULL );
    Fl_Color co = luaL_opt( L, f4l_check_color, 5, FL_FOREGROUND_COLOR );
    c->replace( ind, v, l, co );
  } F4L_CATCH( L );
  return 0;
}


static int chart_size( lua_State* L ) {
  Fl_Chart* c = check_chart( L, 1 );
  int w = moon_checkint( L, 2, 0, INT_MAX );
  int h = moon_checkint( L, 3, 0, INT_MAX );
  F4L_TRY( L ) {
    c->size( w, h );
  } F4L_CATCH( L );
  return 0;
}

F4L_LUA_LLINKAGE_END


F4L_DEF_CAST( Fl_Chart, Fl_Widget )


MOON_LOCAL void f4l_chart_setup( lua_State* L ) {
  luaL_Reg const methods[] = {
    F4L_WIDGET_METHODS,
    { "add", chart_add },
    { "bounds", chart_bounds },
    { "clear", chart_clear },
    { "insert", chart_insert },
    { "replace", chart_replace },
    { "size", chart_size },
    { "__index", chart_index },
    { "__newindex", chart_newindex },
    { NULL, NULL }
  };
  moon_defobject( L, F4L_CHART_NAME, 0, methods, 0 );
  moon_defcast( L, F4L_CHART_NAME, F4L_WIDGET_NAME,
                f4l_cast_Fl_Chart_Fl_Widget );
  f4l_new_class_table( L, "Chart", new_chart );
}

