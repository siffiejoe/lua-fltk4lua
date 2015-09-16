#include "fltk4lua.hxx"
#include "f4l_enums.hxx"

/* common macros for creating code from an enum list */
#define GEN_NAME( _a, _b, _c ) _b,
#define GEN_VALUE( _a, _b, _c ) _c,
#define GEN_CASE( _a, _b, _c ) \
  case _c: lua_pushliteral( L, _b ); break;


#define DAMAGE_LIST( _ ) \
  _( "DAMAGE_CHILD", "child", FL_DAMAGE_CHILD ) \
  _( "DAMAGE_EXPOSE", "expose", FL_DAMAGE_EXPOSE ) \
  _( "DAMAGE_SCROLL", "scroll", FL_DAMAGE_SCROLL ) \
  _( "DAMAGE_OVERLAY", "overlay", FL_DAMAGE_OVERLAY ) \
  _( "DAMAGE_USER1", "user1", FL_DAMAGE_USER1 ) \
  _( "DAMAGE_USER2", "user2", FL_DAMAGE_USER2 ) \
  _( "DAMAGE_ALL", "all", FL_DAMAGE_ALL )

#define MOON_FLAG_NAME "fltk4lua.Damage"
#define MOON_FLAG_TYPE Fl_Damage
#define MOON_FLAG_SUFFIX damage
#define MOON_FLAG_USECACHE
#define MOON_FLAG_NORELOPS
#include "moon_flag.h"

MOON_LOCAL Fl_Damage f4l_check_damage( lua_State* L, int idx ) {
  return moon_flag_get_damage( L, idx );
}

MOON_LOCAL void f4l_push_damage( lua_State* L, Fl_Damage d ) {
  moon_flag_new_damage( L, d );
}


#define EVENT_LIST( _ ) \
  _( "NO_EVENT", "no_event", FL_NO_EVENT ) \
  _( "PUSH", "push", FL_PUSH ) \
  _( "RELEASE", "release", FL_RELEASE ) \
  _( "ENTER", "enter", FL_ENTER ) \
  _( "LEAVE", "leave", FL_LEAVE ) \
  _( "DRAG", "drag", FL_DRAG ) \
  _( "FOCUS", "focus", FL_FOCUS ) \
  _( "UNFOCUS", "unfocus", FL_UNFOCUS ) \
  _( "KEYDOWN", "keydown", FL_KEYDOWN ) \
  _( "KEYUP", "keyup", FL_KEYUP ) \
  _( "CLOSE", "close", FL_CLOSE ) \
  _( "MOVE", "move", FL_MOVE ) \
  _( "SHORTCUT", "shortcut", FL_SHORTCUT ) \
  _( "DEACTIVATE", "deactivate", FL_DEACTIVATE ) \
  _( "ACTIVATE", "activate", FL_ACTIVATE ) \
  _( "HIDE", "hide", FL_HIDE ) \
  _( "SHOW", "show", FL_SHOW ) \
  _( "PASTE", "paste", FL_PASTE ) \
  _( "SELECTIONCLEAR", "selectionclear", FL_SELECTIONCLEAR ) \
  _( "MOUSEWHEEL", "mousewheel", FL_MOUSEWHEEL ) \
  _( "DND_ENTER", "dnd_enter", FL_DND_ENTER ) \
  _( "DND_DRAG", "dnd_drag", FL_DND_DRAG ) \
  _( "DND_LEAVE", "dnd_leave", FL_DND_LEAVE ) \
  _( "DND_RELEASE", "dnd_release", FL_DND_RELEASE ) \
  _( "SCREEN_CONFIGURATION_CHANGED", "screen_configuration_changed", FL_SCREEN_CONFIGURATION_CHANGED ) \
  _( "FULLSCREEN", "fullscreen", FL_FULLSCREEN )

MOON_LOCAL Fl_Event f4l_check_event( lua_State* L, int idx ) {
  static char const* const names[] = {
    EVENT_LIST( GEN_NAME )
    "keyboard", // alias for "keydown"
    NULL
  };
  static Fl_Event const values[] = {
    EVENT_LIST( GEN_VALUE )
    FL_KEYBOARD, // alias for FL_KEYDOWN
    (Fl_Event)0 // dummy value
  };
  return values[ luaL_checkoption( L, idx, NULL, names ) ];
}

MOON_LOCAL void f4l_push_event( lua_State* L, Fl_Event e ) {
  switch( e ) {
    EVENT_LIST( GEN_CASE )
    default:
      luaL_error( L, "unknown Fl_Event" );
  }
}


#define LABELTYPE_LIST( _ ) \
  _( "NORMAL_LABEL", "normal", FL_NORMAL_LABEL ) \
  _( "NO_LABEL", "no_label", FL_NO_LABEL ) \
  _( "SHADOW_LABEL", "shadow", _FL_SHADOW_LABEL ) \
  _( "ENGRAVED_LABEL", "engraved", _FL_ENGRAVED_LABEL ) \
  _( "EMBOSSED_LABEL", "embossed", _FL_EMBOSSED_LABEL ) \
  _( "MULTI_LABEL", "multi", _FL_MULTI_LABEL ) \
  _( "ICON_LABEL", "icon", _FL_ICON_LABEL ) \
  _( "IMAGE_LABEL", "image", _FL_IMAGE_LABEL )

MOON_LOCAL Fl_Labeltype f4l_check_labeltype( lua_State* L, int idx ) {
  /* the following macros have side effects! */
  static int const dummy_ = FL_SHADOW_LABEL || FL_ENGRAVED_LABEL ||
                            FL_EMBOSSED_LABEL;
  static char const* const names[] = {
    LABELTYPE_LIST( GEN_NAME )
    NULL
  };
  static Fl_Labeltype const values[] = {
    LABELTYPE_LIST( GEN_VALUE )
    (Fl_Labeltype)0 // dummy value
  };
  (void)dummy_;
  return values[ luaL_checkoption( L, idx, NULL, names ) ];
}

MOON_LOCAL void f4l_push_labeltype( lua_State* L, Fl_Labeltype t ) {
  switch( t ) {
    LABELTYPE_LIST( GEN_CASE )
    default:
      luaL_error( L, "unknown Fl_Labeltype" );
  }
}


#define MODE_LIST( _ ) \
  _( "RGB", "rgb", FL_RGB ) \
  _( "INDEX", "index", FL_INDEX ) \
  _( "SINGLE", "single", FL_SINGLE ) \
  _( "DOUBLE", "double", FL_DOUBLE ) \
  _( "ACCUM", "accum", FL_ACCUM ) \
  _( "ALPHA", "alpha", FL_ALPHA ) \
  _( "DEPTH", "depth", FL_DEPTH ) \
  _( "STENCIL", "stencil", FL_STENCIL ) \
  _( "RGB8", "rgb8", FL_RGB8 ) \
  _( "MULTISAMPLE", "multisample", FL_MULTISAMPLE ) \
  _( "STEREO", "stereo", FL_STEREO ) \
  _( "FAKE_SINGLE", "fake_single", FL_FAKE_SINGLE )

#define MOON_FLAG_NAME "fltk4lua.Mode"
#define MOON_FLAG_TYPE Fl_Mode
#define MOON_FLAG_SUFFIX mode
#define MOON_FLAG_USECACHE
#define MOON_FLAG_NORELOPS
#include "moon_flag.h"

MOON_LOCAL Fl_Mode f4l_check_mode( lua_State* L, int idx ) {
  return moon_flag_get_mode( L, idx );
}

MOON_LOCAL void f4l_push_mode( lua_State* L, Fl_Mode m ) {
  moon_flag_new_mode( L, m );
}


#define WHEN_LIST( _ ) \
  _( "WHEN_NEVER", "never", FL_WHEN_NEVER ) \
  _( "WHEN_CHANGED", "changed", FL_WHEN_CHANGED ) \
  _( "WHEN_NOT_CHANGED", "not_changed", FL_WHEN_NOT_CHANGED ) \
  _( "WHEN_RELEASE", "release", FL_WHEN_RELEASE ) \
  _( "WHEN_RELEASE_ALWAYS", "release_always", FL_WHEN_RELEASE_ALWAYS ) \
  _( "WHEN_ENTER_KEY", "enter_key", FL_WHEN_ENTER_KEY ) \
  _( "WHEN_ENTER_KEY_ALWAYS", "enter_key_always", FL_WHEN_ENTER_KEY_ALWAYS ) \
  _( "WHEN_ENTER_KEY_CHANGED", "enter_key_changed", FL_WHEN_ENTER_KEY_CHANGED )

#define MOON_FLAG_NAME "fltk4lua.When"
#define MOON_FLAG_TYPE Fl_When
#define MOON_FLAG_SUFFIX when
#define MOON_FLAG_USECACHE
#define MOON_FLAG_NORELOPS
#include "moon_flag.h"

MOON_LOCAL Fl_When f4l_check_when( lua_State* L, int idx ) {
  return moon_flag_get_when( L, idx );
}

MOON_LOCAL void f4l_push_when( lua_State* L, Fl_When w ) {
  moon_flag_new_when( L, w );
}


#define CURSOR_LIST( _ ) \
  _( "CURSOR_DEFAULT", "default", FL_CURSOR_DEFAULT ) \
  _( "CURSOR_ARROW", "arrow", FL_CURSOR_ARROW ) \
  _( "CURSOR_CROSS", "cross", FL_CURSOR_CROSS ) \
  _( "CURSOR_WAIT", "wait", FL_CURSOR_WAIT ) \
  _( "CURSOR_INSERT", "insert", FL_CURSOR_INSERT ) \
  _( "CURSOR_HAND", "hand", FL_CURSOR_HAND ) \
  _( "CURSOR_HELP", "help", FL_CURSOR_HELP ) \
  _( "CURSOR_MOVE", "move", FL_CURSOR_MOVE ) \
  _( "CURSOR_NS", "ns", FL_CURSOR_NS ) \
  _( "CURSOR_WE", "we", FL_CURSOR_WE ) \
  _( "CURSOR_NWSE", "nwse", FL_CURSOR_NWSE ) \
  _( "CURSOR_NESW", "nesw", FL_CURSOR_NESW ) \
  _( "CURSOR_NONE", "none", FL_CURSOR_NONE ) \
  _( "CURSOR_N", "n", FL_CURSOR_N ) \
  _( "CURSOR_NE", "ne", FL_CURSOR_NE ) \
  _( "CURSOR_E", "e", FL_CURSOR_E ) \
  _( "CURSOR_SE", "se", FL_CURSOR_SE ) \
  _( "CURSOR_S", "s", FL_CURSOR_S ) \
  _( "CURSOR_SW", "sw", FL_CURSOR_SW ) \
  _( "CURSOR_W", "w", FL_CURSOR_W ) \
  _( "CURSOR_NW", "nw", FL_CURSOR_NW )

MOON_LOCAL Fl_Cursor f4l_check_cursor( lua_State* L, int idx ) {
  static char const* const names[] = {
    CURSOR_LIST( GEN_NAME )
    NULL
  };
  static Fl_Cursor const values[] = {
    CURSOR_LIST( GEN_VALUE )
    (Fl_Cursor)0 // dummy value
  };
  return values[ luaL_checkoption( L, idx, NULL, names ) ];
}

MOON_LOCAL void f4l_push_cursor( lua_State* L, Fl_Cursor c ) {
  switch( c ) {
    CURSOR_LIST( GEN_CASE )
    default:
      luaL_error( L, "unknown Fl_Cursor" );
  }
}


#define BOXTYPE_LIST( _ ) \
  _( "NO_BOX", "no_box", FL_NO_BOX ) \
  _( "FLAT_BOX", "flat_box", FL_FLAT_BOX ) \
  _( "UP_BOX", "up_box", FL_UP_BOX ) \
  _( "DOWN_BOX", "down_box", FL_DOWN_BOX ) \
  _( "UP_FRAME", "up_frame", FL_UP_FRAME ) \
  _( "DOWN_FRAME", "down_frame", FL_DOWN_FRAME ) \
  _( "THIN_UP_BOX", "thin_up_box", FL_THIN_UP_BOX ) \
  _( "THIN_DOWN_BOX", "thin_down_box", FL_THIN_DOWN_BOX ) \
  _( "THIN_UP_FRAME", "thin_up_frame", FL_THIN_UP_FRAME ) \
  _( "THIN_DOWN_FRAME", "thin_down_frame", FL_THIN_DOWN_FRAME ) \
  _( "ENGRAVED_BOX", "engraved_box", FL_ENGRAVED_BOX ) \
  _( "EMBOSSED_BOX", "embossed_box", FL_EMBOSSED_BOX ) \
  _( "ENGRAVED_FRAME", "engraved_frame", FL_ENGRAVED_FRAME ) \
  _( "EMBOSSED_FRAME", "embossed_frame", FL_EMBOSSED_FRAME ) \
  _( "BORDER_BOX", "border_box", FL_BORDER_BOX ) \
  _( "SHADOW_BOX", "shadow_box", _FL_SHADOW_BOX ) \
  _( "BORDER_FRAME", "border_frame", FL_BORDER_FRAME ) \
  _( "SHADOW_FRAME", "shadow_frame", _FL_SHADOW_FRAME ) \
  _( "ROUNDED_BOX", "rounded_box", _FL_ROUNDED_BOX ) \
  _( "RSHADOW_BOX", "rshadow_box", _FL_RSHADOW_BOX ) \
  _( "ROUNDED_FRAME", "rounded_frame", _FL_ROUNDED_FRAME ) \
  _( "RFLAT_BOX", "rflat_box", _FL_RFLAT_BOX ) \
  _( "ROUND_UP_BOX", "round_up_box", _FL_ROUND_UP_BOX ) \
  _( "ROUND_DOWN_BOX", "round_down_box", _FL_ROUND_DOWN_BOX ) \
  _( "DIAMOND_UP_BOX", "diamond_up_box", _FL_DIAMOND_UP_BOX ) \
  _( "DIAMOND_DOWN_BOX", "diamond_down_box", _FL_DIAMOND_DOWN_BOX ) \
  _( "OVAL_BOX", "oval_box", _FL_OVAL_BOX ) \
  _( "OSHADOW_BOX", "oshadow_box", _FL_OSHADOW_BOX ) \
  _( "OVAL_FRAME", "oval_frame", _FL_OVAL_FRAME ) \
  _( "OFLAT_BOX", "oflat_box", _FL_OFLAT_BOX ) \
  _( "PLASTIC_UP_BOX", "plastic_up_box", _FL_PLASTIC_UP_BOX ) \
  _( "PLASTIC_DOWN_BOX", "plastic_down_box", _FL_PLASTIC_DOWN_BOX ) \
  _( "PLASTIC_UP_FRAME", "plastic_up_frame", _FL_PLASTIC_UP_FRAME ) \
  _( "PLASTIC_DOWN_FRAME", "plastic_down_frame", _FL_PLASTIC_DOWN_FRAME ) \
  _( "PLASTIC_THIN_UP_BOX", "plastic_thin_up_box", _FL_PLASTIC_THIN_UP_BOX ) \
  _( "PLASTIC_THIN_DOWN_BOX", "plastic_thin_down_box", _FL_PLASTIC_THIN_DOWN_BOX ) \
  _( "PLASTIC_ROUND_UP_BOX", "plastic_round_up_box", _FL_PLASTIC_ROUND_UP_BOX ) \
  _( "PLASTIC_ROUND_DOWN_BOX", "plastic_round_down_box", _FL_PLASTIC_ROUND_DOWN_BOX ) \
  _( "GTK_UP_BOX", "gtk_up_box", _FL_GTK_UP_BOX ) \
  _( "GTK_DOWN_BOX", "gtk_down_box", _FL_GTK_DOWN_BOX ) \
  _( "GTK_UP_FRAME", "gtk_up_frame", _FL_GTK_UP_FRAME ) \
  _( "GTK_DOWN_FRAME", "gtk_down_frame", _FL_GTK_DOWN_FRAME ) \
  _( "GTK_THIN_UP_BOX", "gtk_thin_up_box", _FL_GTK_THIN_UP_BOX ) \
  _( "GTK_THIN_DOWN_BOX", "gtk_thin_down_box", _FL_GTK_THIN_DOWN_BOX ) \
  _( "GTK_THIN_UP_FRAME", "gtk_thin_up_frame", _FL_GTK_THIN_UP_FRAME ) \
  _( "GTK_THIN_DOWN_FRAME", "gtk_thin_down_frame", _FL_GTK_THIN_DOWN_FRAME ) \
  _( "GTK_ROUND_UP_BOX", "gtk_round_up_box", _FL_GTK_ROUND_UP_BOX ) \
  _( "GTK_ROUND_DOWN_BOX", "gtk_round_down_box", _FL_GTK_ROUND_DOWN_BOX ) \

MOON_LOCAL Fl_Boxtype f4l_check_boxtype( lua_State* L, int idx ) {
  /* the following macros have side effects! */
  static int const dummy_ = FL_ROUND_UP_BOX || FL_SHADOW_BOX ||
                            FL_ROUNDED_BOX || FL_RFLAT_BOX ||
                            FL_RSHADOW_BOX || FL_DIAMOND_UP_BOX ||
                            FL_OVAL_BOX || FL_PLASTIC_UP_BOX ||
                            FL_GTK_UP_BOX;
  static char const* const names[] = {
    BOXTYPE_LIST( GEN_NAME )
    NULL
  };
  static Fl_Boxtype const values[] = {
    BOXTYPE_LIST( GEN_VALUE )
    (Fl_Boxtype)0 // dummy value
  };
  (void)dummy_;
  return values[ luaL_checkoption( L, idx, NULL, names ) ];
}

MOON_LOCAL void f4l_push_boxtype( lua_State* L, Fl_Boxtype b ) {
  switch( b ) {
    BOXTYPE_LIST( GEN_CASE )
    default:
      luaL_error( L, "unknown Fl_Boxtype" );
  }
}


#define ALIGN_LIST( _ ) \
  _( "ALIGN_CENTER", "center", FL_ALIGN_CENTER ) \
  _( "ALIGN_TOP", "top", FL_ALIGN_TOP ) \
  _( "ALIGN_BOTTOM", "bottom", FL_ALIGN_BOTTOM ) \
  _( "ALIGN_RIGHT", "right", FL_ALIGN_RIGHT ) \
  _( "ALIGN_LEFT", "left", FL_ALIGN_LEFT ) \
  _( "ALIGN_INSIDE", "inside", FL_ALIGN_INSIDE ) \
  _( "ALIGN_TEXT_OVER_IMAGE", "text_over_image", FL_ALIGN_TEXT_OVER_IMAGE ) \
  _( "ALIGN_IMAGE_OVER_TEXT", "image_over_text", FL_ALIGN_IMAGE_OVER_TEXT ) \
  _( "ALIGN_CLIP", "clip", FL_ALIGN_CLIP ) \
  _( "ALIGN_WRAP", "wrap", FL_ALIGN_WRAP ) \
  _( "ALIGN_IMAGE_NEXT_TO_TEXT", "image_next_to_text", FL_ALIGN_IMAGE_NEXT_TO_TEXT ) \
  _( "ALIGN_TEXT_NEXT_TO_IMAGE", "text_next_to_image", FL_ALIGN_TEXT_NEXT_TO_IMAGE ) \
  _( "ALIGN_IMAGE_BACKDROP", "image_backdrop", FL_ALIGN_IMAGE_BACKDROP ) \
  _( "ALIGN_TOP_LEFT", "top_left", FL_ALIGN_TOP_LEFT ) \
  _( "ALIGN_TOP_RIGHT", "top_right", FL_ALIGN_TOP_RIGHT ) \
  _( "ALIGN_BOTTOM_LEFT", "bottom_left", FL_ALIGN_BOTTOM_LEFT ) \
  _( "ALIGN_BOTTOM_RIGHT", "bottom_right", FL_ALIGN_BOTTOM_RIGHT ) \
  _( "ALIGN_LEFT_TOP", "left_top", FL_ALIGN_LEFT_TOP ) \
  _( "ALIGN_RIGHT_TOP", "right_top", FL_ALIGN_RIGHT_TOP ) \
  _( "ALIGN_LEFT_BOTTOM", "left_bottom", FL_ALIGN_LEFT_BOTTOM ) \
  _( "ALIGN_RIGHT_BOTTOM", "right_bottom", FL_ALIGN_RIGHT_BOTTOM ) \
  _( "ALIGN_NOWRAP", "nowrap", FL_ALIGN_NOWRAP ) \
  _( "ALIGN_POSITION_MASK", "position_mask", FL_ALIGN_POSITION_MASK ) \
  _( "ALIGN_IMAGE_MASK", "image_mask", FL_ALIGN_IMAGE_MASK )

#define MOON_FLAG_NAME "fltk4lua.Align"
#define MOON_FLAG_TYPE Fl_Align
#define MOON_FLAG_SUFFIX align
#define MOON_FLAG_USECACHE
#define MOON_FLAG_NORELOPS
#include "moon_flag.h"

MOON_LOCAL Fl_Align f4l_check_align( lua_State* L, int idx ) {
  if( lua_type( L, idx ) == LUA_TSTRING ) {
    static char const* const names[] = {
      ALIGN_LIST( GEN_NAME )
      NULL
    };
    static Fl_Align const values[] = {
      ALIGN_LIST( GEN_VALUE )
      (Fl_Align)0 // dummy value
    };
    return values[ luaL_checkoption( L, idx, NULL, names ) ];
  } else
    return moon_flag_get_align( L, idx );
}

MOON_LOCAL void f4l_push_align( lua_State* L, Fl_Align a ) {
  moon_flag_new_align( L, a );
}


#define FONT_LIST( _ ) \
  _( "HELVETICA", "helvetica", FL_HELVETICA ) \
  _( "HELVETICA_BOLD", "helvetica_bold", FL_HELVETICA_BOLD ) \
  _( "HELVETICA_ITALIC", "helvetica_italic", FL_HELVETICA_ITALIC ) \
  _( "HELVETICA_BOLD_ITALIC", "helvetica_bold_italic", FL_HELVETICA_BOLD_ITALIC ) \
  _( "COURIER", "courier", FL_COURIER ) \
  _( "COURIER_BOLD", "courier_bold", FL_COURIER_BOLD ) \
  _( "COURIER_ITALIC", "courier_italic", FL_COURIER_ITALIC ) \
  _( "COURIER_BOLD_ITALIC", "courier_bold_italic", FL_COURIER_BOLD_ITALIC ) \
  _( "TIMES", "times", FL_TIMES ) \
  _( "TIMES_BOLD", "times_bold", FL_TIMES_BOLD ) \
  _( "TIMES_ITALIC", "times_italic", FL_TIMES_ITALIC ) \
  _( "TIMES_BOLD_ITALIC", "times_bold_italic", FL_TIMES_BOLD_ITALIC ) \
  _( "SYMBOL", "symbol", FL_SYMBOL ) \
  _( "SCREEN", "screen", FL_SCREEN ) \
  _( "SCREEN_BOLD", "screen_bold", FL_SCREEN_BOLD ) \
  _( "ZAPF_DINGBATS", "zapf_dingbats", FL_ZAPF_DINGBATS ) \

MOON_LOCAL Fl_Font f4l_check_font( lua_State* L, int idx ) {
  static char const* const names[] = {
    FONT_LIST( GEN_NAME )
    NULL
  };
  static Fl_Font const values[] = {
    FONT_LIST( GEN_VALUE )
    (Fl_Font)0 // dummy value
  };
  return values[ luaL_checkoption( L, idx, NULL, names ) ];
}

MOON_LOCAL void f4l_push_font( lua_State* L, Fl_Font f ) {
  switch( f ) {
    FONT_LIST( GEN_CASE )
    default:
      luaL_error( L, "unknown Fl_Font" );
  }
}


#define COLOR_LIST( _ ) \
  _( "FOREGROUND_COLOR", "foreground_color", FL_FOREGROUND_COLOR ) \
  _( "BACKGROUND2_COLOR", "background2_color", FL_BACKGROUND2_COLOR ) \
  _( "INACTIVE_COLOR", "inactive_color", FL_INACTIVE_COLOR ) \
  _( "SELECTION_COLOR", "selection_color", FL_SELECTION_COLOR ) \
  _( "GRAY0", "gray0", FL_GRAY0 ) \
  _( "DARK3", "dark3", FL_DARK3 ) \
  _( "DARK2", "dark2", FL_DARK2 ) \
  _( "DARK1", "dark1", FL_DARK1 ) \
  _( "BACKGROUND_COLOR", "background_color", FL_BACKGROUND_COLOR ) \
  _( "LIGHT1", "light1", FL_LIGHT1 ) \
  _( "LIGHT2", "light2", FL_LIGHT2 ) \
  _( "LIGHT3", "light3", FL_LIGHT3 ) \
  _( "BLACK", "black", FL_BLACK ) \
  _( "RED", "red", FL_RED ) \
  _( "GREEN", "green", FL_GREEN ) \
  _( "YELLOW", "yellow", FL_YELLOW ) \
  _( "BLUE", "blue", FL_BLUE ) \
  _( "MAGENTA", "magenta", FL_MAGENTA ) \
  _( "CYAN", "cyan", FL_CYAN ) \
  _( "DARK_RED", "dark_red", FL_DARK_RED ) \
  _( "DARK_GREEN", "dark_green", FL_DARK_GREEN ) \
  _( "DARK_YELLOW", "dark_yellow", FL_DARK_YELLOW ) \
  _( "DARK_BLUE", "dark_blue", FL_DARK_BLUE ) \
  _( "DARK_MAGENTA", "dark_magenta", FL_DARK_MAGENTA ) \
  _( "DARK_CYAN", "dark_cyan", FL_DARK_CYAN ) \
  _( "WHITE", "white", FL_WHITE )

#define MOON_FLAG_NAME "fltk4lua.Color"
#define MOON_FLAG_TYPE Fl_Color
#define MOON_FLAG_SUFFIX color
#define MOON_FLAG_NOBITOPS
#include "moon_flag.h"

MOON_LOCAL Fl_Color f4l_check_color( lua_State* L, int idx ) {
  if( lua_type( L, idx ) == LUA_TSTRING ) {
    static char const* const names[] = {
      COLOR_LIST( GEN_NAME )
      NULL
    };
    static Fl_Color const values[] = {
      COLOR_LIST( GEN_VALUE )
      (Fl_Color)0 // dummy value
    };
    return values[ luaL_checkoption( L, idx, NULL, names ) ];
  } else
    return moon_flag_get_color( L, idx );
}

MOON_LOCAL void f4l_push_color( lua_State* L, Fl_Color c ) {
  moon_flag_new_color( L, c );
}




MOON_LOCAL void f4l_enums_setup( lua_State* L ) {
  moon_flag_def_damage( L );
  moon_flag_def_mode( L );
  moon_flag_def_when( L );
  moon_flag_def_align( L );
  moon_flag_def_color( L );
#define GEN_UDATA( _a, _b, _c ) \
  (moon_flag_new_damage( L, _c ), lua_setfield( L, -2, _a ));
  DAMAGE_LIST( GEN_UDATA )
#undef GEN_UDATA
#define GEN_UDATA( _a, _b, _c ) \
  (moon_flag_new_mode( L, _c ), lua_setfield( L, -2, _a ));
  MODE_LIST( GEN_UDATA )
#undef GEN_UDATA
#define GEN_UDATA( _a, _b, _c ) \
  (moon_flag_new_when( L, _c ), lua_setfield( L, -2, _a ));
  WHEN_LIST( GEN_UDATA )
#undef GEN_UDATA
#define GEN_UDATA( _a, _b, _c ) \
  (moon_flag_new_align( L, _c ), lua_setfield( L, -2, _a ));
  ALIGN_LIST( GEN_UDATA )
#undef GEN_UDATA
#define GEN_UDATA( _a, _b, _c ) \
  (moon_flag_new_color( L, _c ), lua_setfield( L, -2, _a ));
  COLOR_LIST( GEN_UDATA )
#undef GEN_UDATA
}

