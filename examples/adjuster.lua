#!/usr/bin/env lua

local fl = require( "fltk4lua" )
local window = fl.Window( 320, 100, arg[ 0 ] )
local b1 = fl.Box( 20, 35, 80, 25 )
b1.box = "FL_DOWN_BOX"
b1.color = fl.WHITE
local a1 = fl.Adjuster( 20+80, 35, 3*25, 25 )
a1.user_data = b1
function a1:callback( v )
  v.label = self:format()
  v:redraw()
end
a1:callback( b1 )

local b2 = fl.Box( 20+80+4*25, 35, 80, 25 )
b2.box = "FL_DOWN_BOX"
b2.color = fl.WHITE
local a2 = fl.Adjuster( b2.x+b2.w, 10, 25, 3*25 )
a2.user_data = b2
a2.callback = a1.callback
a2:callback( b2 )

--window.resizable = window -- looks bad in a tiling window manager
window:end_group()
window:show( arg )
fl.run()

