#include "fltk4lua.hxx"
#include "f4l_image.hxx"
#include <FL/Fl_Shared_Image.H>
#include <cstring>
#include <climits>


namespace {

  inline Fl_Shared_Image* check_shared_image( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_SHARED_IMAGE_NAME );
    return static_cast< Fl_Shared_Image* >( p );
  }


  int shared_image_index_( lua_State* L, Fl_Shared_Image* si,
                           char const* key, size_t n ) {
    using namespace std;
    if( n == 4 && F4L_MEMCMP( key, "name", 4 ) == 0 ) {
      lua_pushstring( L, si->name() );
      return 1;
    }
    return 0;
  }

} // anonymous namespace


F4L_MOON_LLINKAGE_BEGIN

static void shared_image_delete( void* p ) {
  Fl_Shared_Image* si = static_cast< Fl_Shared_Image* >( p );
  si->release();
}

F4L_MOON_LLINKAGE_END


F4L_LUA_LLINKAGE_BEGIN

static int shared_image_index( lua_State* L ) {
  Fl_Shared_Image* si = check_shared_image( L, 1 );
  size_t n = 0;
  char const* key = luaL_checklstring( L, 2, &n );
  F4L_TRY( L ) {
    if( !shared_image_index_( L, si, key, n ) &&
        !f4l_image_index_( L, si, key, n ) &&
        !f4l_bad_property( L, F4L_SHARED_IMAGE_NAME, key ) )
      lua_pushnil( L );
  } F4L_CATCH( L );
  return 1;
}


static int shared_image_copy( lua_State* L ) {
  Fl_Shared_Image* si = check_shared_image( L, 1 );
  int w = moon_checkint( L, 2, 0, INT_MAX );
  int h = moon_checkint( L, 3, 0, INT_MAX );
  F4L_TRY( L ) {
    void** p = moon_newpointer( L, F4L_SHARED_IMAGE_NAME,
                                shared_image_delete );
    Fl_Shared_Image* si2 = NULL;
    si2 = static_cast< Fl_Shared_Image* >( si->copy( w, h ) );
    *p = static_cast< void* >( si2 );
  } F4L_CATCH( L );
  return 1;
}


static int shared_image_reload( lua_State* L ) {
  Fl_Shared_Image* si = check_shared_image( L, 1 );
  F4L_TRY( L ) {
    si->reload();
  } F4L_CATCH( L );
  return 0;
}


static int shared_image_get( lua_State* L ) {
  char const* name = luaL_checkstring( L, 1 );
  int w = moon_optint( L, 2, 0, INT_MAX, 0 );
  int h = moon_optint( L, 3, 0, INT_MAX, 0 );
  F4L_TRY( L ) {
    void** p = moon_newpointer( L, F4L_SHARED_IMAGE_NAME,
                                shared_image_delete );
    Fl_Shared_Image* si2 = Fl_Shared_Image::get( name, w, h );
    if( si2 == NULL )
      luaL_error( L, "could not load image '%s'", name );
    *p = static_cast< void* >( si2 );
  } F4L_CATCH( L );
  return 1;
}


static int shared_image_find( lua_State* L ) {
  char const* name = luaL_checkstring( L, 1 );
  int w = moon_optint( L, 2, 0, INT_MAX, 0 );
  int h = moon_optint( L, 3, 0, INT_MAX, 0 );
  F4L_TRY( L ) {
    void** p = moon_newpointer( L, F4L_SHARED_IMAGE_NAME,
                                shared_image_delete );
    Fl_Shared_Image* si2 = Fl_Shared_Image::get( name, w, h );
    *p = static_cast< void* >( si2 );
    if( *p == NULL )
      lua_pushnil( L );
  } F4L_CATCH( L );
  return 1;
}

F4L_LUA_LLINKAGE_END


F4L_DEF_CAST( Fl_Shared_Image, Fl_Image )


MOON_LOCAL void f4l_shared_image_setup( lua_State* L ) {
  luaL_Reg const methods[] = {
    F4L_IMAGE_METHODS,
    { "copy", shared_image_copy },
    { "reload", shared_image_reload },
    { "__index", shared_image_index },
    { NULL, NULL }
  };
  luaL_Reg const smethods[] = {
    { "get", shared_image_get },
    { "find", shared_image_find },
    { NULL, NULL }
  };
  moon_defobject( L, F4L_SHARED_IMAGE_NAME, 0, methods, 0 );
  moon_defcast( L, F4L_SHARED_IMAGE_NAME, F4L_IMAGE_NAME,
                f4l_cast_Fl_Shared_Image_Fl_Image );
  f4l_new_class_table( L, "Shared_Image", 0, smethods );
#if 1
  F4L_TRY( L ) {
    // add support for more image formats (PNG, JPEG)
    // you will need to link to the fltk_images library
    // use `fltk-config --use-images ...` to get appropriate flags
    fl_register_images();
  } F4L_CATCH( L );
#endif
}

