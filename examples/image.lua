#!/usr/bin/env lua

local fl = require( "fltk4lua" )
local window = fl.Window( 300, 150 )
local group = fl.Group( 0, 0, 300, 150, "FLTK image" )
-- you'll need the fltk.xpm file available in the FLTK source to run
-- this test script!
group.image = fl.Shared_Image.get( "examples/fltk.xpm" )
group.align = fl.ALIGN_INSIDE
local button = fl.Button( 240, 115, 50, 25, "Close" )
function button:callback()
  window:hide()
end
group:end_group()
window:end_group()
window:show( arg )
fl.run()

