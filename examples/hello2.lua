#!/usr/bin/env lua

local fl = require( "fltk4lua" )
local window = fl.Window{ 340, 180, label = "Hello" }
local box = fl.Box{ 20, 40, 300, 100, "Hello World!",
                    box = "FL_UP_BOX", labelsize = 36,
                    labelfont = "FL_HELVETICA_BOLD_ITALIC",
                    labeltype = "FL_SHADOW_LABEL" }
window:end_group()
window:show( arg )
fl.run()

