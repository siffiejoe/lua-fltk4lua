#include "fltk4lua.hxx"
#include "f4l_image.hxx"
#include "f4l_enums.hxx"
#include <cstring>


namespace {

  inline Fl_Image* check_image( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_IMAGE_NAME );
    return static_cast< Fl_Image* >( p );
  }

} // anonymous namespace


MOON_LOCAL int f4l_image_index_( lua_State* L, Fl_Image* i,
                                 char const* key, size_t n ) {
  if( n == 1 ) {
    switch( *key ) {
      case 'd':
        lua_pushinteger( L, i->d() );
        return 1;
      case 'h':
        lua_pushinteger( L, i->h() );
        return 1;
      case 'w':
        lua_pushinteger( L, i->w() );
        return 1;
    }
  }
  return 0;
}


F4L_LUA_LLINKAGE_BEGIN

MOON_LOCAL int f4l_image_color_average( lua_State* L ) {
  Fl_Image* i = check_image( L, 1 );
  Fl_Color c = f4l_check_color( L, 2 );
  float w = static_cast< float >( luaL_checknumber( L, 3 ) );
  F4L_TRY( L ) {
    i->color_average( c, w );
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_image_desaturate( lua_State* L ) {
  Fl_Image* i = check_image( L, 1 );
  F4L_TRY( L ) {
    i->desaturate();
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_image_inactive( lua_State* L ) {
  Fl_Image* i = check_image( L, 1 );
  F4L_TRY( L ) {
    i->inactive();
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_image_uncache( lua_State* L ) {
  Fl_Image* i = check_image( L, 1 );
  F4L_TRY( L ) {
    i->uncache();
  } F4L_CATCH( L );
  return 0;
}

F4L_LUA_LLINKAGE_END

