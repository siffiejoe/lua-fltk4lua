#!/usr/bin/env lua

local function sleep( s )
  local start = os.clock()
  while os.clock() - start < s do
    -- busy loop
  end
end

local fl = require( "fltk4lua" )
local win = fl.Window( 220, 90 )
local butt = fl.Button( 10, 10, 100, 25, "Press" )
butt.user_data = win
function butt:callback( w )
  self:deactivate()
  fl.check()
  w:begin_group()
  local progress = fl.Progress( 10, 50, 200, 30 )
  progress.minimum = 0
  progress.maximum = 1
  progress.color = 2290649088 -- new Lua versions also know hex numbers
  progress.selection_color = 1145372416
  progress.labelcolor = fl.WHITE
  w:end_group()
  for t = 1, 500 do
    progress.value = t/500
    progress.label = ("%d%%"):format( math.floor( t/500*100 ) )
    if not fl.check() then break end
    sleep( 0.01 )
  end
  w:remove( w:find( progress ) )
  self:activate()
  w:redraw()
end
--win.resizable = win -- looks bad with a tiling window manager
win:end_group()
win:show()
fl.run()

