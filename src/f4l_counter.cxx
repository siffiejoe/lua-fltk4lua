#include "fltk4lua.hxx"
#include "f4l_valuator.hxx"
#include "f4l_widget.hxx"
#include "f4l_enums.hxx"
#include <FL/Fl_Counter.H>
#include <cstring>
#include <climits>


#define TYPE_LIST( _ ) \
  _( "FL_NORMAL_COUNTER", FL_NORMAL_COUNTER ) \
  _( "FL_SIMPLE_COUNTER", FL_SIMPLE_COUNTER )

  F4L_GEN_TYPE_ENUM( TYPE_LIST, counter )


namespace {

  inline Fl_Counter* check_counter( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_COUNTER_NAME );
    return static_cast< Fl_Counter* >( p );
  }


  int counter_index_( lua_State* L, Fl_Counter* c,
                      char const* key, size_t n ) {
    using namespace std;
    switch( n ) {
      case 4:
        if( F4L_MEMCMP( key, "step", 4 ) == 0 ) {
          lua_pushnumber( L, c->step() );
          return 1;
        } else if( F4L_MEMCMP( key, "type", 4 ) == 0 ) {
          f4l_push_type_counter( L, c->type() );
          return 1;
        }
        break;
      case 8:
        if( F4L_MEMCMP( key, "textfont", 8 ) == 0 ) {
          f4l_push_font( L, c->textfont() );
          return 1;
        } else if( F4L_MEMCMP( key, "textsize", 8 ) == 0 ) {
          lua_pushinteger( L, c->textsize() );
          return 1;
        }
        break;
      case 9:
        if( F4L_MEMCMP( key, "textcolor", 9 ) == 0 ) {
          f4l_push_color( L, c->textcolor() );
          return 1;
        }
        break;
    }
    return 0;
  }


  int counter_newindex_( lua_State* L, Fl_Counter* c,
                         char const* key, size_t n ) {
    using namespace std;
    switch( n ) {
      case 4:
        if( F4L_MEMCMP( key, "step", 4 ) == 0 ) {
          c->step( luaL_checknumber( L, 3 ) );
          return 1;
        } else if( F4L_MEMCMP( key, "type", 4 ) == 0 ) {
          c->type( f4l_check_type_counter( L, 3 ) );
          return 1;
        }
        break;
      case 5:
        if( F4L_MEMCMP( key, "lstep", 5 ) == 0 ) {
          c->lstep( luaL_checknumber( L, 3 ) );
          return 1;
        }
        break;
      case 8:
        if( F4L_MEMCMP( key, "textfont", 8 ) == 0 ) {
          c->textfont( f4l_check_font( L, 3 ) );
          return 1;
        } else if( F4L_MEMCMP( key, "textsize", 8 ) == 0 ) {
          c->textsize( moon_checkint( L, 3, 0, INT_MAX ) );
          return 1;
        }
        break;
      case 9:
        if( F4L_MEMCMP( key, "textcolor", 9 ) == 0 ) {
          c->textcolor( f4l_check_color( L, 3 ) );
          return 1;
        }
        break;
    }
    return 0;
  }

} // anonymous namespace


F4L_DEF_DELETE( Fl_Counter )


F4L_LUA_LLINKAGE_BEGIN

static int new_counter( lua_State* L ) {
  F4L_TRY( L ) {
    f4l_new_widget< Fl_Counter >( L, F4L_COUNTER_NAME,
                                  f4l_delete_Fl_Counter );
  } F4L_CATCH( L );
  return 1;
}


static int counter_index( lua_State* L ) {
  Fl_Counter* c = check_counter( L, 1 );
  size_t n = 0;
  char const* key = luaL_checklstring( L, 2, &n );
  F4L_TRY( L ) {
    if( !counter_index_( L, c, key, n ) &&
        !f4l_valuator_index_( L, c, key, n ) &&
        !f4l_widget_index_( L, c, key, n ) &&
        !f4l_bad_property( L, F4L_COUNTER_NAME, key ) )
      lua_pushnil( L );
  } F4L_CATCH( L );
  return 1;
}


static int counter_newindex( lua_State* L ) {
  Fl_Counter* c = check_counter( L, 1 );
  size_t n = 0;
  char const* key = luaL_checklstring( L, 2, &n );
  F4L_TRY( L ) {
    (void)(counter_newindex_( L, c, key, n ) ||
           f4l_valuator_newindex_( L, c, key, n ) ||
           f4l_widget_newindex_( L, c, key, n ) ||
           f4l_bad_property( L, F4L_COUNTER_NAME, key ));
  } F4L_CATCH( L );
  return 0;
}

F4L_LUA_LLINKAGE_END


F4L_DEF_CAST( Fl_Counter, Fl_Valuator )
F4L_DEF_CAST( Fl_Counter, Fl_Widget )


MOON_LOCAL void f4l_counter_setup( lua_State* L ) {
  luaL_Reg const methods[] = {
    F4L_WIDGET_METHODS,
    F4L_VALUATOR_METHODS,
    { "__index", counter_index },
    { "__newindex", counter_newindex },
    { NULL, NULL }
  };
  moon_defobject( L, F4L_COUNTER_NAME, 0, methods, 0 );
  moon_defcast( L, F4L_COUNTER_NAME, F4L_VALUATOR_NAME,
                f4l_cast_Fl_Counter_Fl_Valuator );
  moon_defcast( L, F4L_COUNTER_NAME, F4L_WIDGET_NAME,
                f4l_cast_Fl_Counter_Fl_Widget );
  f4l_new_class_table( L, "Counter", new_counter );
}

