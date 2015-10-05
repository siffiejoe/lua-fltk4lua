#!/usr/bin/env lua

local fl = require( "fltk4lua" )
fl.scheme( "gtk+" )
local win = fl.Window( 500, 200, "Tabs Example" )
do
  local tabs = fl.Tabs( 10, 10, 500-20, 200-20 )
  do
    local aaa = fl.Group( 10, 35, 500-20, 200-45, "Aaa" )
    do
      local a1 = fl.Button( 50,  60, 90, 25, "Button A1" )
      a1.color = 88+1
      local a2 = fl.Button( 50,  90, 90, 25, "Button A2" )
      a2.color = 88+2
      local a3 = fl.Button( 50, 120, 90, 25, "Button A3" )
      a3.color = 88+3
    end
    aaa:end_group()
    local bbb = fl.Group( 10, 35, 500-10, 200-35, "Bbb" )
    do
      local b1 = fl.Button(  50, 60, 90, 25, "Button B1" )
      b1.color = 88+1
      local b2 = fl.Button( 150, 60, 90, 25, "Button B2" )
      b2.color = 88+3
      local b3 = fl.Button( 250, 60, 90, 25, "Button B3" )
      b3.color = 88+5
      local b4 = fl.Button(  50, 90, 90, 25, "Button B4" )
      b4.color = 88+2
      local b5 = fl.Button( 150, 90, 90, 25, "Button B5" )
      b5.color = 88+4
      local b6 = fl.Button( 250, 90, 90, 25, "Button B6" )
      b6.color = 88+6
    end
    bbb:end_group()
  end
  tabs:end_group()
end
win:end_group()
win:show( arg )
fl.run()

