#!/usr/bin/env lua

local fl = require( "fltk4lua" )
local window = fl.Window( 340, 180 )
local box = fl.Box( 20, 40, 300, 100, "Hello World!" )
box.box = "FL_UP_BOX"
box.labelfont = "FL_HELVETICA_BOLD_ITALIC"
box.labelsize = 36
box.labeltype = "FL_SHADOW_LABEL"
window:end_group()
window:show( arg )
print( window.xid )
print( fl.w(), fl.h() )
fl.run()

