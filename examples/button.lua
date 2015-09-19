#!/usr/bin/env lua

local fl = require( "fltk4lua" )
local window = fl.Window( 320, 65 )

local b1 = fl.Button( 20, 20, 80, 25, "&Beep" )
function b1:callback()
  fl.beep()
end
fl.Button( 120, 20, 80, 25, "&no op" )
local b3 = fl.Button( 220, 20, 80, 25, "E&xit" )
function b3:callback()
  --os.exit( 0 ) -- bad style
  window:hide()
end
window:end_group()
window:show( arg )
fl.run()

