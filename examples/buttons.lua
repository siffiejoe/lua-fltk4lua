#!/usr/bin/env lua

local fl = require( "fltk4lua" )
local window = fl.Window( 320, 130 )
fl.Button( 10, 10, 130, 30, "Fl_Button" )
  .tooltip = "This is a Tooltip."
fl.Repeat_Button( 10, 50, 130, 30, "Fl_Repeat_Button" )
fl.Light_Button( 10, 90, 130, 30, "Fl_Light_Button" )
fl.Return_Button( 150, 10, 160, 30, "Fl_Return_Button" )
fl.Round_Button( 150, 50, 160, 30, "Fl_Round_Button" )
fl.Check_Button( 150, 90, 160, 30, "Fl_Check_Button" )
window:end_group()
window:show( arg )
fl.run()

