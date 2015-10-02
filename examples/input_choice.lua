#!/usr/bin/env lua

local fl = require( "fltk4lua" )
local window = fl.Window( 300, 200 )

local ic = fl.Input_Choice( 40, 40, 100, 28, "Test" )
function ic:callback()
  print( ("Value='%s'"):format( self.value ) )
end
ic:add( "one" )
ic:add( "two" )
ic:add( "three" )
ic.value = 1

local onoff = fl.Button( 40, 150, 200, 28, "Activate/Deactivate" )
local flag = true
function onoff:callback()
  flag = not flag
  if flag then
    ic:activate()
  else
    ic:deactivate()
  end
  if ic.changed then
    print( "Callback: changed() is set" )
    ic:clear_changed()
  end
end

window:end_group()
--window.resizable = window -- looks bad with a tiling window mananger
window:show( arg )
fl.run()

