#include "fltk4lua.hxx"
#include "f4l_browserx.hxx"
#include "f4l_enums.hxx"
#include <cstring>
#include <climits>


#define TYPE_LIST( _ ) \
  _( "HORIZONTAL", Fl_Browser_::HORIZONTAL ) \
  _( "VERTICAL", Fl_Browser_::VERTICAL ) \
  _( "BOTH", Fl_Browser_::BOTH ) \
  _( "HORIZONTAL_ALWAYS", Fl_Browser_::HORIZONTAL_ALWAYS ) \
  _( "VERTICAL_ALWAYS", Fl_Browser_::VERTICAL_ALWAYS ) \
  _( "BOTH_ALWAYS", Fl_Browser_::BOTH_ALWAYS )

  F4L_GEN_TYPE_ENUM( TYPE_LIST, bscroll )


namespace {

  inline Fl_Browser_* check_browserx( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_BROWSERX_NAME );
    return static_cast< Fl_Browser_* >( p );
  }

} // anonymous namespace


F4L_LUA_LLINKAGE_BEGIN

static int browserx_deselect_( lua_State* L ) {
  Fl_Browser_* b = check_browserx( L, 1 );
  int cb = lua_toboolean( L, 2 );
  F4L_TRY( L ) {
    lua_pushboolean( L, b->deselect( cb ) );
  } F4L_CATCH( L );
  return 1;
}

MOON_LOCAL int f4l_browserx_deselect( lua_State* L ) {
  F4L_CALL_PROTECTED( L, browserx_deselect_, 1 );
  return 1;
}


MOON_LOCAL int f4l_browserx_scrollbar_left( lua_State* L ) {
  Fl_Browser_* b = check_browserx( L, 1 );
  F4L_TRY( L ) {
    b->scrollbar_left();
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_browserx_scrollbar_right( lua_State* L ) {
  Fl_Browser_* b = check_browserx( L, 1 );
  F4L_TRY( L ) {
    b->scrollbar_right();
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_browserx_sort( lua_State* L ) {
  Fl_Browser_* b = check_browserx( L, 1 );
  static char const* const names[] = {
    "FL_SORT_ASCENDING",
    "FL_SORT_DESCENDING",
    NULL
  };
  static int const values[] = {
    FL_SORT_ASCENDING,
    FL_SORT_DESCENDING
  };
  int flags = values[ luaL_checkoption( L, 2, "FL_SORT_ASCENDING", names ) ];
  F4L_TRY( L ) {
    b->sort( flags );
  } F4L_CATCH( L );
  return 0;
}

F4L_LUA_LLINKAGE_END


MOON_LOCAL int f4l_browserx_index_( lua_State* L, Fl_Browser_* b,
                                    char const* key, size_t n ) {
  using namespace std;
  switch( n ) {
    case 8:
      if( F4L_MEMCMP( key, "textfont", 8 ) == 0 ) {
        f4l_push_font( L, b->textfont() );
        return 1;
      } else if( F4L_MEMCMP( key, "textsize", 8 ) == 0 ) {
        lua_pushinteger( L, b->textsize() );
        return 1;
      }
      break;
    case 9:
      if( F4L_MEMCMP( key, "hposition", 9 ) == 0 ) {
        lua_pushinteger( L, b->hposition() );
        return 1;
      } else if( F4L_MEMCMP( key, "textcolor", 9 ) == 0 ) {
        f4l_push_color( L, b->textcolor() );
        return 1;
      } else if( F4L_MEMCMP( key, "vposition", 9 ) == 0 ) {
        lua_pushinteger( L, b->position() );
        return 1;
      }
      break;
    case 13:
      if( F4L_MEMCMP( key, "has_scrollbar", 13 ) == 0 ) {
        f4l_push_type_bscroll( L, b->has_scrollbar() );
        return 1;
      }
      break;
    case 14:
      if( F4L_MEMCMP( key, "scrollbar_size", 14 ) == 0 ) {
        lua_pushinteger( L, b->scrollbar_size() );
        return 1;
      }
      break;
    case 15:
      if( F4L_MEMCMP( key, "scrollbar_width", 15 ) == 0 ) {
        lua_pushinteger( L, b->scrollbar_width() );
        return 1;
      }
      break;
  }
  return 0;
}


MOON_LOCAL int f4l_browserx_newindex_( lua_State* L, Fl_Browser_* b,
                                       char const* key, size_t n ) {
  using namespace std;
  switch( n ) {
    case 8:
      if( F4L_MEMCMP( key, "textfont", 8 ) == 0 ) {
        b->textfont( f4l_check_font( L, 3 ) );
        return 1;
      } else if( F4L_MEMCMP( key, "textsize", 8 ) == 0 ) {
        b->textsize( moon_checkint( L, 3, 0, INT_MAX ) );
        return 1;
      }
      break;
    case 9:
      if( F4L_MEMCMP( key, "hposition", 9 ) == 0 ) {
        b->hposition( moon_checkint( L, 3, 0, INT_MAX ) );
        return 1;
      } else if( F4L_MEMCMP( key, "textcolor", 9 ) == 0 ) {
        b->textcolor( f4l_check_color( L, 3 ) );
        return 1;
      } else if( F4L_MEMCMP( key, "vposition", 9 ) == 0 ) {
        b->position( moon_checkint( L, 3, 0, INT_MAX ) );
        return 1;
      }
      break;
    case 13:
      if( F4L_MEMCMP( key, "has_scrollbar", 13 ) == 0 ) {
        b->has_scrollbar( f4l_check_type_bscroll( L, 3 ) );
        return 1;
      }
      break;
    case 14:
      if( F4L_MEMCMP( key, "scrollbar_size", 14 ) == 0 ) {
        b->scrollbar_size( moon_checkint( L, 3, 0, INT_MAX ) );
        return 1;
      }
      break;
    case 15:
      if( F4L_MEMCMP( key, "scrollbar_width", 15 ) == 0 ) {
        b->scrollbar_width( moon_checkint( L, 3, 0, INT_MAX ) );
        return 1;
      }
      break;
  }
  return 0;
}

