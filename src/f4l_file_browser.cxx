#include "fltk4lua.hxx"
#include "f4l_browser.hxx"
#include "f4l_browserx.hxx"
#include "f4l_widget.hxx"
#include "f4l_enums.hxx"
#include <FL/Fl_File_Browser.H>
#include <cstring>
#include <climits>


#define TYPE_LIST( _ ) \
  _( "FILES", Fl_File_Browser::FILES ) \
  _( "DIRECTORIES", Fl_File_Browser::DIRECTORIES )

  F4L_GEN_TYPE_ENUM( TYPE_LIST, fbrowser )


namespace {

  inline Fl_File_Browser* check_fbrowser( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_FILE_BROWSER_NAME );
    return static_cast< Fl_File_Browser* >( p );
  }


  int fbrowser_index_( lua_State* L, Fl_File_Browser* b,
                       char const* key, size_t n ) {
    using namespace std;
    switch( n ) {
      case 6:
        if( F4L_MEMCMP( key, "filter", 6 ) == 0 ) {
          lua_pushstring( L, b->filter() );
          return 1;
        }
        break;
      case 8:
        if( F4L_MEMCMP( key, "filetype", 8 ) == 0 ) {
          f4l_push_type_fbrowser( L, b->filetype() );
          return 1;
        } else if( F4L_MEMCMP( key, "iconsize", 8 ) == 0 ) {
          lua_pushinteger( L, b->iconsize() );
          return 1;
        } else if( F4L_MEMCMP( key, "textsize", 8 ) == 0 ) {
          lua_pushinteger( L, b->textsize() );
          return 1;
        }
        break;
    }
    return 0;
  }


  int fbrowser_newindex_( lua_State* L, Fl_File_Browser* b,
                          char const* key, size_t n ) {
    using namespace std;
    switch( n ) {
      case 6:
        if( F4L_MEMCMP( key, "filter", 6 ) == 0 ) {
          b->filter( luaL_checkstring( L, 3 ) );
          return 1;
        }
        break;
      case 8:
        if( F4L_MEMCMP( key, "filetype", 8 ) == 0 ) {
          b->filetype( f4l_check_type_fbrowser( L, 3 ) );
          return 1;
        } else if( F4L_MEMCMP( key, "iconsize", 8 ) == 0 ) {
          b->iconsize( moon_checkint( L, 3, 0, UCHAR_MAX ) );
          return 1;
        } else if( F4L_MEMCMP( key, "textsize", 8 ) == 0 ) {
          b->textsize( moon_checkint( L, 3, 0, INT_MAX ) );
          return 1;
        }
        break;
    }
    return 0;
  }

} // anonymous namespace


F4L_DEF_DELETE( Fl_File_Browser )


F4L_LUA_LLINKAGE_BEGIN

static int new_file_browser( lua_State* L ) {
  F4L_TRY( L ) {
    f4l_new_widget< Fl_File_Browser >( L, F4L_FILE_BROWSER_NAME,
                                       f4l_delete_Fl_File_Browser );
  } F4L_CATCH( L );
  return 1;
}


static int fbrowser_index( lua_State* L ) {
  Fl_File_Browser* b = check_fbrowser( L, 1 );
  size_t n = 0;
  char const* key = luaL_checklstring( L, 2, &n );
  F4L_TRY( L ) {
    if( !fbrowser_index_( L, b, key, n ) &&
        !f4l_browser_index_( L, b, key, n ) &&
        !f4l_browserx_index_( L, b, key, n ) &&
        !f4l_widget_index_( L, b, key, n ) &&
        !f4l_bad_property( L, F4L_FILE_BROWSER_NAME, key ) )
      lua_pushnil( L );
  } F4L_CATCH( L );
  return 1;
}


static int fbrowser_newindex( lua_State* L ) {
  Fl_File_Browser* b = check_fbrowser( L, 1 );
  size_t n = 0;
  char const* key = luaL_checklstring( L, 2, &n );
  F4L_TRY( L ) {
    (void)(fbrowser_newindex_( L, b, key, n ) ||
           f4l_browser_newindex_( L, b, key, n ) ||
           f4l_browserx_newindex_( L, b, key, n ) ||
           f4l_widget_newindex_( L, b, key, n ) ||
           f4l_bad_property( L, F4L_FILE_BROWSER_NAME, key ));
  } F4L_CATCH( L );
  return 0;
}


static int fbrowser_load( lua_State* L ) {
  static char const* names[] = {
    "fl_numericsort", "fl_casenumericsort",
    "fl_alphasort", "fl_casealphasort", NULL
  };
  static Fl_File_Sort_F* const values[] = {
    fl_numericsort,
    fl_casenumericsort,
    fl_alphasort,
    fl_casealphasort
  };
  Fl_File_Browser* b = check_fbrowser( L, 1 );
  char const* dname = luaL_checkstring( L, 2 );
  Fl_File_Sort_F* f = values[ luaL_checkoption( L, 3, "fl_numericsort", names ) ];
  F4L_TRY( L ) {
    return luaL_fileresult( L, b->load( dname, f ), dname );
  } F4L_CATCH( L );
  return 0;
}

F4L_LUA_LLINKAGE_END


F4L_DEF_CAST( Fl_File_Browser, Fl_Browser )
F4L_DEF_CAST( Fl_File_Browser, Fl_Browser_ )
F4L_DEF_CAST( Fl_File_Browser, Fl_Widget )


MOON_LOCAL void f4l_file_browser_setup( lua_State* L ) {
  luaL_Reg const methods[] = {
    F4L_WIDGET_METHODS,
    F4L_BROWSERX_METHODS,
    F4L_BROWSER_METHODS,
    { "load", fbrowser_load },
    { "__index", fbrowser_index },
    { "__newindex", fbrowser_newindex },
    { NULL, NULL }
  };
  moon_defobject( L, F4L_FILE_BROWSER_NAME, 0, methods, 0 );
  moon_defcast( L, F4L_FILE_BROWSER_NAME, F4L_BROWSER_NAME,
                f4l_cast_Fl_File_Browser_Fl_Browser );
  moon_defcast( L, F4L_FILE_BROWSER_NAME, F4L_BROWSERX_NAME,
                f4l_cast_Fl_File_Browser_Fl_Browser_ );
  moon_defcast( L, F4L_FILE_BROWSER_NAME, F4L_WIDGET_NAME,
                f4l_cast_Fl_File_Browser_Fl_Widget );
  f4l_new_class_table( L, "File_Browser", new_file_browser );
}

