#include "fltk4lua.hxx"
#include "f4l_input.hxx"
#include "f4l_widget.hxx"
#include "f4l_enums.hxx"
#include <cstring>
#include <climits>


#define TYPE_LIST( _ ) \
  _( "FL_NORMAL_INPUT", FL_NORMAL_INPUT ) \
  _( "FL_FLOAT_INPUT", FL_FLOAT_INPUT ) \
  _( "FL_INT_INPUT", FL_INT_INPUT ) \
  _( "FL_HIDDEN_INPUT", FL_HIDDEN_INPUT ) \
  _( "FL_MULTILINE_INPUT", FL_MULTILINE_INPUT ) \
  _( "FL_SECRET_INPUT", FL_SECRET_INPUT ) \
  _( "FL_NORMAL_OUTPUT", FL_NORMAL_OUTPUT ) \
  _( "FL_MULTILINE_OUTPUT", FL_MULTILINE_OUTPUT ) \
  _( "FL_MULTILINE_INPUT_WRAP", FL_MULTILINE_INPUT_WRAP ) \
  _( "FL_MULTILINE_OUTPUT_WRAP", FL_MULTILINE_OUTPUT_WRAP )

  F4L_GEN_TYPE_ENUM( TYPE_LIST, input )


namespace {

  inline Fl_Input* check_input( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_INPUT_NAME );
    return static_cast< Fl_Input* >( p );
  }

  inline Fl_File_Input* check_file_input( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_FILE_INPUT_NAME );
    return static_cast< Fl_File_Input* >( p );
  }


  int file_input_index_( lua_State* L, Fl_File_Input* fi,
                         char const* key, size_t n ) {
    using namespace std;
    switch( n ) {
      case 5:
        if( F4L_MEMCMP( key, "value", 5 ) == 0 ) {
          lua_pushstring( L, fi->value() );
          return 1;
        }
        break;
      case 8:
        if( F4L_MEMCMP( key, "down_box", 8 ) == 0 ) {
          f4l_push_boxtype( L, fi->down_box() );
          return 1;
        }
        break;
      case 10:
        if( F4L_MEMCMP( key, "errorcolor", 10 ) == 0 ) {
          f4l_push_color( L, fi->errorcolor() );
          return 1;
        }
        break;
    }
    return 0;
  }


  int file_input_newindex_( lua_State* L, Fl_File_Input* fi,
                            char const* key, size_t n ) {
    using namespace std;
    switch( n ) {
      case 5:
        if( F4L_MEMCMP( key, "value", 5 ) == 0 ) {
          size_t l = 0;
          char const* s = luaL_checklstring( L, 3, &l );
          fi->value( s, static_cast< int >( l ) );
          return 1;
        }
        break;
      case 8:
        if( F4L_MEMCMP( key, "down_box", 8 ) == 0 ) {
          fi->down_box( f4l_check_boxtype( L, 3 ) );
          return 1;
        }
        break;
      case 10:
        if( F4L_MEMCMP( key, "errorcolor", 10 ) == 0 ) {
          fi->errorcolor( f4l_check_color( L, 3 ) );
          return 1;
        }
        break;
    }
    return 0;
  }

} // anonymous namespace


F4L_DEF_DELETE( Fl_Input )
F4L_DEF_DELETE( Fl_File_Input )


F4L_LUA_LLINKAGE_BEGIN

static int new_input( lua_State* L ) {
  F4L_TRY( L ) {
    f4l_new_widget< Fl_Input >( L, F4L_INPUT_NAME,
                                f4l_delete_Fl_Input );
  } F4L_CATCH( L );
  return 1;
}


static int new_file_input( lua_State* L ) {
  F4L_TRY( L ) {
    f4l_new_widget< Fl_File_Input >( L, F4L_FILE_INPUT_NAME,
                                     f4l_delete_Fl_File_Input );
  } F4L_CATCH( L );
  return 1;
}


static int input_index( lua_State* L ) {
  Fl_Input* i = check_input( L, 1 );
  size_t n = 0;
  char const* key = luaL_checklstring( L, 2, &n );
  F4L_TRY( L ) {
    if( !f4l_input_index_( L, i, key, n ) &&
        !f4l_widget_index_( L, i, key, n ) &&
        !f4l_bad_property( L, F4L_INPUT_NAME, key ) )
      lua_pushnil( L );
  } F4L_CATCH( L );
  return 1;
}


static int input_newindex( lua_State* L ) {
  Fl_Input* i = check_input( L, 1 );
  size_t n = 0;
  char const* key = luaL_checklstring( L, 2, &n );
  F4L_TRY( L ) {
    (void)(f4l_input_newindex_( L, i, key, n ) ||
           f4l_widget_newindex_( L, i, key, n ) ||
           f4l_bad_property( L, F4L_INPUT_NAME, key ));
  } F4L_CATCH( L );
  return 0;
}


static int file_input_index( lua_State* L ) {
  Fl_File_Input* fi = check_file_input( L, 1 );
  size_t n = 0;
  char const* key = luaL_checklstring( L, 2, &n );
  F4L_TRY( L ) {
    if( !file_input_index_( L, fi, key, n ) &&
        !f4l_input_index_( L, fi, key, n ) &&
        !f4l_widget_index_( L, fi, key, n ) &&
        !f4l_bad_property( L, F4L_FILE_INPUT_NAME, key ) )
      lua_pushnil( L );
  } F4L_CATCH( L );
  return 1;
}


static int file_input_newindex( lua_State* L ) {
  Fl_File_Input* fi = check_file_input( L, 1 );
  size_t n = 0;
  char const* key = luaL_checklstring( L, 2, &n );
  F4L_TRY( L ) {
    (void)(file_input_newindex_( L, fi, key, n ) ||
           f4l_input_newindex_( L, fi, key, n ) ||
           f4l_widget_newindex_( L, fi, key, n ) ||
           f4l_bad_property( L, F4L_FILE_INPUT_NAME, key ));
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_input_copy( lua_State* L ) {
  Fl_Input* i = check_input( L, 1 );
  int cl = moon_checkint( L, 2, 0, 1 );
  F4L_TRY( L ) {
    lua_pushboolean( L, i->copy( cl ) );
  } F4L_CATCH( L );
  return 1;
}


MOON_LOCAL int f4l_input_copy_cuts( lua_State* L ) {
  Fl_Input* i = check_input( L, 1 );
  F4L_TRY( L ) {
    lua_pushboolean( L, i->copy_cuts() );
  } F4L_CATCH( L );
  return 1;
}


MOON_LOCAL int f4l_input_cut( lua_State* L ) {
  Fl_Input* i = check_input( L, 1 );
  F4L_TRY( L ) {
    switch( lua_gettop( L ) ) {
      case 1:
        lua_pushboolean( L, i->cut() );
        break;
      case 2: {
        int x = moon_checkint( L, 2, INT_MIN, INT_MAX );
        lua_pushboolean( L, i->cut( x ) );
        break;
      }
      default: {
        int a = moon_checkint( L, 2, 0, INT_MAX );
        int b = moon_checkint( L, 3, 0, INT_MAX );
        lua_pushboolean( L, i->cut( a, b ) );
        break;
      }
    }
  } F4L_CATCH( L );
  return 1;
}


MOON_LOCAL int f4l_input_idx( lua_State* L ) {
  Fl_Input* i = check_input( L, 1 );
  int x = moon_checkint( L, 2, 0, INT_MAX );
  F4L_TRY( L ) {
    lua_pushinteger( L, i->index( x ) );
  } F4L_CATCH( L );
  return 1;
}


MOON_LOCAL int f4l_input_insert( lua_State* L ) {
  Fl_Input* i = check_input( L, 1 );
  size_t len = 0;
  char const* s = luaL_checklstring( L, 2, &len );
  F4L_TRY( L ) {
    int n = static_cast< int >( len );
    lua_pushboolean( L, i->insert( s, n ) );
  } F4L_CATCH( L );
  return 1;
}


MOON_LOCAL int f4l_input_replace( lua_State* L ) {
  Fl_Input* i = check_input( L, 1 );
  int b = moon_checkint( L, 2, 0, INT_MAX );
  int e = moon_checkint( L, 3, 0, INT_MAX );
  size_t len = 0;
  char const* s = NULL;
  if( !lua_isnoneornil( L, 4 ) )
    s = luaL_checklstring( L, 4, &len );
  F4L_TRY( L ) {
    int n = static_cast< int >( len );
    lua_pushboolean( L, i->replace( b, e, s, n ) );
  } F4L_CATCH( L );
  return 1;
}


MOON_LOCAL int f4l_input_size( lua_State* L ) {
  Fl_Input* i = check_input( L, 1 );
  int w = moon_checkint( L, 2, 0, INT_MAX );
  int h = moon_checkint( L, 3, 0, INT_MAX );
  F4L_TRY( L ) {
    i->size( w, h );
  } F4L_CATCH( L );
  return 0;
}


MOON_LOCAL int f4l_input_undo( lua_State* L ) {
  Fl_Input* i = check_input( L, 1 );
  F4L_TRY( L ) {
    lua_pushboolean( L, i->undo() );
  } F4L_CATCH( L );
  return 1;
}

F4L_LUA_LLINKAGE_END


MOON_LOCAL int f4l_input_index_( lua_State* L, Fl_Input* i,
                                 char const* key, size_t n ) {
  using namespace std;
  switch( n ) {
    case 4:
      if( F4L_MEMCMP( key, "mark", 4 ) == 0 ) {
        lua_pushinteger( L, i->mark() );
        return 1;
      } else if( F4L_MEMCMP( key, "type", 4 ) == 0 ) {
        f4l_push_type_input( L, i->type() );
        return 1;
      } else if( F4L_MEMCMP( key, "wrap", 4 ) == 0 ) {
        lua_pushboolean( L, i->wrap() );
        return 1;
      }
      break;
    case 5:
      if( F4L_MEMCMP( key, "value", 5 ) == 0 ) {
        lua_pushlstring( L, i->value(), i->size() );
        return 1;
      }
      break;
    case 7:
      if( F4L_MEMCMP( key, "tab_nav", 7 ) == 0 ) {
        lua_pushboolean( L, i->tab_nav() );
        return 1;
      }
      break;
    case 8:
      if( F4L_MEMCMP( key, "readonly", 8 ) == 0 ) {
        lua_pushboolean( L, i->readonly() );
        return 1;
      } else if( F4L_MEMCMP( key, "shortcut", 8 ) == 0 ) {
        f4l_push_shortcut( L, i->shortcut() );
        return 1;
      } else if( F4L_MEMCMP( key, "textfont", 8 ) == 0 ) {
        f4l_push_font( L, i->textfont() );
        return 1;
      } else if( F4L_MEMCMP( key, "textsize", 8 ) == 0 ) {
        lua_pushinteger( L, i->textsize() );
        return 1;
      }
      break;
    case 9:
      if( F4L_MEMCMP( key, "textcolor", 9 ) == 0 ) {
        f4l_push_color( L, i->textcolor() );
        return 1;
      }
      break;
    case 10:
      if( F4L_MEMCMP( key, "value_size", 10 ) == 0 ) {
        lua_pushinteger( L, i->size() );
        return 1;
      }
      break;
    case 12:
      if( F4L_MEMCMP( key, "cursor_color", 12 ) == 0 ) {
        f4l_push_color( L, i->cursor_color() );
        return 1;
      } else if( F4L_MEMCMP( key, "maximum_size", 12 ) == 0 ) {
        lua_pushinteger( L, i->maximum_size() );
        return 1;
      }
      break;
    case 15:
      if( F4L_MEMCMP( key, "cursor_position", 15 ) == 0 ) {
        lua_pushinteger( L, i->position() );
        return 1;
      }
      break;
  }
  return 0;
}


MOON_LOCAL int f4l_input_newindex_( lua_State* L, Fl_Input* i,
                                    char const* key, size_t n ) {
  using namespace std;
  switch( n ) {
    case 4:
      if( F4L_MEMCMP( key, "mark", 4 ) == 0 ) {
        i->mark( moon_checkint( L, 3, 0, INT_MAX ) );
        return 1;
      } else if( F4L_MEMCMP( key, "type", 4 ) == 0 ) {
        i->type( f4l_check_type_input( L, 3 ) );
        return 1;
      } else if( F4L_MEMCMP( key, "wrap", 4 ) == 0 ) {
        i->wrap( lua_toboolean( L, 3 ) );
        return 1;
      }
      break;
    case 5:
      if( F4L_MEMCMP( key, "value", 5 ) == 0 ) {
        size_t l = 0;
        char const* s = luaL_checklstring( L, 3, &l );
        i->value( s, static_cast< int >( l ) );
        return 1;
      }
      break;
    case 7:
      if( F4L_MEMCMP( key, "tab_nav", 7 ) == 0 ) {
        i->tab_nav( lua_toboolean( L, 3 ) );
        return 1;
      }
      break;
    case 8:
      if( F4L_MEMCMP( key, "readonly", 8 ) == 0 ) {
        i->readonly( lua_toboolean( L, 3 ) );
        return 1;
      } else if( F4L_MEMCMP( key, "shortcut", 8 ) == 0 ) {
        i->shortcut( f4l_check_shortcut( L, 3 ) );
        return 1;
      } else if( F4L_MEMCMP( key, "textfont", 8 ) == 0 ) {
        i->textfont( f4l_check_font( L, 3 ) );
        return 1;
      } else if( F4L_MEMCMP( key, "textsize", 8 ) == 0 ) {
        i->textsize( moon_checkint( L, 3, 0, INT_MAX ) );
        return 1;
      }
      break;
    case 9:
      if( F4L_MEMCMP( key, "textcolor", 9 ) == 0 ) {
        i->textcolor( f4l_check_color( L, 3 ) );
        return 1;
      }
      break;
    case 12:
      if( F4L_MEMCMP( key, "cursor_color", 12 ) == 0 ) {
        i->cursor_color( f4l_check_color( L, 3 ) );
        return 1;
      } else if( F4L_MEMCMP( key, "maximum_size", 12 ) == 0 ) {
        i->maximum_size( moon_checkint( L, 3, 0, INT_MAX ) );
        return 1;
      }
      break;
    case 15:
      if( F4L_MEMCMP( key, "cursor_position", 15 ) == 0 ) {
        i->position( moon_checkint( L, 3, 0, INT_MAX ) );
        return 1;
      }
      break;
  }
  return 0;
}


F4L_DEF_CAST( Fl_Input, Fl_Widget )
F4L_DEF_CAST( Fl_File_Input, Fl_Input )
F4L_DEF_CAST( Fl_File_Input, Fl_Widget )


MOON_LOCAL void f4l_input_setup( lua_State* L ) {
  luaL_Reg const methods[] = {
    F4L_WIDGET_METHODS,
    F4L_INPUT_METHODS,
    { "__index", input_index },
    { "__newindex", input_newindex },
    { NULL, NULL }
  };
  luaL_Reg const fi_methods[] = {
    F4L_WIDGET_METHODS,
    F4L_INPUT_METHODS,
    { "__index", file_input_index },
    { "__newindex", file_input_newindex },
    { NULL, NULL }
  };

  moon_defobject( L, F4L_INPUT_NAME, 0, methods, 0 );
  moon_defcast( L, F4L_INPUT_NAME, F4L_WIDGET_NAME,
                f4l_cast_Fl_Input_Fl_Widget );

  moon_defobject( L, F4L_FILE_INPUT_NAME, 0, fi_methods, 0 );
  moon_defcast( L, F4L_FILE_INPUT_NAME, F4L_INPUT_NAME,
                f4l_cast_Fl_File_Input_Fl_Input );
  moon_defcast( L, F4L_FILE_INPUT_NAME, F4L_WIDGET_NAME,
                f4l_cast_Fl_File_Input_Fl_Widget );

  f4l_new_class_table( L, "Input", new_input );
  f4l_new_class_table( L, "File_Input", new_file_input );
}

