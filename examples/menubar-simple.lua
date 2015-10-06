#!/usr/bin/env lua

local fl = require( "fltk4lua" )
local window = fl.Window( 400, 240 )
local menubar = fl.Menu_Bar( 0, 0, 400, 30 )
local box = fl.Box( 20, 55, 360, 120, "<no item>" )
box.box = "FL_UP_BOX"
box.labelfont = "FL_HELVETICA_BOLD_ITALIC"
box.labelsize = 36
box.labeltype = "FL_SHADOW_LABEL"
local b1 = fl.Button( 20, 185, 60, 30, "Add" )
local b2 = fl.Button( 320, 185, 60, 30, "Remove" )
window:end_group()

local function menu_cb( self, udata )
  box.label = udata
  box:redraw()
end

function b1:callback()
  print( menubar:add( "&Help/&About", fl.CTRL+"a", menu_cb, "help/about" ) )
  print( menubar:add( "&Help/&Help", 0, menu_cb, "help/help" ) )
  menubar:redraw()
end

function b2:callback()
  local i = menubar:find_index( "&Help" )
  if i then
    menubar:remove( i )
    menubar:redraw()
  end
end

local function quit_cb()
  window:hide()
end

print( menubar:add( "&File/&New", "^n", menu_cb, "file/new" ) )
print( menubar:add( "&File/&Save", "^s", menu_cb, "file/save" ) )
print( menubar:add( "&File/&Quit", "^q", quit_cb ) )
print( menubar:add( "&Edit/&Copy", fl.CTRL+"c", menu_cb, "edit/copy" ) )
print( menubar:add( "&Edit/&Paste", fl.CTRL+"v", menu_cb, "edit/paste" ) )

window:show( arg )
fl.run()

