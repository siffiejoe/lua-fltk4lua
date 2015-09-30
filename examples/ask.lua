#!/usr/bin/env lua

local fl = require( "fltk4lua" )
local window = fl.Window( 200, 105 )
function window:callback()
  local hotspot = fl.message_hotspot()
  fl.message_hotspot( false )
  local rep = fl.choice( "Are you sure you want to quit?",
                         "Cancel", "Quit", "Dunno" )
  fl.message_hotspot( hotspot )
  if rep == "Quit" then
    --os.exit( 0 ) -- bad style
    self:hide()
  elseif rep == "Dunno" then
    fl.message( "Well, maybe you should know before we quit." )
  end
end

local b = fl.Return_Button( 20, 10, 160, 35, "Test text" )
function b:callback()
  local input = fl.input( "Input:", self.label )
  if input then
    self.label = input
    self:redraw()
  end
end

local b2 = fl.Button( 20, 50, 160, 35, "MyPassword" )
function b2:callback()
  local input = fl.password( "Input PWD:", self.label )
  if input then
    self.label = input
    self:redraw()
  end
end

window:end_group()
--window.resizable = b -- looks bad on a tiling window manager
window:show( arg )

fl.run()

