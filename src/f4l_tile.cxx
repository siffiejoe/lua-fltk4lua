#include "fltk4lua.hxx"
#include "f4l_group.hxx"
#include "f4l_widget.hxx"
#include <FL/Fl_Tile.H>

namespace {

  inline Fl_Tile* check_tile( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_TILE_NAME );
    return static_cast< Fl_Tile* >( p );
  }

  int tile_index( lua_State* L ) {
    Fl_Tile* t = check_tile( L, 1 );
    size_t n = 0;
    char const* key = luaL_checklstring( L, 2, &n );
    F4L_TRY {
      if( !f4l_group_index_( L, t, key, n ) &&
          !f4l_widget_index_( L, t, key, n ) )
        lua_pushnil( L );
    } F4L_CATCH( L );
    return 1;
  }

  int tile_newindex( lua_State* L ) {
    Fl_Tile* t = check_tile( L, 1 );
    size_t n = 0;
    char const* key = luaL_checklstring( L, 2, &n );
    F4L_TRY {
      (void)(f4l_group_newindex_( L, t, key, n ) ||
             f4l_widget_newindex_( L, t, key, n ));
    } F4L_CATCH( L );
    return 0;
  }

  int new_tile( lua_State* L ) {
    F4L_TRY {
      f4l_new_widget< Fl_Tile >( L, F4L_TILE_NAME );
    } F4L_CATCH( L );
    return 1;
  }


  int tile_position( lua_State* L ) {
    Fl_Tile* t = check_tile( L, 1 );
    int oix = moon_checkint( L, 2, 0, INT_MAX );
    int oiy = moon_checkint( L, 3, 0, INT_MAX );
    int newx = moon_checkint( L, 4, 0, INT_MAX );
    int newy = moon_checkint( L, 5, 0, INT_MAX );
    F4L_TRY {
      t->position( oix, oiy, newx, newy );
    } F4L_CATCH( L );
    return 0;
  }

} // anonymous namespace


MOON_LOCAL void f4l_tile_setup( lua_State* L ) {
  luaL_Reg const methods[] = {
    F4L_WIDGET_METHODS,
    F4L_GROUP_METHODS,
    { "position", tile_position },
    { "__index", tile_index },
    { "__newindex", tile_newindex },
    { NULL, NULL }
  };
  moon_defobject( L, F4L_TILE_NAME, 0, methods, 0 );
  moon_defcast( L, F4L_TILE_NAME, F4L_GROUP_NAME,
                f4l_cast< Fl_Tile, Fl_Group > );
  moon_defcast( L, F4L_TILE_NAME, F4L_WIDGET_NAME,
                f4l_cast< Fl_Tile, Fl_Widget > );
  f4l_new_class_table( L, "Tile", new_tile );
}

