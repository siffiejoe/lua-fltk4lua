#!/usr/bin/env lua

local fl = require( "fltk4lua" )
local mainw = fl.Window( 200, 200 )
mainw:end_group()
mainw:show( arg )

local control = fl.Window( 120, 120 )
function control:callback()
  --os.exit( 0 ) -- bad style!
  self:hide()
  mainw:hide()
end

local hide_button = fl.Button( 0, 0, 120, 30, "hide()" )
function hide_button:callback()
  mainw:hide()
end

local iconize_button = fl.Button( 0, 30, 120, 30, "iconize()" )
function iconize_button:callback()
  mainw:iconize()
end

local show_button = fl.Button( 0, 60, 120, 30, "show()" )
function show_button:callback()
  mainw:show()
end

local show_button2 = fl.Button( 0, 90, 120, 30, "show this" )
function show_button2:callback()
  control:show()
end

control:end_group()
control:show()
fl.run()

