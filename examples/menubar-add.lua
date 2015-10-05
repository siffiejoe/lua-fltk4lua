#!/usr/bin/env lua

local fl = require( "fltk4lua" )
fl.scheme( "gtk+" )
local win = fl.Window( 400, 200, "menubar-add" )
local menu = fl.Menu_Bar( 0, 0, 400, 25 )

local function menu_cb( bar )
  local item = bar.value
  local label = bar:menuitem_getp( item, "label" )
  local flags = bar:menuitem_getp( item, "flags" )
  io.write( ("callback: You picked '%s'"):format( label ) )
  if flags( fl.MENU_RADIO ) or flags( fl.MENU_TOGGLE ) then
    io.write( ", value is ", bar:menuitem_value( item ) and "on" or "off" )
  end
  io.write( "\n" )
  if label == "Google" then
    fl.open_uri( "http://google.com/" )
  elseif label == "&Quit" then
    --os.exit( 0, true ) -- bad style
    win:hide()
  end
end

menu:add( "&File/&Open",  "^o", menu_cb )
menu:add( "&File/&Save",  "^s", menu_cb, nil, fl.MENU_DIVIDER )
menu:add( "&File/&Quit",  "^q", menu_cb )
menu:add( "&Edit/&Copy",  "^c", menu_cb )
menu:add( "&Edit/&Paste", "^v", menu_cb, nil, fl.MENU_DIVIDER )
menu:add( "&Edit/Radio 1",   0, menu_cb, nil, fl.MENU_RADIO )
menu:add( "&Edit/Radio 2",   0, menu_cb, nil, fl.MENU_RADIO+fl.MENU_DIVIDER )
menu:add( "&Edit/Toggle 1",  0, menu_cb, nil, fl.MENU_TOGGLE )
menu:add( "&Edit/Toggle 2",  0, menu_cb, nil, fl.MENU_TOGGLE )
menu:add( "&Edit/Toggle 3",  0, menu_cb, nil, fl.MENU_TOGGLE+fl.MENU_VALUE )
menu:add( "&Help/Google",    0, menu_cb )

do
  local i = menu:find_index( "&Edit/Toggle 2" )
  if i then
    menu:menuitem_set( i )
  else
    io.write( "'Toggle 2' item not found?!\n" )
  end
end

win:end_group()
win:show()
fl.run()

