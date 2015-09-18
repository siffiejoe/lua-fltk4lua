#!/usr/bin/env lua

local fl = require( "fltk4lua" )
local window = fl.Window( 320, 100, arg[ 0 ] )
local b1 = fl.Box( 20, 30, 80, 25 )
b1.box = "FL_DOWN_BOX"
b1.color = fl.WHITE
local a1 = fl.Adjuster( 20+80, 30, 3*25, 25 )
function a1:callback()
  b1.label = self:format()
  b1:redraw()
end
a1:callback()

local b2 = fl.Box( 20+80+4*25, 30, 80, 25 )
b2.box = "FL_DOWN_BOX"
b2.color = fl.WHITE
local a2 = fl.Adjuster( b2.x+b2.w, 10, 25, 3*25 )
function a2:callback()
  b2.label = self:format()
  b2:redraw()
end
a2:callback()

window.resizable = window
window:end_group()
window:show( arg )
fl.run()

