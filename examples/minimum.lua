#!/usr/bin/env lua

local fl = require( "fltk4lua" )
local window = fl.Window( 400, 320, arg[ 0 ] )
local b = fl.Box( 10, 10, 300, 300, [[
MINIMUM UPDATE TEST

The slider on the right purposely
draws outside its boundaries.
Moving it should leave old copies
of the label.  These copies should
*not* be erased by any actions
other than hiding and showing
of that portion of the window
or changing the button that
intersects them.]] )
b.box = "FL_ENGRAVED_FRAME"
window.resizable = b

local s = fl.Slider( 320, 10, 20, 300, "Too_Big_Label" )
s.align = fl.ALIGN_CENTER
fl.Button( 20, 270, 100, 30, "Button" )
fl.Return_Button( 200, 270, 100, 30, "Button" )

window:show( arg )
fl.run()

