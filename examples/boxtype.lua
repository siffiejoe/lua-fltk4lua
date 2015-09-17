#!/usr/bin/env lua

local fl = require( "fltk4lua" )

local N = 0
local W = 100
local H = 30
local ROWS = 14
local square = false

local function bt( t )
  local x = N % 4
  local y = (N - x)/4
  N = N + 1
  x = x * W + 10
  y = y * H + 10
  local b = fl.Box( x, y, square and H-20 or W-20, H-20, t )
  b.box = t
  b.labelsize = 11
  if square then b.align = fl.ALIGN_RIGHT end
end

local window = fl.Window( 4*W, ROWS*H )
window.box = "FL_FLAT_BOX"
fl.args( arg )
fl.get_system_colors()
window.color = 12
bt( "FL_NO_BOX" )
bt( "FL_FLAT_BOX" )
N = N + 2
bt( "FL_UP_BOX" )
bt( "FL_DOWN_BOX" )
bt( "FL_UP_FRAME" )
bt( "FL_DOWN_FRAME" )
bt( "FL_THIN_UP_BOX" )
bt( "FL_THIN_DOWN_BOX" )
bt( "FL_THIN_UP_FRAME" )
bt( "FL_THIN_DOWN_FRAME" )
bt( "FL_ENGRAVED_BOX" )
bt( "FL_EMBOSSED_BOX" )
bt( "FL_ENGRAVED_FRAME" )
bt( "FL_EMBOSSED_FRAME" )
bt( "FL_BORDER_BOX" )
bt( "FL_SHADOW_BOX" )
bt( "FL_BORDER_FRAME" )
bt( "FL_SHADOW_FRAME" )
bt( "FL_ROUNDED_BOX" )
bt( "FL_RSHADOW_BOX" )
bt( "FL_ROUNDED_FRAME" )
bt( "FL_RFLAT_BOX" )
bt( "FL_OVAL_BOX" )
bt( "FL_OSHADOW_BOX" )
bt( "FL_OVAL_FRAME" )
bt( "FL_OFLAT_BOX" )
bt( "FL_ROUND_UP_BOX" )
bt( "FL_ROUND_DOWN_BOX" )
bt( "FL_DIAMOND_UP_BOX" )
bt( "FL_DIAMOND_DOWN_BOX" )

bt( "FL_PLASTIC_UP_BOX" )
bt( "FL_PLASTIC_DOWN_BOX" )
bt( "FL_PLASTIC_UP_FRAME" )
bt( "FL_PLASTIC_DOWN_FRAME" )
bt( "FL_PLASTIC_THIN_UP_BOX" )
bt( "FL_PLASTIC_THIN_DOWN_BOX" )
N = N + 2
bt( "FL_PLASTIC_ROUND_UP_BOX" )
bt( "FL_PLASTIC_ROUND_DOWN_BOX" )
N = N + 2

bt( "FL_GTK_UP_BOX" )
bt( "FL_GTK_DOWN_BOX" )
bt( "FL_GTK_UP_FRAME" )
bt( "FL_GTK_DOWN_FRAME" )
bt( "FL_GTK_THIN_UP_BOX" )
bt( "FL_GTK_THIN_DOWN_BOX" )
bt( "FL_GTK_THIN_UP_FRAME" )
bt( "FL_GTK_THIN_DOWN_FRAME" )
bt( "FL_GTK_ROUND_UP_BOX" )
bt( "FL_GTK_ROUND_DOWN_BOX" )
window.resizable = window
window:end_group()
window:show()
fl.run()

