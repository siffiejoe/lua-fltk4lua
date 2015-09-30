#!/usr/bin/env lua

local fl = require( "fltk4lua" )
local window1 = fl.Window{ 220, 220, "Fl_Clock", xclass = "Fl_Clock" }
local c1 = fl.Clock{ 0, 0, 220, 220 }
--window1.resizable = c1 -- looks bad on a tiling window manager
window1:end_group()
local window2 = fl.Window{ 220, 220, "Fl_Round_Clock", xclass = "Fl_Clock" }
local c1 = fl.Clock{ 0, 0, 220, 220, type = "FL_ROUND_CLOCK" }
--window2.resizable = c1 -- looks bad on a tiling window manager
window2:end_group()
window1:show( arg )
window2:show()
fl.run()

