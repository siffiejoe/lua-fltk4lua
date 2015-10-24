#include "fltk4lua.hxx"
#include "f4l_group.hxx"
#include "f4l_widget.hxx"
#include "f4l_enums.hxx"
#include <FL/Fl_Pack.H>


#define TYPE_LIST( _ ) \
  _( "VERTICAL", Fl_Pack::VERTICAL ) \
  _( "HORIZONTAL", Fl_Pack::HORIZONTAL )

  F4L_GEN_TYPE_ENUM( TYPE_LIST, pack )


namespace {

  inline Fl_Pack* check_pack( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_PACK_NAME );
    return static_cast< Fl_Pack* >( p );
  }


  int pack_index_( lua_State* L, Fl_Pack* p,
                   char const* key, size_t n ) {
    using namespace std;
    switch( n ) {
      case 4:
        if( F4L_MEMCMP( key, "type", 4 ) == 0 ) {
          f4l_push_type_pack( L, p->type() );
          return 1;
        }
        break;
      case 7:
        if( F4L_MEMCMP( key, "spacing", 7 ) == 0 ) {
          lua_pushinteger( L, p->spacing() );
          return 1;
        }
        break;
      case 10:
        if( F4L_MEMCMP( key, "horizontal", 10 ) == 0 ) {
          lua_pushboolean( L, p->horizontal() );
          return 1;
        }
        break;
    }
    return 0;
  }


  int pack_newindex_( lua_State* L, Fl_Pack* p,
                      char const* key, size_t n ) {
    using namespace std;
    switch( n ) {
      case 4:
        if( F4L_MEMCMP( key, "type", 4 ) == 0 ) {
          p->type( f4l_check_type_pack( L, 3 ) );
          return 1;
        }
        break;
      case 7:
        if( F4L_MEMCMP( key, "spacing", 7 ) == 0 ) {
          p->spacing( moon_checkint( L, 3, 0, INT_MAX ) );
          return 1;
        }
        break;
    }
    return 0;
  }

} // anonymous namespace


F4L_DEF_DELETE( Fl_Pack )


F4L_LUA_LLINKAGE_BEGIN

static int new_pack( lua_State* L ) {
  F4L_TRY( L ) {
    f4l_new_widget< Fl_Pack >( L, F4L_PACK_NAME,
                               f4l_delete_Fl_Pack );
  } F4L_CATCH( L );
  return 1;
}


static int pack_index( lua_State* L ) {
  Fl_Pack* p = check_pack( L, 1 );
  size_t n = 0;
  char const* key = luaL_checklstring( L, 2, &n );
  F4L_TRY( L ) {
    if( !pack_index_( L, p, key, n ) &&
        !f4l_group_index_( L, p, key, n ) &&
        !f4l_widget_index_( L, p, key, n ) &&
        !f4l_bad_property( L, F4L_PACK_NAME, key ) )
      lua_pushnil( L );
  } F4L_CATCH( L );
  return 1;
}


static int pack_newindex( lua_State* L ) {
  Fl_Pack* p = check_pack( L, 1 );
  size_t n = 0;
  char const* key = luaL_checklstring( L, 2, &n );
  F4L_TRY( L ) {
    (void)(pack_newindex_( L, p, key, n ) ||
           f4l_group_newindex_( L, p, key, n ) ||
           f4l_widget_newindex_( L, p, key, n ) ||
           f4l_bad_property( L, F4L_PACK_NAME, key ));
  } F4L_CATCH( L );
  return 0;
}

F4L_LUA_LLINKAGE_END


F4L_DEF_CAST( Fl_Pack, Fl_Group )
F4L_DEF_CAST( Fl_Pack, Fl_Widget )


MOON_LOCAL void f4l_pack_setup( lua_State* L ) {
  luaL_Reg const methods[] = {
    F4L_WIDGET_METHODS,
    F4L_GROUP_METHODS,
    { "__index", pack_index },
    { "__newindex", pack_newindex },
    { NULL, NULL }
  };
  moon_defobject( L, F4L_PACK_NAME, 0, methods, 0 );
  moon_defcast( L, F4L_PACK_NAME, F4L_GROUP_NAME,
                f4l_cast_Fl_Pack_Fl_Group );
  moon_defcast( L, F4L_PACK_NAME, F4L_WIDGET_NAME,
                f4l_cast_Fl_Pack_Fl_Widget );
  f4l_new_class_table( L, "Pack", new_pack );
}

