#!/usr/bin/env lua

local fl = require( "fltk4lua" )
local window = fl.Window( 300, 300 )
window.box = "FL_NO_BOX"
--window.resizable = window -- looks bad on a tiling window manager!
local tile = fl.Tile( 0, 0, 300, 300 )
local box0 = fl.Box{
  0, 0, 150, 150, "0",
  box="FL_DOWN_BOX", color=9, labelsize=36, align=fl.ALIGN_CLIP,
}

local w1 = fl.Window( 150, 0, 150, 150, "1" )
w1.box = "FL_NO_BOX"
local box1 = fl.Box{
  0, 0, 150, 150, "1\nThis is a\nchild\nwindow",
  box="FL_DOWN_BOX", color=19, labelsize=18, align=fl.ALIGN_CLIP,
}
w1.resizable = box1
w1:end_group()

fl.Box{
  0, 150, 70, 150, "2a",
  box="FL_DOWN_BOX", color=12, labelsize=36, align=fl.ALIGN_CLIP,
}
fl.Box{
  70, 150, 80, 150, "2b",
  box="FL_DOWN_BOX", color=13, labelsize=36, align=fl.ALIGN_CLIP,
}

fl.Box{
  150, 150, 150, 70, "3a",
  box="FL_DOWN_BOX", color=12, labelsize=36, align=fl.ALIGN_CLIP,
}
fl.Box{
  150, 150+70, 150, 80, "3b",
  box="FL_DOWN_BOX", color=13, labelsize=36, align=fl.ALIGN_CLIP,
}

local r = fl.Box( 10, 0, 300-10, 300-10 )
tile.resizable = r

tile:end_group()

window:end_group()
w1:show()
window:show( arg )
fl.run()

