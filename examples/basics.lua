#!/usr/bin/env lua

local fl = require( "fltk4lua" )
local window = fl.Window( 340, 180 )
local box = fl.Box( 20, 40, 300, 100, "Hello World!" )
box.box = "up_box"
box.labelfont = "helvetica_bold_italic"
box.labelsize = 36
box.labeltype = "shadow"
window:end_group()
window:show( arg )
fl.run()

