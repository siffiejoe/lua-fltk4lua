#!/usr/bin/env lua

local fl = require( "fltk4lua" )

local function bidi( t )
  local t2 = {}
  for k,v in ipairs( t ) do
    t2[ k ] = v
    t2[ v ] = k
  end
  return t2
end

local cursors = bidi{
  "FL_CURSOR_DEFAULT",
  "FL_CURSOR_ARROW",
  "FL_CURSOR_CROSS",
  "FL_CURSOR_WAIT",
  "FL_CURSOR_INSERT",
  "FL_CURSOR_HAND",
  "FL_CURSOR_HELP",
  "FL_CURSOR_MOVE",
  "FL_CURSOR_NS",
  "FL_CURSOR_WE",
  "FL_CURSOR_NWSE",
  "FL_CURSOR_NESW",
  "FL_CURSOR_NONE",
  "FL_CURSOR_N",
  "FL_CURSOR_NE",
  "FL_CURSOR_E",
  "FL_CURSOR_SE",
  "FL_CURSOR_S",
  "FL_CURSOR_SW",
  "FL_CURSOR_W",
  "FL_CURSOR_NW",
}

local fg = 56 -- fl.BLACK
local bg = 255 -- fl.WHITE
local cursor = "FL_CURSOR_DEFAULT"
local choice, cursor_slider

local function choice_cb( self, v )
  local c = cursors[ v ]
  if c then
    cursor_slider.value = c
    fl.cursor( v, fg, bg )
  end
end
local function setcursor( self )
  local c = cursors[ self.value ]
  if c then
    cursor = c
    choice.value = self.value-1
    fl.cursor( cursor, fg, bg )
  end
end
local function setfg( self )
  fg = self.value
  fl.cursor( cursor, fg, bg )
end
local function setbg( self )
  bg = self.value
  fl.cursor( cursor, fg, bg )
end

local window = fl.Window( 400, 300 )

choice = fl.Choice{
  80, 100, 200, 25, "Cursor:",
  when=fl.WHEN_RELEASE+fl.WHEN_NOT_CHANGED,
  callback=choice_cb,
}
for _,v in ipairs( cursors ) do
  choice:add( v, 0, choice_cb, v )
end
choice.value = 0

cursor_slider = fl.Value_Slider{
  80, 180, 310, 30, "Cursor:",
  type="FL_HORIZONTAL", align=fl.ALIGN_LEFT, step=1,
  precision=0, value=0, callback=setcursor,
}
cursor_slider:bounds( 1, #cursors )
cursor_slider.value = cursors[ cursor ]

local slider2 = fl.Value_Slider{
  80, 220, 310, 30, "fgcolor:",
  type="FL_HORIZONTAL", align=fl.ALIGN_LEFT, step=1,
  precision=0, value=0, callback=setfg,
}
slider2:bounds( 0, 255 )
slider2.value = fg

local slider3 = fl.Value_Slider{
  80, 260, 310, 30, "bgcolor:",
  type="FL_HORIZONTAL", align=fl.ALIGN_LEFT, step=1,
  precision=0, value=0, callback=setbg,
}
slider3:bounds( 0, 255 )
slider3.value = bg

--window.resizable = window -- looks bad on a tiling window manager!
window:end_group()
window:show( arg )
fl.run()

