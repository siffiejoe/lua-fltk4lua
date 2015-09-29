#          fltk4lua -- Lua Binding to the Fast Light ToolKit         #

##                           Introduction                           ##

[FLTK][1] is a small C++ GUI toolkit portable to the MS Windows,
Linux, and Mac OSX operating systems. **fltk4lua** is a binding to
this C++ toolkit, which allows you to create GUIs from within Lua
scripts.

  [1]:  http://www.fltk.org/


##                           Documentation                          ##

Unfortunately, there is no real documentation for **fltk4lua**, yet.
The Lua API is very close to the C++ API, so you can use the [official
FLTK documentation][2], and look at the examples or the source code.

  [2]:  http://www.fltk.org/doc-1.3/index.html

In general there are the following differences between Lua API and C++
API (assuming you did a `local fl = require( "fltk4lua" )` at the top
of your Lua source file):

*   The prefixes of classes and functions have been removed, so use
    *   `fl.message()` instead of `fl_message()`
    *   `fl.run()` instead of `Fl::run()`
    *   `fl.Box()` instead of `new Fl_Box()`
    *   `fl.ALIGN_CENTER` instead of `FL_ALIGN_CENTER` (but see below).
*   Some `enum`s or preprocessor macros are translated to strings:
    *   `"FL_UP_BOX"` instead of `FL_UP_BOX`.
*   The remaining `enum`s/macros are available as userdata, so that
    you can combine them using bitwise operators (in Lua 5.3) or the
    following alternative operators:
    *   `local a = fl.ALIGN_TOP + fl.ALIGN_LEFT` instead of `Fl_Align
        a = FL_ALIGN_TOP | FL_ALIGN_LEFT;`
    *   `local a = b - fl.ALIGN_LEFT` instead of `Fl_Align a = b &
        (~FL_ALIGN_LEFT);` and
    *   `if a( fl.ALIGN_TOP ) then` instead of `if( a & FL_ALIGN_TOP )`.
*   C++ method calls are translated to Lua properties whenever
    possible, so use
    *   `b.box = "FL_UP_BOX"` instead of `b->box( FL_UP_BOX );` and
    *   `local bt = b.box` instead of `Fl_Boxtype bt = b->box();`.
*   Integers used as boolean values are translated to real `boolean`s.
*   `nil` is translated to `NULL` if `NULL` is allowed (and vice
    versa).
*   Output parameters end up as (multiple) return values.
*   The menu interface is a bit different, though, as it is completely
    index based, and the Fl_Menu_Items are not exposed as userdata.
    Instead there are extra methods on the widget that contains the
    menu items.

Here is a list of userdata types and their functions/properties. Lua
types are abbreviated as:  `nil=n`, `boolean=b`, `integer=i`,
`number=d` (think `double`), `string=s`, `function=f`, `userdata=u`,
`coroutine=c`, `table=t`, `any (non-nil)=a`. Alternative types are
concatenated together, so e.g.  `nu` means `nil` or `userdata`.
Parameters at the end of the parameter list which also accept `nil`
can be left out as usual (optional parameters). Boolean parameters
accept any Lua value that is interpreted as true-ish/false-y as usual,
so a boolean parameter at the end of the parameter list is optional as
well. Methods (of the same name) always take precedence over
properties, and methods/properties defined on the sub-class take
precedence over inherited ones.

`Image` (abstract):
*   `obj:color_average( iu, d )`
*   `obj:desaturate()`
*   `obj:inactive()`
*   `obj:uncache()`
*   `obj.d  [get: i; set: -]`
*   `obj.h  [get: i; set: -]`
*   `obj.w  [get: i; set: -]`

`Shared_Image`:
*   `fl.Shared_Image.get( s, ni, ni ) ==> u`
*   `fl.Shared_Image.find( s, ni, ni ) ==> u`
*   `obj:copy( i, i ) ==> u`
*   `obj:reload()`
*   methods defined for the `Image` userdata type
*   `obj.name  [get: s; set: -]`
*   properties defined for the `Image` userdata type

`Widget` (abstract):
*   `obj:activate()`
*   `obj:clear_changed()`
*   `obj:clear_damage()`
*   `obj:clear_output()`
*   `obj:clear_visible()`
*   `obj:clear_visible_focus()`
*   `obj:contains( u ) ==> b`
*   `obj:deactivate()`
*   `obj:hide()`
*   `obj:inside( nu ) ==> b`
*   `obj:measure_label() ==> i, i`
*   `obj:position( i, i )`
*   `obj:redraw()`
*   `obj:redraw_label()`
*   `obj:resize( i, i, i, i )`
*   `obj:set_changed()`
*   `obj:set_output()`
*   `obj:set_visible()`
*   `obj:set_visible_focus()`
*   `obj:show()`
*   `obj:size( i, i )`
*   `obj:take_focus() ==> b`
*   `obj.x  [get: i; set: -]`
*   `obj.y  [get: i; set: -]`
*   `obj.w  [get: i; set: -]`
*   `obj.h  [get: i; set: -]`
*   `obj.box  [get: s; set: s]`
*   `obj.when  [get: u; set: u]`
*   `obj.align  [get: u; set: su]`
*   `obj.color  [get: u; set: iu]`
*   `obj.image  [get: nu; set: u]`
*   `obj.label  [get: s; set: s]`
*   `obj.active  [get: b; set: -]`
*   `obj.output  [get: b; set: -]`
*   `obj.parent  [get: u; set: -]`
*   `obj.changed  [get: b; set: -]`
*   `obj.deimage  [get: nu; set: u]`
*   `obj.tooltip  [get: s; set: s]`
*   `obj.visible  [get: b; set: -]`
*   `obj.active_r  [get: b; set: -]`
*   `obj.callback  [get: nf; set: nf]`
*   `obj.labelfont  [get: s; set: is]`
*   `obj.labelsize  [get: i; set: i]`
*   `obj.labeltype  [get: s; set: s]`
*   `obj.user_data  [get: na; set: na]`
*   `obj.visible_r  [get: b; set: -]`
*   `obj.labelcolor  [get: u; set: iu]`
*   `obj.takesevents  [get: b; set: -]`
*   `obj.visible_focus  [get: b; set: b]`
*   `obj.selection_color  [get: u; set: iu]`

`Box`:
*   `fl.Box( i, i, i, i, ns ) ==> u`
*   `fl.Box( t ) ==> u` (table constructor syntax)
*   methods defined for the `Widget` userdata type
*   properties defined for the `Widget` userdata type

`Button`:
*   `fl.Button( i, i, i, i, ns ) ==> u`
*   `fl.Button( t ) ==> u` (table constructor syntax)
*   `obj:clear() ==> b`
*   `obj:set() ==> b`
*   `obj:setonly()`
*   methods defined for the `Widget` userdata type
*   `obj.type  [get: s; set: s]`
*   `obj.value  [get: b; set: b]`
*   `obj.down_box  [get: s; set: s]`
*   `obj.shortcut  [get: u; set: isu]`
*   `obj.down_color  [get: u; set: iu]`
*   properties defined for the `Widget` userdata type

`Light_Button`:
*   `fl.Light_Button( i, i, i, i, ns ) ==> u`
*   `fl.Light_Button( t ) ==> u` (table constructor syntax)
*   methods defined for the `Box` userdata type
*   methods defined for the `Widget` userdata type
*   properties defined for the `Box` userdata type
*   properties defined for the `Widget` userdata type

`Check_Button`:
*   `fl.Check_Button( i, i, i, i, ns ) ==> u`
*   `fl.Check_Button( t ) ==> u` (table constructor syntax)
*   methods defined for the `Box` userdata type
*   methods defined for the `Widget` userdata type
*   properties defined for the `Box` userdata type
*   properties defined for the `Widget` userdata type

`Repeat_Button`:
*   `fl.Repeat_Button( i, i, i, i, ns ) ==> u`
*   `fl.Repeat_Button( t ) ==> u` (table constructor syntax)
*   `obj:deactivate()`
*   methods defined for the `Box` userdata type
*   methods defined for the `Widget` userdata type
*   properties defined for the `Box` userdata type
*   properties defined for the `Widget` userdata type

`Return_Button`:
*   `fl.Return_Button( i, i, i, i, ns ) ==> u`
*   `fl.Return_Button( t ) ==> u` (table constructor syntax)
*   methods defined for the `Box` userdata type
*   methods defined for the `Widget` userdata type
*   properties defined for the `Box` userdata type
*   properties defined for the `Widget` userdata type

`Round_Button`:
*   `fl.Round_Button( i, i, i, i, ns ) ==> u`
*   `fl.Round_Button( t ) ==> u` (table constructor syntax)
*   methods defined for the `Box` userdata type
*   methods defined for the `Widget` userdata type
*   properties defined for the `Box` userdata type
*   properties defined for the `Widget` userdata type

`Chart`:
*   `fl.Chart( i, i, i, i, ns ) ==> u`
*   `fl.Chart( t ) ==> u` (table constructor syntax)
*   `obj:add( d, ns, niu )`
*   `obj:bounds() ==> d, d`
*   `obj:bounds( d, d )`
*   `obj:clear()`
*   `obj:insert( i, d, ns, niu )`
*   `obj:replace( i, d, ns, niu )`
*   `obj:size( i, i )`
*   methods defined for the `Widget` userdata type
*   `obj.type  [get: s; set: s]`
*   `obj.maxsize  [get: i; set: i]`
*   `obj.autosize  [get: b; set: b]`
*   `obj.textsize  [get: i; set: i]`
*   `obj.textcolor  [get: u; set: iu]`
*   `obj.chart_size  [get: i; set: -]` (corresponds to
    `Fl_Chart::size()`)
*   properties defined for the `Widget` userdata type

`Clock_Output`:
*   `fl.Clock_Output( i, i, i, i, ns ) ==> u`
*   `fl.Clock_Output( t ) ==> u` (table constructor syntax)
*   `obj:setvalue( i, i, i )` (corresponds to
    `Fl_Clock_Output::value(int, int, int)`)
*   methods defined for the `Widget` userdata type
*   `obj.hour  [get: i; set: -]`
*   `obj.type  [get: s; set: s]`
*   `obj.value  [get: id; set: id]` (type depends on size of
    `lua_Integer`)
*   `obj.minute  [get: i; set: -]`
*   `obj.second  [get: i; set: -]`
*   properties defined for the `Widget` userdata type

`Clock`:
*   `fl.Clock( i, i, i, i, ns ) ==> u`
*   `fl.Clock( t ) ==> u` (table constructor syntax)
*   methods defined for the `Clock_Output` userdata type
*   methods defined for the `Widget` userdata type
*   properties defined for the `Clock_Output` userdata type
*   properties defined for the `Widget` userdata type

`Group`:
*   `fl.Group( i, i, i, i, ns ) ==> u`
*   `fl.Group( t ) ==> u` (table constructor syntax)
*   `obj:add( u )`
*   `obj:add_resizable( u )`
*   `obj:begin()`
*   `obj:child( i ) ==> u`
*   `obj:clear()`
*   `obj:end_group()` (corresponds to `Fl_Group::end()`)
*   `obj:find( u ) ==> i`
*   `obj:insert( u, i )`
*   `obj:remove( i )`
*   methods defined for the `Widget` userdata type
*   `obj.children  [get: i; set: -]`
*   `obj.resizable  [get: nu; set: nu]`
*   `obj.clip_children  [get: b; set: b]`
*   properties defined for the `Widget` userdata type

`Browser_` (abstract):
*   `obj:deselect( b ) ==> b`
*   `obj:scrollbar_left()`
*   `obj:scrollbar_right()`
*   `obj:sort( ns )`
*   `obj.textfont  [get: s; set: is]`
*   `obj.textsize  [get: i; set: i]`
*   `obj.textcolor  [get: u; set: iu]`
*   `obj.hposition  [get: i; set: i]`
*   `obj.vposition  [get: i; set: i]` (corresponds to
    `Fl_Browser_::position()`)
*   `obj.has_scrollbar  [get: s; set: s]`
*   `obj.scrollbar_size  [get: i; set: i]`
*   `obj.scrollbar_width  [get: i; set: i]`

`Browser`:
*   `fl.Browser( i, i, i, i, ns ) ==> u`
*   `fl.Browser( t ) ==> u` (table constructor syntax)
*   `obj:add( ns )`
*   `obj:clear()`
*   `obj:displayed( i ) ==> b`
*   `obj:hide( ni )`
*   `obj:insert( i, ns )`
*   `obj:load( s ) ==> b / (n, s, i)`
*   `obj:make_visible( i )`
*   `obj:move( i, i )`
*   `obj:remove( i )`
*   `obj:select( i ) ==> b`
*   `obj:selected( i ) ==> b`
*   `obj:show( ni )`
*   `obj:size( i, i )`
*   `obj:swap( i, i )`
*   `obj:text( i ) ==> ns`
*   `obj:text( i, s )`
*   `obj:visible( i ) ==> b`
*   methods defined for the `Browser_` userdata type
*   methods defined for the `Widget` userdata type
*   `obj.type  [get: s; set: s]`
*   `obj.value  [get: i; set: i]`
*   `obj.nitems  [get: i; set: -]` (corresponds to
    `Fl_Browser::size()`)
*   `obj.topline  [get: i; set: i]`
*   `obj.bottomline  [get: -; set: i]`
*   `obj.middleline  [get: -; set: i]`
*   `obj.column_char  [get: s; set: -]`
*   `obj.format_char  [get: s; set: -]`
*   `obj.column_widths  [get: t; set: t]`
*   properties defined for the `Browser_` userdata type
*   properties defined for the `Widget` userdata type
*   (note: `Browser` does not inherit the methods and properties of
    `Group`, although `Fl_Browser` is implemented as a sub-class of
    `Fl_Group`!)

`File_Browser`:
*   `fl.File_Browser( i, i, i, i, ns ) ==> u`
*   `fl.File_Browser( t ) ==> u` (table constructor syntax)
*   `obj:load( s, s ) ==> b / (n, s, i)`
*   methods defined for the `Browser` userdata type
*   methods defined for the `Browser_` userdata type
*   methods defined for the `Widget` userdata type
*   `obj.filter  [get: s; set: s]`
*   `obj.filetype  [get: s; set: s]`
*   `obj.iconsize  [get: i; set: i]`
*   `obj.textsize  [get: i; set: i]`
*   properties defined for the `Browser` userdata type
*   properties defined for the `Browser_` userdata type
*   properties defined for the `Widget` userdata type
*   (note: `File_Browser` does not inherit the methods and properties
    of `Group`, although `Fl_File_Browser` is implemented as a
    sub-class of `Fl_Group`!)

`Check_Browser`:
*   `fl.Check_Browser( i, i, i, i, ns ) ==> u`
*   `fl.Check_Browser( t ) ==> u` (table constructor syntax)
*   `obj:add( ns, b )`
*   `obj:check_all()`
*   `obj:check_none()`
*   `obj:checked( i ) ==> b`
*   `obj:checked( i, b )`
*   `obj:clear()`
*   `obj:remove( i ) ==> i`
*   `obj:set_checked( i )`
*   `obj:text( i ) ==> ns`
*   methods defined for the `Browser_` userdata type
*   methods defined for the `Widget` userdata type
*   `obj.value  [get: i; set: -]`
*   `obj.nitems  [get: i; set: -]`
*   `obj.nchecked  [get: i; set: -]`
*   properties defined for the `Browser_` userdata type
*   properties defined for the `Widget` userdata type
*   (note: `Check_Browser` does not inherit the methods and properties
    of `Group`, although `Fl_Check_Browser` is implemented as a
    sub-class of `Fl_Group`!)

`Color_Chooser`:
*   `fl.Color_Chooser( i, i, i, i, ns ) ==> u`
*   `fl.Color_Chooser( t ) ==> u` (table constructor syntax)
*   `obj:rgb( d, d, d ) ==> b`
*   `obj:hsv( d, d, d ) ==> b`
*   methods defined for the `Widget` userdata type
*   `obj.r  [get: d; set: -]`
*   `obj.g  [get: d; set: -]`
*   `obj.b  [get: d; set: -]`
*   `obj.hue  [get: d; set: -]`
*   `obj.mode  [get: i; set: i]`
*   `obj.value  [get: d; set: -]`
*   `obj.saturation  [get: d; set: -]`
*   properties defined for the `Widget` userdata type
*   (note: `Color_Chooser` does not inherit the methods and properties
    of `Group`, although `Fl_Color_Chooser` is implemented as a
    sub-class of `Fl_Group`!)

`Input_Choice`:
*   `fl.Input_Choice( i, i, i, i, ns ) ==> u`
*   `fl.Input_Choice( t ) ==> u` (table constructor syntax)
*   `obj:add( s )`
*   `obj:clear()`
*   `obj:clear_changed()`
*   `obj:set_changed()`
*   methods defined for the `Widget` userdata type
*   `obj.input  [get: u; set: -]`
*   `obj.value  [get: ns; set: nis]`
*   `obj.changed  [get: b; set: -]`
*   `obj.down_box  [get: s; set: s]`
*   `obj.textfont  [get: s; set: is]`
*   `obj.textsize  [get: i; set: i]`
*   `obj.textcolor  [get: u; set: iu]`
*   `obj.menubutton  [get: u; set: -]`
*   properties defined for the `Widget` userdata type
*   (note: `Input_Choice` does not inherit the methods and properties
    of `Group`, although `Fl_Input_Choice` is implemented as a
    sub-class of `Fl_Group`!)

`Pack`:
*   `fl.Pack( i, i, i, i, ns ) ==> u`
*   `fl.Pack( t ) ==> u` (table constructor syntax)
*   methods defined for the `Group` userdata type
*   methods defined for the `Widget` userdata type
*   `obj.type  [get: s; set: s]`
*   `obj.spacing  [get: i; set: i]`
*   `obj.horizontal  [get: b; set: -]`
*   properties defined for the `Group` userdata type
*   properties defined for the `Widget` userdata type

`Scroll`:
*   `fl.Scroll( i, i, i, i, ns ) ==> u`
*   `fl.Scroll( t ) ==> u` (table constructor syntax)
*   `obj:clear()`
*   `obj:scroll_to( i, i )`
*   methods defined for the `Group` userdata type
*   methods defined for the `Widget` userdata type
*   `obj.type  [get: s; set: s]`
*   `obj.scrollbar  [get: u; set: -]`
*   `obj.xposition  [get: i; set: -]`
*   `obj.yposition  [get: i; set: -]`
*   `obj.hscrollbar  [get: u; set: -]`
*   `obj.scrollbar_size  [get: i; set: i]`
*   properties defined for the `Group` userdata type
*   properties defined for the `Widget` userdata type

`Spinner`:
*   `fl.Spinner( i, i, i, i, ns ) ==> u`
*   `fl.Spinner( t ) ==> u` (table constructor syntax)
*   `obj:range( d, d )`
*   methods defined for the `Widget` userdata type
*   `obj.step  [get: d; set: d]`
*   `obj.type  [get: s; set: s]`
*   `obj.color  [get: u; set: iu]`
*   `obj.value  [get: d; set: d]`
*   `obj.format  [get: s; set: s]`
*   `obj.maximum  [get: d; set: d]`
*   `obj.minimum  [get: d; set: d]`
*   `obj.textfont  [get: s; set: is]`
*   `obj.textsize  [get: i; set: i]`
*   `obj.textcolor  [get: u; set: iu]`
*   properties defined for the `Widget` userdata type
*   (note: `Spinner` does not inherit the methods and properties of
    `Group`, although `Fl_Spinner` is implemented as a sub-class of
    `Fl_Group`!)


`Tabs`:
*   `fl.Tabs( i, i, i, i, ns ) ==> u`
*   `fl.Tabs( t ) ==> u` (table constructor syntax)
*   `obj:client_area( ni ) ==> i, i, i, i`
*   methods defined for the `Group` userdata type
*   methods defined for the `Widget` userdata type
*   `obj.push  [get: u; set: u]`
*   `obj.value  [get: u; set: u]`
*   properties defined for the `Group` userdata type
*   properties defined for the `Widget` userdata type

`Tile`:
*   `fl.Tile( i, i, i, i, ns ) ==> u`
*   `fl.Tile( t ) ==> u` (table constructor syntax)
*   `obj:position( i, i, i, i )`
*   methods defined for the `Group` userdata type
*   methods defined for the `Widget` userdata type
*   properties defined for the `Group` userdata type
*   properties defined for the `Widget` userdata type

`Window`:
*   `fl.Window( i, i, i, i, ns ) ==> u`
*   `fl.Window( i, i, ns ) ==> u`
*   `fl.Window( t ) ==> u` (table constructor syntax)
*   `obj:clear_border()`
*   `obj:cursor( s, niu, niu )`
*   `obj:default_cursor( s, niu, niu )`
*   `obj:fullscreen()`
*   `obj:fullscreen_off( [i, i, i, i] )`
*   `obj:iconize()`
*   `obj:make_current()`
*   `obj:set_modal()`
*   `obj:set_non_modal()`
*   `obj:set_override()`
*   `obj:show( nt )`
*   `obj:size_range( i, i, ni, ni, ni, ni, b )`
*   methods defined for the `Group` userdata type
*   methods defined for the `Widget` userdata type
*   `label  [get: s; set: s]`
*   `modal  [get: b; set: b]`
*   `shown  [get: b; set: -]`
*   `border  [get: b; set: -]`
*   `x_root  [get: i; set: -]`
*   `y_root  [get: i; set: -]`
*   `xclass  [get: s; set: s]`
*   `override  [get: b; set: -]`
*   `iconlabel  [get: s; set: s]`
*   `non_modal  [get: b; set: -]`
*   `decorated_h  [get: i; set: -]`
*   `decorated_w  [get: i; set: -]`
*   `menu_window  [get: b; set: -]`
*   `tooltip_window  [get: b; set: -]`
*   `fullscreen_active  [get: b; set: -]`
*   properties defined for the `Group` userdata type
*   properties defined for the `Widget` userdata type

`Wizard`:
*   `fl.Wizard( i, i, i, i, ns ) ==> u`
*   `fl.Wizard( t ) ==> u` (table constructor syntax)
*   `obj:next()`
*   `obj:prev()`
*   methods defined for the `Group` userdata type
*   methods defined for the `Widget` userdata type
*   `obj.value  [get: u; set: u]`
*   properties defined for the `Group` userdata type
*   properties defined for the `Widget` userdata type

`Input`:
*   `fl.Input( i, i, i, i, ns ) ==> u`
*   `fl.Input( t ) ==> u` (table constructor syntax)
*   `obj:copy( i ) ==> b`
*   `obj:copy_cuts() ==> b`
*   `obj:cut( [i [, i]] ) ==> b`
*   `obj:index( i ) ==> i`
*   `obj:insert( s ) ==> b`
*   `obj:replace( i, i, ns ) ==> b`
*   `obj:size( i, i )`
*   `obj:undo()`
*   methods defined for the `Widget` userdata type
*   `obj.mark  [get: i; set: i]`
*   `obj.type  [get: s; set: s]`
*   `obj.wrap  [get: b; set: b]`
*   `obj.value  [get: s; set: s]`
*   `obj.tab_nav  [get: -; set: b]`
*   `obj.position  [get: i; set: i]`
*   `obj.readonly  [get: b; set: b]`
*   `obj.shortcut  [get: u; set: isu]`
*   `obj.textfont  [get: s; set: is]`
*   `obj.textsize  [get: i; set: i]`
*   `obj.textcolor  [get: u; set: iu]`
*   `obj.value_size  [get: i; set: -]` (corresponds to
    `Fl_Input_::size()`)
*   `obj.cursor_color  [get: u; set: iu]`
*   `obj.maximum_size  [get: i; set: i]`
*   properties defined for the `Widget` userdata type


`File_Input`:
*   `fl.File_Input( i, i, i, i, ns ) ==> u`
*   `fl.File_Input( t ) ==> u` (table constructor syntax)
*   methods defined for the `Input` userdata type
*   methods defined for the `Widget` userdata type
*   `obj.value  [get: s; set: s]`
*   `obj.down_box  [get: s; set: s]`
*   `obj.errorcolor  [get: u; set: iu]`
*   properties defined for the `Input` userdata type
*   properties defined for the `Widget` userdata type

`Menu` (abstract, represents `Fl_Menu_`):
*   `obj:add( s, nisu, nf, na, nu ) ==> i`
*   `obj:clear()`
*   `obj:clear_submenu( i ) ==> nb`
*   `obj:find_index( s ) ==> ni`
*   `obj:insert( i, s, nisu, nf, na, nu ) ==> i`
*   `obj:remove( i )`
*   `obj:size( i, i )`
*   `obj:menuitem_getp( i, s ) ==> ?` gets a property value for the
    menu element identified by the given index.
    -   `"text" ==> ns`
    -   `"flags" ==> u`
    -   `"label" ==> ns`
    -   `"callback" ==> nf`
    -   `"shortcut" ==> u`
    -   `"labelfont" ==> s`
    -   `"labelsize" ==> i`
    -   `"labeltype" ==> s`
    -   `"user_data" ==> na`
    -   `"labelcolor" ==> u`
*   `obj:menuitem_setp( i, s, ? )`
    -   `"text": s`
    -   `"flags": u`
    -   `"label": s`
    -   `"callback": nf`
    -   `"shortcut": isu`
    -   `"labelfont": is`
    -   `"labelsize": i`
    -   `"user_data": na`
    -   `"labelcolor": iu`
*   `obj:menuitem_activate( i )`
*   `obj:menuitem_active( i ) ==> b`
*   `obj:menuitem_activevisible( i ) ==> b`
*   `obj:menuitem_checkbox( i ) ==> b`
*   `obj:menuitem_clear( i )`
*   `obj:menuitem_deactivate( i )`
*   `obj:menuitem_hide( i )`
*   `obj:menuitem_radio( i ) ==> b`
*   `obj:menuitem_set( i )`
*   `obj:menuitem_setonly( i )`
*   `obj:menuitem_show( i )`
*   `obj:menuitem_submenu( i ) ==> b`
*   `obj:menuitem_value( i ) ==> b`
*   `obj:menuitem_visible( i ) ==> b`
*   `obj.value  [get: i; set: i]`
*   `obj.down_box  [get: s; set: s]`
*   `obj.textfont  [get: s; set: is]`
*   `obj.textsize  [get: i; set: i]`
*   `obj.menu_size  [get: i; set: -]`
*   `obj.textcolor  [get: u; set: iu]`

`Choice`:
*   `fl.Choice( i, i, i, i, ns ) ==> u`
*   `fl.Choice( t ) ==> u` (table constructor syntax)
*   methods defined for the `Menu` userdata type
*   methods defined for the `Widget` userdata type
*   `obj.value  [get: i; set: i]`
*   properties defined for the `Menu` userdata type
*   properties defined for the `Widget` userdata type

`Menu_Bar`:
*   `fl.Menu_Bar( i, i, i, i, ns ) ==> u`
*   `fl.Menu_Bar( t ) ==> u` (table constructor syntax)
*   methods defined for the `Menu` userdata type
*   methods defined for the `Widget` userdata type
*   properties defined for the `Menu` userdata type
*   properties defined for the `Widget` userdata type

`Menu_Button`:
*   `fl.Menu_Button( i, i, i, i, ns ) ==> u`
*   `fl.Menu_Button( t ) ==> u` (table constructor syntax)
*   methods defined for the `Menu` userdata type
*   methods defined for the `Widget` userdata type
*   `obj.type  [get: s; set: s]`
*   properties defined for the `Menu` userdata type
*   properties defined for the `Widget` userdata type

`Progress`:
*   `fl.Progress( i, i, i, i, ns ) ==> u`
*   `fl.Progress( t ) ==> u` (table constructor syntax)
*   methods defined for the `Widget` userdata type
*   `obj.value  [get: d; set: d]`
*   `obj.maximum  [get: d; set: d]`
*   `obj.minimum  [get: d; set: d]`
*   properties defined for the `Widget` userdata type

`Valuator` (abstract):
*   `obj:bounds( d, d )`
*   `obj:clamp( d ) ==> d`
*   `obj:format() ==> s`
*   `obj:increment( d, i ) ==> d`
*   `obj:range( d, d )`
*   `obj:round( d ) ==> d`
*   `obj.step  [get: d; set: d]`
*   `obj.value  [get: d; set: d]`
*   `obj.maximum  [get: d; set: d]`
*   `obj.minimum  [get: d; set: d]`
*   `obj.precision  [get: -; set: i]`

`Adjuster`:
*   `fl.Adjuster( i, i, i, i, ns ) ==> u`
*   `fl.Adjuster( t ) ==> u` (table constructor syntax)
*   methods defined for the `Valuator` userdata type
*   methods defined for the `Widget` userdata type
*   `obj.soft  [get: b; set: b]`
*   properties defined for the `Valuator` userdata type
*   properties defined for the `Widget` userdata type

`Counter`:
*   `fl.Counter( i, i, i, i, ns ) ==> u`
*   `fl.Counter( t ) ==> u` (table constructor syntax)
*   methods defined for the `Valuator` userdata type
*   methods defined for the `Widget` userdata type
*   `obj.step  [get: d; set: d]`
*   `obj.type  [get: s; set: s]`
*   `obj.lstep  [get: -; set: d]`
*   `obj.textfont  [get: s; set: is]`
*   `obj.textsize  [get: i; set: i]`
*   `obj.textcolor  [get: u; set: iu]`
*   properties defined for the `Valuator` userdata type
*   properties defined for the `Widget` userdata type

`Dial`:
*   `fl.Dial( i, i, i, i, ns ) ==> u`
*   `fl.Dial( t ) ==> u` (table constructor syntax)
*   `obj:angles( i, i )`
*   methods defined for the `Valuator` userdata type
*   methods defined for the `Widget` userdata type
*   `obj.type  [get: s; set: s]`
*   `obj.angle1  [get: i; set: i]`
*   `obj.angle2  [get: i; set: i]`
*   properties defined for the `Valuator` userdata type
*   properties defined for the `Widget` userdata type

`Roller`:
*   `fl.Roller( i, i, i, i, ns ) ==> u`
*   `fl.Roller( t ) ==> u` (table constructor syntax)
*   methods defined for the `Valuator` userdata type
*   methods defined for the `Widget` userdata type
*   properties defined for the `Valuator` userdata type
*   properties defined for the `Widget` userdata type

`Slider`:
*   `fl.Slider( i, i, i, i, ns ) ==> u`
*   `fl.Slider( t ) ==> u` (table constructor syntax)
*   `obj:bounds( d, d )`
*   `obj:scrollvalue( i, i, i, i ) ==> i`
*   methods defined for the `Valuator` userdata type
*   methods defined for the `Widget` userdata type
*   `obj.type  [get: s; set: s]`
*   `obj.slider  [get: s; set: s]`
*   `obj.slider_size  [get: d; set: d]`
*   properties defined for the `Valuator` userdata type
*   properties defined for the `Widget` userdata type

`Scrollbar`:
*   `fl.Scrollbar( i, i, i, i, ns ) ==> u`
*   `fl.Scrollbar( t ) ==> u` (table constructor syntax)
*   `obj:setvalue( i, i, i, i )` (corresponds to
    `Fl_Scrollbar::value(int, int, int, int)`)
*   methods defined for the `Slider` userdata type
*   methods defined for the `Valuator` userdata type
*   methods defined for the `Widget` userdata type
*   `obj.value  [get: i; set: i]`
*   `obj.linesize  [get: i; set: i]`
*   properties defined for the `Slider` userdata type
*   properties defined for the `Valuator` userdata type
*   properties defined for the `Widget` userdata type

`Value_Slider`:
*   `fl.Value_Slider( i, i, i, i, ns ) ==> u`
*   `fl.Value_Slider( t ) ==> u` (table constructor syntax)
*   methods defined for the `Slider` userdata type
*   methods defined for the `Valuator` userdata type
*   methods defined for the `Widget` userdata type
*   `obj.textfont  [get: s; set: is]`
*   `obj.textsize  [get: i; set: i]`
*   `obj.textcolor  [get: u; set: iu]`
*   properties defined for the `Slider` userdata type
*   properties defined for the `Valuator` userdata type
*   properties defined for the `Widget` userdata type

`Value_Input`:
*   `fl.Value_Input( i, i, i, i, ns ) ==> u`
*   `fl.Value_Input( t ) ==> u` (table constructor syntax)
*   methods defined for the `Valuator` userdata type
*   methods defined for the `Widget` userdata type
*   `obj.soft  [get: b; set: b]`
*   `obj.input  [get: u; set: -]`
*   `obj.shortcut  [get: u; set: isu]`
*   `obj.textfont  [get: s; set: is]`
*   `obj.textsize  [get: i; set: i]`
*   `obj.textcolor  [get: u; set: iu]`
*   `obj.cursor_color  [get: u; set: iu]`
*   properties defined for the `Valuator` userdata type
*   properties defined for the `Widget` userdata type

`Value_Output`:
*   `fl.Value_Output( i, i, i, i, ns ) ==> u`
*   `fl.Value_Output( t ) ==> u` (table constructor syntax)
*   methods defined for the `Valuator` userdata type
*   methods defined for the `Widget` userdata type
*   `obj.soft  [get: b; set: b]`
*   `obj.textfont  [get: s; set: is]`
*   `obj.textsize  [get: i; set: i]`
*   `obj.textcolor  [get: u; set: iu]`
*   properties defined for the `Valuator` userdata type
*   properties defined for the `Widget` userdata type

additional global functions:
*   `fl.run() ==> i`
*   `fl.wait( nd ) ==> b`
*   `fl.check() ==> b`
*   `fl.args( t )`
*   `fl.get_system_colors()`
*   `fl.inactive( iu ) ==> u`
*   `fl.contrast( iu, iu ) ==> u`
*   `fl.color_average( iu, iu ) ==> u`
*   `fl.lighter( iu ) ==> u`
*   `fl.darger( iu ) == u`
*   `fl.rgb_color( i [, i, i] ) ==> u`
*   `fl.alert( s )`
*   `fl.beep( ns )`
*   `fl.choice( s, ns, ns, ns ) ==> ns`
*   `fl.color_chooser( s, ni ) ==> nu`
*   `fl.dir_chooser( s, s, b ) == ns`
*   `fl.file_chooser( s, s, s, b ) ==> ns`
*   `fl.input( s, ns ) ==> ns`
*   `fl.message( s )`
*   `fl.password( s, ns ) ==> ns`


##                              Contact                             ##

Philipp Janda, siffiejoe(a)gmx.net

Comments and feedback are always welcome.


##                              License                             ##

`fltk4lua` is *copyrighted free software* distributed under the MIT
license (the same license as Lua 5.1). The full license text follows:

    fltk4lua (c) 2015 Philipp Janda

    Permission is hereby granted, free of charge, to any person obtaining
    a copy of this software and associated documentation files (the
    "Software"), to deal in the Software without restriction, including
    without limitation the rights to use, copy, modify, merge, publish,
    distribute, sublicense, and/or sell copies of the Software, and to
    permit persons to whom the Software is furnished to do so, subject to
    the following conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHOR OR COPYRIGHT HOLDER BE LIABLE FOR ANY
    CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
    SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

