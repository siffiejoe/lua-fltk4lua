#!/usr/bin/env lua

local fl = require( "fltk4lua" )
local window = fl.Window( 360, 370 )
local scroll = fl.Scroll( 10, 10, 340, 285 )
local pack = fl.Pack{ 10, 10, 340, 285, box = "FL_DOWN_FRAME" }
fl.Button( 35, 35, 25, 25, "b1" )
fl.Button( 45, 45, 25, 25, "b2" )
fl.Button( 55, 55, 25, 25, "b3" )
fl.Button( 65, 65, 25, 25, "b4" )
fl.Button( 75, 75, 25, 25, "b5" )
fl.Button( 85, 85, 25, 25, "b6" )
fl.Button( 95, 95, 25, 25, "b7" )
fl.Button( 105, 105, 25, 25, "b8" )
fl.Button( 115, 115, 25, 25, "b9" )
fl.Button( 125, 125, 25, 25, "b10" )
fl.Button( 135, 135, 25, 25, "b11" )
fl.Button( 145, 145, 25, 25, "b12" )
fl.Button( 155, 155, 25, 25, "b13" )
fl.Button( 165, 165, 25, 25, "b14" )
fl.Button( 175, 175, 25, 25, "b15" )
fl.Button( 185, 185, 25, 25, "b16" )
fl.Button( 195, 195, 25, 25, "b17" )
fl.Button( 205, 205, 25, 25, "b18" )
fl.Button( 215, 215, 25, 25, "b19" )
fl.Button( 225, 225, 25, 25, "b20" )
fl.Button( 235, 235, 25, 25, "b21" )
fl.Button( 245, 245, 25, 25, "b22" )
fl.Button( 255, 255, 25, 25, "b23" )
fl.Button( 265, 265, 25, 25, "b24" )
pack:end_group()
window.resizable = pack
scroll:end_group()

local function type_cb( _, t )
  for i = 0, pack.children-1 do
    local o = pack:child( i )
    o:resize( 0, 0, 25, 25 )
  end
  pack:resize( scroll.x, scroll.y, scroll.w, scroll.h )
  pack.parent:redraw()
  pack.type = t
  pack:redraw()
end

fl.Light_Button{ 10, 305, 165, 25, "HORIZONTAL",
                 type = "FL_RADIO_BUTTON",
                 user_data = "HORIZONTAL",
                 callback = type_cb }
fl.Light_Button{ 185, 305, 165, 25, "VERTICAL",
                 type = "FL_RADIO_BUTTON",
                 value = true,
                 user_data = "VERTICAL",
                 callback = type_cb }
local sl = fl.Slider{ 100, 335, 250, 25, "Spacing: ",
                      align = fl.ALIGN_LEFT,
                      type = "FL_HORIZONTAL",
                      step = 1 }
sl:range( 0, 30 )
function sl:callback()
  pack.spacing = self.value
  scroll:redraw()
end

window:end_group()
window:show( arg )
fl.run()

