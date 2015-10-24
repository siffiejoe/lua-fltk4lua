#include "fltk4lua.hxx"
#include "f4l_group.hxx"
#include "f4l_widget.hxx"
#include <FL/Fl_Wizard.H>


namespace {

  inline Fl_Wizard* check_wizard( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_WIZARD_NAME );
    return static_cast< Fl_Wizard* >( p );
  }

  inline Fl_Widget* check_widget( lua_State* L, int idx ) {
    void* p = moon_checkobject( L, idx, F4L_WIDGET_NAME );
    return static_cast< Fl_Widget* >( p );
  }


  int wizard_index_( lua_State* L, Fl_Wizard* w,
                     char const* key, size_t n ) {
    using namespace std;
    switch( n ) {
      case 5:
        if( F4L_MEMCMP( key, "value", 5 ) == 0 ) {
          f4l_push_widget( L, w->value() );
          return 1;
        }
        break;
    }
    return 0;
  }


  int wizard_newindex_( lua_State* L, Fl_Wizard* w,
                        char const* key, size_t n ) {
    using namespace std;
    switch( n ) {
      case 5:
        if( F4L_MEMCMP( key, "value", 5 ) == 0 ) {
          w->value( check_widget( L, 3 ) );
          return 1;
        }
        break;
    }
    return 0;
  }

} // anonymous namespace


F4L_DEF_DELETE( Fl_Wizard )


F4L_LUA_LLINKAGE_BEGIN

static int new_wizard( lua_State* L ) {
  F4L_TRY( L ) {
    f4l_new_widget< Fl_Wizard >( L, F4L_WIZARD_NAME,
                                 f4l_delete_Fl_Wizard );
  } F4L_CATCH( L );
  return 1;
}


static int wizard_index( lua_State* L ) {
  Fl_Wizard* w = check_wizard( L, 1 );
  size_t n = 0;
  char const* key = luaL_checklstring( L, 2, &n );
  F4L_TRY( L ) {
    if( !wizard_index_( L, w, key, n ) &&
        !f4l_group_index_( L, w, key, n ) &&
        !f4l_widget_index_( L, w, key, n ) &&
        !f4l_bad_property( L, F4L_WIZARD_NAME, key ) )
      lua_pushnil( L );
  } F4L_CATCH( L );
  return 1;
}


static int wizard_newindex( lua_State* L ) {
  Fl_Wizard* w = check_wizard( L, 1 );
  size_t n = 0;
  char const* key = luaL_checklstring( L, 2, &n );
  F4L_TRY( L ) {
    (void)(wizard_newindex_( L, w, key, n ) ||
           f4l_group_newindex_( L, w, key, n ) ||
           f4l_widget_newindex_( L, w, key, n ) ||
           f4l_bad_property( L, F4L_WIZARD_NAME, key ));
  } F4L_CATCH( L );
  return 0;
}


static int wizard_next( lua_State* L ) {
  Fl_Wizard* w = check_wizard( L, 1 );
  F4L_TRY( L ) {
    w->next();
  } F4L_CATCH( L );
  return 0;
}


static int wizard_prev( lua_State* L ) {
  Fl_Wizard* w = check_wizard( L, 1 );
  F4L_TRY( L ) {
    w->prev();
  } F4L_CATCH( L );
  return 0;
}

F4L_LUA_LLINKAGE_END


F4L_DEF_CAST( Fl_Wizard, Fl_Group )
F4L_DEF_CAST( Fl_Wizard, Fl_Widget )


MOON_LOCAL void f4l_wizard_setup( lua_State* L ) {
  luaL_Reg const methods[] = {
    F4L_WIDGET_METHODS,
    F4L_GROUP_METHODS,
    { "next", wizard_next },
    { "prev", wizard_prev },
    { "__index", wizard_index },
    { "__newindex", wizard_newindex },
    { NULL, NULL }
  };
  moon_defobject( L, F4L_WIZARD_NAME, 0, methods, 0 );
  moon_defcast( L, F4L_WIZARD_NAME, F4L_GROUP_NAME,
                f4l_cast_Fl_Wizard_Fl_Group );
  moon_defcast( L, F4L_WIZARD_NAME, F4L_WIDGET_NAME,
                f4l_cast_Fl_Wizard_Fl_Widget );
  f4l_new_class_table( L, "Wizard", new_wizard );
}

