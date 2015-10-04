#!/usr/bin/env lua

local fl = require( "fltk4lua" )

local window = fl.Window{
  580, 510, "Valuator classes, showing values for type()",
  color=43, selection_color=43
}

local function cb( w )
  print( w.value )
end

local a17 = fl.ALIGN_TOP+fl.ALIGN_INSIDE

fl.Box{
  10, 10, 280, 210, "Fl_Slider",
  box="FL_ENGRAVED_BOX", labelfont=1, align=a17
}
fl.Slider{
  30, 45, 20, 145, "0",
  tooltip="Vertical Slider", selection_color=1, labelsize=8,
  align=fl.ALIGN_TOP, callback=cb,
}
fl.Slider{
  70, 55, 20, 145, "FL_VERT_FILL_SLIDER",
  type="FL_VERT_FILL_SLIDER", selection_color=1, labelsize=8,
  callback=cb,
}
fl.Slider{
  105, 45, 20, 145, "FL_VERT_NICE_SLIDER",
  type="FL_VERT_NICE_SLIDER", box="FL_FLAT_BOX", color=10,
  selection_color=1, labelsize=8,
  align=fl.ALIGN_TOP, callback=cb,
}
fl.Slider{
  140, 80, 130, 20, "FL_HORIZONTAL",
  type="FL_HORIZONTAL", selection_color=1, labelsize=8, callback=cb,
}
fl.Slider{
  140, 120, 130, 20, "FL_HOR_FILL_SLIDER",
  type="FL_HOR_FILL_SLIDER", selection_color=1, labelsize=8, callback=cb,
}
fl.Slider{
  140, 160, 130, 20, "FL_HOR_NICE_SLIDER",
  type="FL_HOR_NICE_SLIDER", box="FL_FLAT_BOX", color=10,
  selection_color=1, labelsize=8, callback=cb,
}
fl.Box{
  10, 230, 280, 210, "Fl_Value_Slider",
  box="FL_ENGRAVED_BOX", labelfont=1, align=a17,
}
fl.Value_Slider{
  30, 260, 30, 145, "0",
  tooltip="Value Slider", selection_color=1, labelsize=8,
  align=fl.ALIGN_TOP, callback=cb,
}
fl.Value_Slider{
  70, 275, 30, 140, "FL_VERT_FILL_SLIDER",
  type="FL_VERT_FILL_SLIDER", selection_color=1, labelsize=8,
  callback=cb,
}
fl.Value_Slider{
  110, 260, 20, 145, "FL_VERT_NICE_SLIDER",
  type="FL_VERT_NICE_SLIDER", box="FL_FLAT_BOX", color=10,
  selection_color=1, labelsize=8, align=fl.ALIGN_TOP,
  callback=cb,
}
fl.Value_Slider{
  140, 290, 130, 20, "FL_HOR_SLIDER",
  type="FL_HORIZONTAL", selection_color=1, labelsize=8,
  callback=cb,
}
fl.Value_Slider{
  140, 330, 130, 20, "FL_HOR_FILL_SLIDER",
  type="FL_HOR_FILL_SLIDER", selection_color=1, labelsize=8, callback=cb,
}
fl.Value_Slider{
  140, 370, 130, 20, "FL_HOR_NICE_SLIDER",
  type="FL_HOR_NICE_SLIDER", box="FL_FLAT_BOX", color=10,
  selection_color=1, labelsize=8, callback=cb,
}
fl.Box{
  10, 450, 135, 50, "Fl_Value_Input",
  box="FL_ENGRAVED_BOX", labelfont=1, align=a17,
}
fl.Value_Input{
  30, 470, 105, 25, "0",
  tooltip="Value Input", labelsize=8, maximum=100, step=0.1,
  callback=cb,
}
fl.Box{
  155, 450, 135, 50, "Fl_Value_Output",
  box="FL_ENGRAVED_BOX", labelfont=1, align=a17,
}
fl.Value_Output{
  170, 470, 105, 25, "0",
  tooltip="Value Output", labelsize=8, maximum=100, step=0.1,
}
fl.Box{
  300, 10, 130, 120, "Fl_Scrollbar",
  box="FL_ENGRAVED_BOX", labelfont=1,
  align=fl.ALIGN_TOP_LEFT+fl.ALIGN_INSIDE,
}
fl.Scrollbar{
  305, 65, 95, 20, "FL_HORIZONTAL",
  tooltip="Horizontal Scrollbar", type="FL_HORIZONTAL", labelsize=8,
  maximum=100, value=20, callback=cb,
}
fl.Scrollbar{
  400, 20, 20, 105, "0",
  tooltip="Vertical Scrollbar", labelsize=8, maximum=100,
  align=fl.ALIGN_TOP, callback=cb,
}
fl.Box{
  440, 10, 130, 120, "Fl_Adjuster",
  box="FL_ENGRAVED_BOX", labelfont=1, align=a17,
}
fl.Adjuster{
  450, 60, 75, 25, "w()>h()",
  tooltip="Horizontal Adjuster", labelsize=8, callback=cb,
}
fl.Adjuster{
  530, 35, 25, 75, "w()<h()",
  tooltip="Vertical Adjuster", labelsize=8, callback=cb,
}
fl.Box{
  300, 140, 130, 120, "Fl_Counter",
  box="FL_ENGRAVED_BOX", labelfont=1, align=a17,
}
fl.Counter{
  310, 175, 110, 25, "0",
  tooltip="Standard Counter", labelsize=8, callback=cb,
}
fl.Counter{
  310, 215, 110, 25, "FL_SIMPLE_COUNTER",
  type="FL_SIMPLE_COUNTER", tooltip="Simple Counter", labelsize=8,
  callback=cb,
}
fl.Box{
  440, 140, 130, 120, "Fl_Spinner",
  box="FL_ENGRAVED_BOX", labelfont=1, align=a17,
}
fl.Spinner{
  465, 176, 80, 24, "FL_INT_INPUT",
  labelsize=8, minimum=-30, maximum=30, step=2, value=5,
  align=fl.ALIGN_BOTTOM, callback=cb,
}
fl.Spinner{
  465, 216, 80, 24, "FL_FLOAT_INPUT",
  type="FL_FLOAT_INPUT", labelsize=8, minimum=0, maximum=1, step=0.01,
  value=0.05, align=fl.ALIGN_BOTTOM, callback=cb,
}
fl.Box{
  300, 270, 270, 105, "Fl_Dial",
  box="FL_ENGRAVED_BOX", labelfont=1, align=a17,
}
fl.Dial{
  320, 295, 65, 65, "0",
  tooltip="Standard Dial", color=10, selection_color=1, labelsize=8,
  value=0.5, callback=cb,
}:angles( 0, 315 )
fl.Dial{
  400, 295, 65, 65, "FL_LINE_DIAL",
  type="FL_LINE_DIAL", color=10, selection_color=1, labelsize=8,
  value=0.5, callback=cb,
}
--[[
-- FIXME: For some reason manipulating this Fill_Dial will cause my
-- X-Session to die (the same happens when using C++, so it's probably
-- not my fault). Disable for now, but if you are feeling lucky, you
-- can try ...
fl.Dial{
  480, 295, 65, 65, "FL_FILL_DIAL",
  type="FL_FILL_DIAL", color=10, selection_color=1, labelsize=8,
  value=1, callback=cb,
}:angles( 0, 360 )
--]]
fl.Box{
  300, 385, 150, 115, "Fl_Roller",
  box="FL_ENGRAVED_BOX", labelfont=1, align=a17,
}
fl.Roller{
  315, 390, 20, 95, "0",
  tooltip="Vertical Roller", labelsize=8, callback=cb,
}
fl.Roller{
  345, 430, 90, 20, "FL_HORIZONTAL",
  type="FL_HORIZONTAL", tooltip="Horizontal Roller", labelsize=8,
  callback=cb,
}
fl.Box{
  460, 385, 110, 115,
  "Some widgets have color(FL_GREEN and color2(FL_RED) to show the aread these effect.",
  box="FL_BORDER_FRAME", color=0, selection_color=0, labelsize=11, align=fl.ALIGN_WRAP,
}
window:end_group()

window:show( arg )
fl.run()

