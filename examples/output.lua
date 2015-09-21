#!/usr/bin/env lua

local fl = require( "fltk4lua" )

local text, text2

local window = fl.Window( 400, 400 )
local input = fl.Input( 50, 375, 350, 25 )
input.value = "The quick brown fox\njumped over\nthe lazy dog."
input.when = fl.WHEN_CHANGED
function input:callback()
  text.value = self.value
  text2.value = self.value
end

local sizes = fl.Value_Slider( 50, 350, 350, 25, "Size" )
sizes.type = "FL_HORIZONTAL"
sizes.align = fl.ALIGN_LEFT
sizes:bounds( 1, 64 )
sizes.step = 1
sizes.value = 14
function sizes:callback()
  text.textsize = self.value
  text:redraw()
  text2.textsize = self.value
  text2:redraw()
end

local fonts = fl.Value_Slider( 50, 325, 350, 25, "Font" )
fonts.type = "FL_HORIZONTAL"
fonts.align = fl.ALIGN_LEFT
fonts:bounds( 0, 15 )
fonts.step = 1
fonts.value = 0
function fonts:callback()
  text.textfont = self.value
  text:redraw()
  text2.textfont = self.value
  text2:redraw()
end

text2 = fl.Input( 100, 150, 200, 100, "Fl_Multiline_Output" )
text2.type = "FL_MULTILINE_OUTPUT"
text2.value = input.value
text2.align = fl.ALIGN_BOTTOM
text2.tooltip = "This is an Fl_Multiline_Output widget."
window.resizable = text2

text = fl.Input( 100, 90, 200, 30, "Fl_Output" )
text.type = "FL_NORMAL_OUTPUT"
text.value = input.value
text.align = fl.ALIGN_BOTTOM
text.tooltip = "This is an Fl_Output widget."

window:end_group()
window:show( arg )
fl.run()

