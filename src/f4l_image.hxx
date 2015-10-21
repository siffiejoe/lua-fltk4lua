#ifndef F4L_IMAGE_HXX_
#define F4L_IMAGE_HXX_

#include "fltk4lua.hxx"
#include <FL/Fl_Image.H>


/* (Meta-)methods for images: */
MOON_LOCAL int f4l_image_index_( lua_State* L, Fl_Image* i,
                                 char const* key, size_t n );

F4L_LUA_LLINKAGE_BEGIN
MOON_LOCAL int f4l_image_color_average( lua_State* L );
MOON_LOCAL int f4l_image_desaturate( lua_State* L );
MOON_LOCAL int f4l_image_inactive( lua_State* L );
MOON_LOCAL int f4l_image_uncache( lua_State* L );
F4L_LUA_LLINKAGE_END


#define F4L_IMAGE_METHODS \
  { "color_average", f4l_image_color_average }, \
  { "desaturate", f4l_image_desaturate }, \
  { "inactive", f4l_image_inactive }, \
  { "uncache", f4l_image_uncache }


#endif /* F4L_IMAGE_HXX_ */

