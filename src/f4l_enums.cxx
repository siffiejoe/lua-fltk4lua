#include "fltk4lua.hxx"
#include "f4l_enums.hxx"
#include <FL/fl_draw.H>
#include <climits>
#include <cctype>


#define SHORTCUT_LIST( _ ) \
  _( "Button1", FL_Button + 1 ) \
  _( "Button2", FL_Button + 2 ) \
  _( "Button3", FL_Button + 3 ) \
  _( "BackSpace", FL_BackSpace ) \
  _( "Tab", FL_Tab ) \
  _( "Iso_Key", FL_Iso_Key ) \
  _( "Enter", FL_Enter ) \
  _( "Pause", FL_Pause ) \
  _( "Scroll_Lock", FL_Scroll_Lock ) \
  _( "Escape", FL_Escape ) \
  _( "Home", FL_Home ) \
  _( "Left", FL_Left ) \
  _( "Up", FL_Up ) \
  _( "Right", FL_Right ) \
  _( "Down", FL_Down ) \
  _( "Page_Up", FL_Page_Up ) \
  _( "Page_Down", FL_Page_Down ) \
  _( "End", FL_End ) \
  _( "Print", FL_Print ) \
  _( "Insert", FL_Insert ) \
  _( "Menu", FL_Menu ) \
  _( "Help", FL_Help ) \
  _( "Num_Lock", FL_Num_Lock ) \
  _( "KP0", FL_KP + 0 ) \
  _( "KP1", FL_KP + 1 ) \
  _( "KP2", FL_KP + 2 ) \
  _( "KP3", FL_KP + 3 ) \
  _( "KP4", FL_KP + 4 ) \
  _( "KP5", FL_KP + 5 ) \
  _( "KP6", FL_KP + 6 ) \
  _( "KP7", FL_KP + 7 ) \
  _( "KP8", FL_KP + 8 ) \
  _( "KP9", FL_KP + 9 ) \
  _( "KP_Enter", FL_KP_Enter ) \
  _( "F1", FL_F + 1 ) \
  _( "F2", FL_F + 2 ) \
  _( "F3", FL_F + 3 ) \
  _( "F4", FL_F + 4 ) \
  _( "F5", FL_F + 5 ) \
  _( "F6", FL_F + 6 ) \
  _( "F7", FL_F + 7 ) \
  _( "F8", FL_F + 8 ) \
  _( "F9", FL_F + 9 ) \
  _( "F10", FL_F + 10 ) \
  _( "F11", FL_F + 11 ) \
  _( "F12", FL_F + 12 ) \
  _( "Shift_L", FL_Shift_L ) \
  _( "Shift_R", FL_Shift_R ) \
  _( "Control_L", FL_Control_L ) \
  _( "Control_R", FL_Control_R ) \
  _( "Caps_Lock", FL_Caps_Lock ) \
  _( "Meta_L", FL_Meta_L ) \
  _( "Meta_R", FL_Meta_R ) \
  _( "Alt_L", FL_Alt_L ) \
  _( "Alt_R", FL_Alt_R ) \
  _( "Delete", FL_Delete ) \
  _( "Volume_Down", FL_Volume_Down ) \
  _( "Volume_Mute", FL_Volume_Mute ) \
  _( "Volume_Up", FL_Volume_Up ) \
  _( "Media_Play", FL_Media_Play ) \
  _( "Media_Stop", FL_Media_Stop ) \
  _( "Media_Prev", FL_Media_Prev ) \
  _( "Media_Next", FL_Media_Next ) \
  _( "Home_Page", FL_Home_Page ) \
  _( "Mail", FL_Mail ) \
  _( "Search", FL_Search ) \
  _( "Back", FL_Back ) \
  _( "Forward", FL_Forward ) \
  _( "Stop", FL_Stop ) \
  _( "Refresh", FL_Refresh ) \
  _( "Sleep", FL_Sleep ) \
  _( "Favorites", FL_Favorites ) \
  _( "SHIFT", FL_SHIFT ) \
  _( "CAPS_LOCK", FL_CAPS_LOCK ) \
  _( "CTRL", FL_CTRL ) \
  _( "ALT", FL_ALT ) \
  _( "NUM_LOCK", FL_NUM_LOCK ) \
  _( "META", FL_META ) \
  _( "SCROLL_LOCK", FL_SCROLL_LOCK ) \
  _( "BUTTON1", FL_BUTTON1 ) \
  _( "BUTTON2", FL_BUTTON2 ) \
  _( "BUTTON3", FL_BUTTON3 ) \
  _( "COMMAND", FL_COMMAND ) \
  _( "CONTROL", FL_CONTROL )

#define MOON_FLAG_NAME "fltk4lua.Shortcut"
#define MOON_FLAG_TYPE Fl_Shortcut
#define MOON_FLAG_SUFFIX shortcut
/* we add our own operations below! */
#define MOON_NOBITOPS
#include "moon_flag.h"

MOON_LOCAL Fl_Shortcut f4l_check_shortcut( lua_State* L, int idx ) {
  using namespace std;
  int t = lua_type( L, idx );
  if( t == LUA_TNUMBER )
    return moon_checkint( L, idx, 0, FL_KEY_MASK );
  else if( t == LUA_TSTRING ) {
    char const* sc = lua_tostring( L, idx );
    char const* s = sc;
    int valid = 0, numeric = 1, number = 0;
    while( *s == '#' || *s == '+' || *s == '^' || *s == '!' || *s == '@' )
      ++s;
    while( *s != '\0' ) {
      if( numeric && isdigit( (unsigned char)*s ) && number < 128 ) {
        valid = 1;
        number = number*10 + (*s - '0'); // XXX assumption about order
      } else if( numeric && number == 0 && (unsigned char)*s < 128 ) {
        valid = 1;
        numeric = 0;
      } else {
        valid = 0;
        break;
      }
      ++s;
    }
    if( number >= 128 )
      valid = 0;
    if( !valid )
      luaL_argerror( L, idx, "invalid shortcut string" );
    Fl_Shortcut sh = 0;
    F4L_TRY( L ) {
      sh = fl_old_shortcut( sc );
    } F4L_CATCH( L );
    return sh;
  } else
    return moon_flag_get_shortcut( L, idx );
}

MOON_LOCAL void f4l_push_shortcut( lua_State* L, Fl_Shortcut s ) {
  moon_flag_new_shortcut( L, s );
}


F4L_LUA_LLINKAGE_BEGIN

static int shortcut_add( lua_State* L ) {
  int t1 = lua_type( L, 1 ), t2 = lua_type( L, 2 );
  Fl_Shortcut s1 = 0, s2 = 0;
  if( t1 == LUA_TSTRING ) {
    s1 = (unsigned char)f4l_check_char( L, 1 );
    s2 = moon_flag_get_shortcut( L, 2 ); // can only be userdata
  } else {
    s1 = f4l_check_shortcut( L, 1 );
    if( t2 == LUA_TSTRING )
      s2 = (unsigned char)f4l_check_char( L, 2 );
    else
      s2 = f4l_check_shortcut( L, 2 );
  }
  luaL_argcheck( L, !(s1 & FL_KEY_MASK) + !(s2 & FL_KEY_MASK) >= 1,
                 2, "invalid shortcut combination" );
  moon_flag_new_shortcut( L, s1+s2 );
  return 1;
}

F4L_LUA_LLINKAGE_END


#if 0
#define DAMAGE_LIST( _ ) \
  _( "DAMAGE_CHILD", FL_DAMAGE_CHILD ) \
  _( "DAMAGE_EXPOSE", FL_DAMAGE_EXPOSE ) \
  _( "DAMAGE_SCROLL", FL_DAMAGE_SCROLL ) \
  _( "DAMAGE_OVERLAY", FL_DAMAGE_OVERLAY ) \
  _( "DAMAGE_USER1", FL_DAMAGE_USER1 ) \
  _( "DAMAGE_USER2", FL_DAMAGE_USER2 ) \
  _( "DAMAGE_ALL", FL_DAMAGE_ALL )

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
#endif


#if 0
#define EVENT_LIST( _ ) \
  _( "NO_EVENT", FL_NO_EVENT ) \
  _( "PUSH", FL_PUSH ) \
  _( "RELEASE", FL_RELEASE ) \
  _( "ENTER", FL_ENTER ) \
  _( "LEAVE", FL_LEAVE ) \
  _( "DRAG", FL_DRAG ) \
  _( "FOCUS", FL_FOCUS ) \
  _( "UNFOCUS", FL_UNFOCUS ) \
  _( "KEYDOWN", FL_KEYDOWN ) \
  _( "KEYUP", FL_KEYUP ) \
  _( "CLOSE", FL_CLOSE ) \
  _( "MOVE", FL_MOVE ) \
  _( "SHORTCUT", FL_SHORTCUT ) \
  _( "DEACTIVATE", FL_DEACTIVATE ) \
  _( "ACTIVATE", FL_ACTIVATE ) \
  _( "HIDE", FL_HIDE ) \
  _( "SHOW", FL_SHOW ) \
  _( "PASTE", FL_PASTE ) \
  _( "SELECTIONCLEAR", FL_SELECTIONCLEAR ) \
  _( "MOUSEWHEEL", FL_MOUSEWHEEL ) \
  _( "DND_ENTER", FL_DND_ENTER ) \
  _( "DND_DRAG", FL_DND_DRAG ) \
  _( "DND_LEAVE", FL_DND_LEAVE ) \
  _( "DND_RELEASE", FL_DND_RELEASE ) \
  _( "SCREEN_CONFIGURATION_CHANGED", FL_SCREEN_CONFIGURATION_CHANGED ) \
  _( "FULLSCREEN", FL_FULLSCREEN )

MOON_LOCAL Fl_Event f4l_check_event( lua_State* L, int idx ) {
  static char const* const names[] = {
    EVENT_LIST( F4L_GEN_NAME )
    "FL_KEYBOARD", // alias for "FL_KEYDOWN"
    NULL
  };
  static Fl_Event const values[] = {
    EVENT_LIST( F4L_GEN_VALUE )
    FL_KEYBOARD, // alias for FL_KEYDOWN
    (Fl_Event)0 // dummy value
  };
  return values[ luaL_checkoption( L, idx, NULL, names ) ];
}

MOON_LOCAL void f4l_push_event( lua_State* L, Fl_Event e ) {
  switch( e ) {
    EVENT_LIST( F4L_GEN_CASE )
    default:
      luaL_error( L, "unknown Fl_Event" );
  }
}
#endif


#define LABELTYPE_LIST( _ ) \
  _( "NORMAL_LABEL", FL_NORMAL_LABEL ) \
  _( "NO_LABEL", FL_NO_LABEL ) \
  _( "SHADOW_LABEL", _FL_SHADOW_LABEL ) \
  _( "ENGRAVED_LABEL", _FL_ENGRAVED_LABEL ) \
  _( "EMBOSSED_LABEL", _FL_EMBOSSED_LABEL ) \
  _( "MULTI_LABEL", _FL_MULTI_LABEL ) \
  _( "ICON_LABEL", _FL_ICON_LABEL ) \
  _( "IMAGE_LABEL", _FL_IMAGE_LABEL )

MOON_LOCAL Fl_Labeltype f4l_check_labeltype( lua_State* L, int idx ) {
  static int setup = 1;
  if( setup ) {
    /* the following macros have side effects! */
    (void)(FL_SHADOW_LABEL);
    (void)(FL_ENGRAVED_LABEL);
    (void)(FL_EMBOSSED_LABEL);
    setup = 0;
  }
  static char const* const names[] = {
    LABELTYPE_LIST( F4L_GEN_NAME )
    NULL
  };
  static Fl_Labeltype const values[] = {
    LABELTYPE_LIST( F4L_GEN_VALUE )
    (Fl_Labeltype)0 // dummy value
  };
  return values[ luaL_checkoption( L, idx, NULL, names ) ];
}

MOON_LOCAL void f4l_push_labeltype( lua_State* L, Fl_Labeltype t ) {
  switch( t ) {
    LABELTYPE_LIST( F4L_GEN_CASE )
    default:
      luaL_error( L, "unknown Fl_Labeltype" );
  }
}


#if 0
#define MODE_LIST( _ ) \
  _( "RGB", FL_RGB ) \
  _( "INDEX", FL_INDEX ) \
  _( "SINGLE", FL_SINGLE ) \
  _( "DOUBLE", FL_DOUBLE ) \
  _( "ACCUM", FL_ACCUM ) \
  _( "ALPHA", FL_ALPHA ) \
  _( "DEPTH", FL_DEPTH ) \
  _( "STENCIL", FL_STENCIL ) \
  _( "RGB8", FL_RGB8 ) \
  _( "MULTISAMPLE", FL_MULTISAMPLE ) \
  _( "STEREO", FL_STEREO ) \
  _( "FAKE_SINGLE", FL_FAKE_SINGLE )

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
#endif


#define WHEN_LIST( _ ) \
  _( "WHEN_NEVER", FL_WHEN_NEVER ) \
  _( "WHEN_CHANGED", FL_WHEN_CHANGED ) \
  _( "WHEN_NOT_CHANGED", FL_WHEN_NOT_CHANGED ) \
  _( "WHEN_RELEASE", FL_WHEN_RELEASE ) \
  _( "WHEN_RELEASE_ALWAYS", FL_WHEN_RELEASE_ALWAYS ) \
  _( "WHEN_ENTER_KEY", FL_WHEN_ENTER_KEY ) \
  _( "WHEN_ENTER_KEY_ALWAYS", FL_WHEN_ENTER_KEY_ALWAYS ) \
  _( "WHEN_ENTER_KEY_CHANGED", FL_WHEN_ENTER_KEY_CHANGED )

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
  _( "CURSOR_DEFAULT", FL_CURSOR_DEFAULT ) \
  _( "CURSOR_ARROW", FL_CURSOR_ARROW ) \
  _( "CURSOR_CROSS", FL_CURSOR_CROSS ) \
  _( "CURSOR_WAIT", FL_CURSOR_WAIT ) \
  _( "CURSOR_INSERT", FL_CURSOR_INSERT ) \
  _( "CURSOR_HAND", FL_CURSOR_HAND ) \
  _( "CURSOR_HELP", FL_CURSOR_HELP ) \
  _( "CURSOR_MOVE", FL_CURSOR_MOVE ) \
  _( "CURSOR_NS", FL_CURSOR_NS ) \
  _( "CURSOR_WE", FL_CURSOR_WE ) \
  _( "CURSOR_NWSE", FL_CURSOR_NWSE ) \
  _( "CURSOR_NESW", FL_CURSOR_NESW ) \
  _( "CURSOR_NONE", FL_CURSOR_NONE ) \
  _( "CURSOR_N", FL_CURSOR_N ) \
  _( "CURSOR_NE", FL_CURSOR_NE ) \
  _( "CURSOR_E", FL_CURSOR_E ) \
  _( "CURSOR_SE", FL_CURSOR_SE ) \
  _( "CURSOR_S", FL_CURSOR_S ) \
  _( "CURSOR_SW", FL_CURSOR_SW ) \
  _( "CURSOR_W", FL_CURSOR_W ) \
  _( "CURSOR_NW", FL_CURSOR_NW )

MOON_LOCAL Fl_Cursor f4l_check_cursor( lua_State* L, int idx ) {
  static char const* const names[] = {
    CURSOR_LIST( F4L_GEN_NAME )
    NULL
  };
  static Fl_Cursor const values[] = {
    CURSOR_LIST( F4L_GEN_VALUE )
    (Fl_Cursor)0 // dummy value
  };
  return values[ luaL_checkoption( L, idx, NULL, names ) ];
}

MOON_LOCAL void f4l_push_cursor( lua_State* L, Fl_Cursor c ) {
  switch( c ) {
    CURSOR_LIST( F4L_GEN_CASE )
    default:
      luaL_error( L, "unknown Fl_Cursor" );
  }
}


#define BOXTYPE_LIST( _ ) \
  _( "NO_BOX", FL_NO_BOX ) \
  _( "FLAT_BOX", FL_FLAT_BOX ) \
  _( "UP_BOX", FL_UP_BOX ) \
  _( "DOWN_BOX", FL_DOWN_BOX ) \
  _( "UP_FRAME", FL_UP_FRAME ) \
  _( "DOWN_FRAME", FL_DOWN_FRAME ) \
  _( "THIN_UP_BOX", FL_THIN_UP_BOX ) \
  _( "THIN_DOWN_BOX", FL_THIN_DOWN_BOX ) \
  _( "THIN_UP_FRAME", FL_THIN_UP_FRAME ) \
  _( "THIN_DOWN_FRAME", FL_THIN_DOWN_FRAME ) \
  _( "ENGRAVED_BOX", FL_ENGRAVED_BOX ) \
  _( "EMBOSSED_BOX", FL_EMBOSSED_BOX ) \
  _( "ENGRAVED_FRAME", FL_ENGRAVED_FRAME ) \
  _( "EMBOSSED_FRAME", FL_EMBOSSED_FRAME ) \
  _( "BORDER_BOX", FL_BORDER_BOX ) \
  _( "SHADOW_BOX", _FL_SHADOW_BOX ) \
  _( "BORDER_FRAME", FL_BORDER_FRAME ) \
  _( "SHADOW_FRAME", _FL_SHADOW_FRAME ) \
  _( "ROUNDED_BOX", _FL_ROUNDED_BOX ) \
  _( "RSHADOW_BOX", _FL_RSHADOW_BOX ) \
  _( "ROUNDED_FRAME", _FL_ROUNDED_FRAME ) \
  _( "RFLAT_BOX", _FL_RFLAT_BOX ) \
  _( "ROUND_UP_BOX", _FL_ROUND_UP_BOX ) \
  _( "ROUND_DOWN_BOX", _FL_ROUND_DOWN_BOX ) \
  _( "DIAMOND_UP_BOX", _FL_DIAMOND_UP_BOX ) \
  _( "DIAMOND_DOWN_BOX", _FL_DIAMOND_DOWN_BOX ) \
  _( "OVAL_BOX", _FL_OVAL_BOX ) \
  _( "OSHADOW_BOX", _FL_OSHADOW_BOX ) \
  _( "OVAL_FRAME", _FL_OVAL_FRAME ) \
  _( "OFLAT_BOX", _FL_OFLAT_BOX ) \
  _( "PLASTIC_UP_BOX", _FL_PLASTIC_UP_BOX ) \
  _( "PLASTIC_DOWN_BOX", _FL_PLASTIC_DOWN_BOX ) \
  _( "PLASTIC_UP_FRAME", _FL_PLASTIC_UP_FRAME ) \
  _( "PLASTIC_DOWN_FRAME", _FL_PLASTIC_DOWN_FRAME ) \
  _( "PLASTIC_THIN_UP_BOX", _FL_PLASTIC_THIN_UP_BOX ) \
  _( "PLASTIC_THIN_DOWN_BOX", _FL_PLASTIC_THIN_DOWN_BOX ) \
  _( "PLASTIC_ROUND_UP_BOX", _FL_PLASTIC_ROUND_UP_BOX ) \
  _( "PLASTIC_ROUND_DOWN_BOX", _FL_PLASTIC_ROUND_DOWN_BOX ) \
  _( "GTK_UP_BOX", _FL_GTK_UP_BOX ) \
  _( "GTK_DOWN_BOX", _FL_GTK_DOWN_BOX ) \
  _( "GTK_UP_FRAME", _FL_GTK_UP_FRAME ) \
  _( "GTK_DOWN_FRAME", _FL_GTK_DOWN_FRAME ) \
  _( "GTK_THIN_UP_BOX", _FL_GTK_THIN_UP_BOX ) \
  _( "GTK_THIN_DOWN_BOX", _FL_GTK_THIN_DOWN_BOX ) \
  _( "GTK_THIN_UP_FRAME", _FL_GTK_THIN_UP_FRAME ) \
  _( "GTK_THIN_DOWN_FRAME", _FL_GTK_THIN_DOWN_FRAME ) \
  _( "GTK_ROUND_UP_BOX", _FL_GTK_ROUND_UP_BOX ) \
  _( "GTK_ROUND_DOWN_BOX", _FL_GTK_ROUND_DOWN_BOX )

MOON_LOCAL Fl_Boxtype f4l_check_boxtype( lua_State* L, int idx ) {
  static int setup = 1;
  if( setup ) {
    /* the following macros have side effects! */
    (void)FL_ROUND_UP_BOX;
    (void)FL_SHADOW_BOX;
    (void)FL_ROUNDED_BOX;
    (void)FL_RFLAT_BOX;
    (void)FL_RSHADOW_BOX;
    (void)FL_DIAMOND_UP_BOX;
    (void)FL_OVAL_BOX;
    (void)FL_PLASTIC_UP_BOX;
    (void)FL_GTK_UP_BOX;
    setup = 0;
  }
  static char const* const names[] = {
    BOXTYPE_LIST( F4L_GEN_NAME )
    NULL
  };
  static Fl_Boxtype const values[] = {
    BOXTYPE_LIST( F4L_GEN_VALUE )
    (Fl_Boxtype)0 // dummy value
  };
  return values[ luaL_checkoption( L, idx, NULL, names ) ];
}

MOON_LOCAL void f4l_push_boxtype( lua_State* L, Fl_Boxtype b ) {
  switch( b ) {
    BOXTYPE_LIST( F4L_GEN_CASE )
    default:
      luaL_error( L, "unknown Fl_Boxtype" );
  }
}


#define ALIGN_LIST( _ ) \
  _( "ALIGN_CENTER", FL_ALIGN_CENTER ) \
  _( "ALIGN_TOP", FL_ALIGN_TOP ) \
  _( "ALIGN_BOTTOM", FL_ALIGN_BOTTOM ) \
  _( "ALIGN_RIGHT", FL_ALIGN_RIGHT ) \
  _( "ALIGN_LEFT", FL_ALIGN_LEFT ) \
  _( "ALIGN_INSIDE", FL_ALIGN_INSIDE ) \
  _( "ALIGN_TEXT_OVER_IMAGE", FL_ALIGN_TEXT_OVER_IMAGE ) \
  _( "ALIGN_IMAGE_OVER_TEXT", FL_ALIGN_IMAGE_OVER_TEXT ) \
  _( "ALIGN_CLIP", FL_ALIGN_CLIP ) \
  _( "ALIGN_WRAP", FL_ALIGN_WRAP ) \
  _( "ALIGN_IMAGE_NEXT_TO_TEXT", FL_ALIGN_IMAGE_NEXT_TO_TEXT ) \
  _( "ALIGN_TEXT_NEXT_TO_IMAGE", FL_ALIGN_TEXT_NEXT_TO_IMAGE ) \
  _( "ALIGN_IMAGE_BACKDROP", FL_ALIGN_IMAGE_BACKDROP ) \
  _( "ALIGN_TOP_LEFT", FL_ALIGN_TOP_LEFT ) \
  _( "ALIGN_TOP_RIGHT", FL_ALIGN_TOP_RIGHT ) \
  _( "ALIGN_BOTTOM_LEFT", FL_ALIGN_BOTTOM_LEFT ) \
  _( "ALIGN_BOTTOM_RIGHT", FL_ALIGN_BOTTOM_RIGHT ) \
  _( "ALIGN_LEFT_TOP", FL_ALIGN_LEFT_TOP ) \
  _( "ALIGN_RIGHT_TOP", FL_ALIGN_RIGHT_TOP ) \
  _( "ALIGN_LEFT_BOTTOM", FL_ALIGN_LEFT_BOTTOM ) \
  _( "ALIGN_RIGHT_BOTTOM", FL_ALIGN_RIGHT_BOTTOM ) \
  _( "ALIGN_NOWRAP", FL_ALIGN_NOWRAP ) \
  _( "ALIGN_POSITION_MASK", FL_ALIGN_POSITION_MASK ) \
  _( "ALIGN_IMAGE_MASK", FL_ALIGN_IMAGE_MASK )

#define MOON_FLAG_NAME "fltk4lua.Align"
#define MOON_FLAG_TYPE Fl_Align
#define MOON_FLAG_SUFFIX align
#define MOON_FLAG_USECACHE
#define MOON_FLAG_NORELOPS
#include "moon_flag.h"

MOON_LOCAL Fl_Align f4l_check_align( lua_State* L, int idx ) {
  if( lua_type( L, idx ) == LUA_TSTRING ) {
    static char const* const names[] = {
      ALIGN_LIST( F4L_GEN_NAME )
      NULL
    };
    static Fl_Align const values[] = {
      ALIGN_LIST( F4L_GEN_VALUE )
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
  _( "HELVETICA", FL_HELVETICA ) \
  _( "HELVETICA_BOLD", FL_HELVETICA_BOLD ) \
  _( "HELVETICA_ITALIC", FL_HELVETICA_ITALIC ) \
  _( "HELVETICA_BOLD_ITALIC", FL_HELVETICA_BOLD_ITALIC ) \
  _( "COURIER", FL_COURIER ) \
  _( "COURIER_BOLD", FL_COURIER_BOLD ) \
  _( "COURIER_ITALIC", FL_COURIER_ITALIC ) \
  _( "COURIER_BOLD_ITALIC", FL_COURIER_BOLD_ITALIC ) \
  _( "TIMES", FL_TIMES ) \
  _( "TIMES_BOLD", FL_TIMES_BOLD ) \
  _( "TIMES_ITALIC", FL_TIMES_ITALIC ) \
  _( "TIMES_BOLD_ITALIC", FL_TIMES_BOLD_ITALIC ) \
  _( "SYMBOL", FL_SYMBOL ) \
  _( "SCREEN", FL_SCREEN ) \
  _( "SCREEN_BOLD", FL_SCREEN_BOLD ) \
  _( "ZAPF_DINGBATS", FL_ZAPF_DINGBATS )

MOON_LOCAL Fl_Font f4l_check_font( lua_State* L, int idx ) {
  if( lua_type( L, idx ) == LUA_TNUMBER )
    return moon_checkint( L, idx, 0, FL_FREE_FONT-1 );
  else {
    static char const* const names[] = {
      FONT_LIST( F4L_GEN_NAME )
      NULL
    };
    static Fl_Font const values[] = {
      FONT_LIST( F4L_GEN_VALUE )
      (Fl_Font)0 // dummy value
    };
    return values[ luaL_checkoption( L, idx, NULL, names ) ];
  }
}

MOON_LOCAL void f4l_push_font( lua_State* L, Fl_Font f ) {
  switch( f ) {
    FONT_LIST( F4L_GEN_CASE )
    default:
      luaL_error( L, "unknown Fl_Font" );
  }
}


#define FD_WHEN_LIST( _ ) \
  _( "READ", FL_READ ) \
  _( "WRITE", FL_WRITE ) \
  _( "EXCEPT", FL_EXCEPT )

#define MOON_FLAG_NAME "fltk4lua.Fd_When"
#define MOON_FLAG_TYPE int
#define MOON_FLAG_SUFFIX fd_when
#define MOON_FLAG_USECACHE
#define MOON_FLAG_NORELOPS
#include "moon_flag.h"

MOON_LOCAL int f4l_check_fd_when( lua_State* L, int idx ) {
  return moon_flag_get_fd_when( L, idx );
}


#define COLOR_LIST( _ ) \
  _( "FOREGROUND_COLOR", FL_FOREGROUND_COLOR ) \
  _( "BACKGROUND2_COLOR", FL_BACKGROUND2_COLOR ) \
  _( "INACTIVE_COLOR", FL_INACTIVE_COLOR ) \
  _( "SELECTION_COLOR", FL_SELECTION_COLOR ) \
  _( "GRAY0", FL_GRAY0 ) \
  _( "DARK3", FL_DARK3 ) \
  _( "DARK2", FL_DARK2 ) \
  _( "DARK1", FL_DARK1 ) \
  _( "BACKGROUND_COLOR", FL_BACKGROUND_COLOR ) \
  _( "LIGHT1", FL_LIGHT1 ) \
  _( "LIGHT2", FL_LIGHT2 ) \
  _( "LIGHT3", FL_LIGHT3 ) \
  _( "BLACK", FL_BLACK ) \
  _( "RED", FL_RED ) \
  _( "GREEN", FL_GREEN ) \
  _( "YELLOW", FL_YELLOW ) \
  _( "BLUE", FL_BLUE ) \
  _( "MAGENTA", FL_MAGENTA ) \
  _( "CYAN", FL_CYAN ) \
  _( "DARK_RED", FL_DARK_RED ) \
  _( "DARK_GREEN", FL_DARK_GREEN ) \
  _( "DARK_YELLOW", FL_DARK_YELLOW ) \
  _( "DARK_BLUE", FL_DARK_BLUE ) \
  _( "DARK_MAGENTA", FL_DARK_MAGENTA ) \
  _( "DARK_CYAN", FL_DARK_CYAN ) \
  _( "WHITE", FL_WHITE )

#define MOON_FLAG_NAME "fltk4lua.Color"
#define MOON_FLAG_TYPE Fl_Color
#define MOON_FLAG_SUFFIX color
#define MOON_FLAG_NOBITOPS
#include "moon_flag.h"

MOON_LOCAL Fl_Color f4l_check_color( lua_State* L, int idx ) {
  if( lua_type( L, idx ) == LUA_TNUMBER )
    return static_cast< Fl_Color >( moon_checkint( L, idx, 0, 0xFFFFFF00u ) );
  else
    return moon_flag_get_color( L, idx );
}

MOON_LOCAL void f4l_push_color( lua_State* L, Fl_Color c ) {
  moon_flag_new_color( L, c );
}


#define OPTION_LIST( _ ) \
  _( "OPTION_ARROW_FOCUS", Fl::OPTION_ARROW_FOCUS ) \
  _( "OPTION_VISIBLE_FOCUS", Fl::OPTION_VISIBLE_FOCUS ) \
  _( "OPTION_DND_TEXT", Fl::OPTION_DND_TEXT ) \
  _( "OPTION_SHOW_TOOLTIPS", Fl::OPTION_SHOW_TOOLTIPS )

MOON_LOCAL Fl::Fl_Option f4l_check_option( lua_State* L, int idx ) {
  static char const* const names[] = {
    OPTION_LIST( F4L_GEN_RNAME )
    NULL
  };
  static Fl::Fl_Option const values[] = {
    OPTION_LIST( F4L_GEN_VALUE )
    (Fl::Fl_Option)0 // dummy value
  };
  return values[ luaL_checkoption( L, idx, NULL, names ) ];
}


F4L_LUA_LLINKAGE_BEGIN

static int f4l_inactive( lua_State* L ) {
  Fl_Color c = f4l_check_color( L, 1 );
  F4L_TRY( L ) {
    f4l_push_color( L, fl_inactive( c ) );
  } F4L_CATCH( L );
  return 1;
}


static int f4l_contrast( lua_State* L ) {
  Fl_Color fg = f4l_check_color( L, 1 );
  Fl_Color bg = f4l_check_color( L, 2 );
  F4L_TRY( L ) {
    f4l_push_color( L, fl_contrast( fg, bg ) );
  } F4L_CATCH( L );
  return 1;
}


static int f4l_color_average( lua_State* L ) {
  Fl_Color c1 = f4l_check_color( L, 1 );
  Fl_Color c2 = f4l_check_color( L, 2 );
  float weight = static_cast< float >( luaL_checknumber( L, 3 ) );
  F4L_TRY( L ) {
    f4l_push_color( L, fl_color_average( c1, c2, weight ) );
  } F4L_CATCH( L );
  return 1;
}


static int f4l_lighter( lua_State* L ) {
  Fl_Color c = f4l_check_color( L, 1 );
  F4L_TRY( L ) {
    f4l_push_color( L, fl_lighter( c ) );
  } F4L_CATCH( L );
  return 1;
}


static int f4l_darker( lua_State* L ) {
  Fl_Color c = f4l_check_color( L, 1 );
  F4L_TRY( L ) {
    f4l_push_color( L, fl_darker( c ) );
  } F4L_CATCH( L );
  return 1;
}


static int f4l_rgb_color( lua_State* L ) {
  F4L_TRY( L ) {
    if( lua_gettop( L ) > 1 ) {
      uchar r = moon_checkint( L, 1, 0, 255 );
      uchar g = moon_checkint( L, 2, 0, 255 );
      uchar b = moon_checkint( L, 3, 0, 255 );
      f4l_push_color( L, fl_rgb_color( r, g, b ) );
    } else {
      uchar g = moon_checkint( L, 1, 0, 255 );
      f4l_push_color( L, fl_rgb_color( g ) );
    }
  } F4L_CATCH( L );
  return 1;
}


static int f4l_get_color( lua_State* L ) {
  Fl_Color c = f4l_check_color( L, 1 );
  uchar r, g, b;
  F4L_TRY( L ) {
    Fl::get_color( c, r, g, b );
    lua_pushinteger( L, r );
    lua_pushinteger( L, g );
    lua_pushinteger( L, b );
  } F4L_CATCH( L );
  return 3;
}


static int f4l_set_color( lua_State* L ) {
  Fl_Color c = f4l_check_color( L, 1 );
  uchar r = moon_checkint( L, 2, 0, 255 );
  uchar g = moon_checkint( L, 3, 0, 255 );
  uchar b = moon_checkint( L, 4, 0, 255 );
  F4L_TRY( L ) {
    Fl::set_color( c, r, g, b );
  } F4L_CATCH( L );
  return 0;
}


static int f4l_cursor( lua_State* L ) {
  Fl_Cursor c = f4l_check_cursor( L, 1 );
  Fl_Color fg = f4l_check_color( L, 2 );
  Fl_Color bg = f4l_check_color( L, 3 );
  F4L_TRY( L ) {
    fl_cursor( c, fg, bg );
  } F4L_CATCH( L );
  return 0;
}


static int f4l_shortcut_label( lua_State* L ) {
  Fl_Shortcut s = f4l_check_shortcut( L, 1 );
  F4L_TRY( L ) {
    lua_pushstring( L, fl_shortcut_label( s ) );
  } F4L_CATCH( L );
  return 1;
}

F4L_LUA_LLINKAGE_END


MOON_LOCAL void f4l_enums_setup( lua_State* L ) {
  luaL_Reg const functions[] = {
    { "inactive", f4l_inactive },
    { "contrast", f4l_contrast },
    { "color_average", f4l_color_average },
    { "lighter", f4l_lighter },
    { "darker", f4l_darker },
    { "rgb_color", f4l_rgb_color },
    { "get_color", f4l_get_color },
    { "set_color", f4l_set_color },
    { "cursor", f4l_cursor },
    { "shortcut_label", f4l_shortcut_label },
    { NULL, NULL }
  };
  moon_flag_def_shortcut( L );
  // the default moon_flag operations are insufficient in this case:
  luaL_getmetatable( L, "fltk4lua.Shortcut" );
  lua_pushcfunction( L, shortcut_add );
  lua_setfield( L, -2, "__add" );
  lua_pop( L, 1 );
#if 0
  moon_flag_def_damage( L );
#endif
#if 0
  moon_flag_def_mode( L );
#endif
  moon_flag_def_when( L );
  moon_flag_def_fd_when( L );
  moon_flag_def_align( L );
  moon_flag_def_color( L );
#define GEN_UDATA( _a, _b ) \
  (moon_flag_new_shortcut( L, _b ), lua_setfield( L, -2, _a ));
  SHORTCUT_LIST( GEN_UDATA )
#undef GEN_UDATA
#if 0
#define GEN_UDATA( _a, _b ) \
  (moon_flag_new_damage( L, _b ), lua_setfield( L, -2, _a ));
  DAMAGE_LIST( GEN_UDATA )
#undef GEN_UDATA
#endif
#if 0
#define GEN_UDATA( _a, _b ) \
  (moon_flag_new_mode( L, _b ), lua_setfield( L, -2, _a ));
  MODE_LIST( GEN_UDATA )
#undef GEN_UDATA
#endif
#define GEN_UDATA( _a, _b ) \
  (moon_flag_new_when( L, _b ), lua_setfield( L, -2, _a ));
  WHEN_LIST( GEN_UDATA )
#undef GEN_UDATA
#define GEN_UDATA( _a, _b ) \
  (moon_flag_new_fd_when( L, _b ), lua_setfield( L, -2, _a ));
  FD_WHEN_LIST( GEN_UDATA )
#undef GEN_UDATA
#define GEN_UDATA( _a, _b ) \
  (moon_flag_new_align( L, _b ), lua_setfield( L, -2, _a ));
  ALIGN_LIST( GEN_UDATA )
#undef GEN_UDATA
#define GEN_UDATA( _a, _b ) \
  (moon_flag_new_color( L, _b ), lua_setfield( L, -2, _a ));
  COLOR_LIST( GEN_UDATA )
#undef GEN_UDATA
  luaL_setfuncs( L, functions, 0 );
}

