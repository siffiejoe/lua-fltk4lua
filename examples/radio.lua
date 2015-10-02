#!/usr/bin/env lua

local fl = require( "fltk4lua" )
local window = fl.Window( 380, 220 )
local cb_info -- forward declaration

local function button_cb( b )
  local s = ("Label: '%s'\nValue: %s"):format( b.label, b.value and "true" or "false" )
  cb_info.value = s
  cb_info:redraw()
  print( s )
end

fl.Button{
  20, 10, 160, 30, "&Fl_Button A1",
  tooltip="Normal button (callback called only when released)",
  labelsize=13, callback=button_cb,
}
fl.Button{
  20, 44, 160, 30, "Fl_Button &A2",
  tooltip="Normal button with callback called when changed (push and released)",
  labelsize=13, when=fl.WHEN_CHANGED, callback=button_cb,
}
fl.Return_Button{
  20, 78, 160, 30, "Fl_Return_Button &B",
  tooltip="Button with Return key as default shortcut",
  labelsize=13, callback=button_cb,
}
fl.Light_Button{
  20, 113, 160, 30, "Fl_Light_Button &C",
  tooltip="Button with toggle state and a visual indicator of the current state",
  labelsize=13, callback=button_cb,
}
fl.Check_Button{
  20, 148, 160, 30, "Fl_Check_Button &D",
  tooltip="Check button with toggle state",
  down_box="FL_DOWN_BOX", labelsize=13, callback=button_cb,
}
fl.Round_Button{
  20, 178, 160, 30, "Fl_Round_Button &E",
  tooltip="Round button with toggle state",
  down_box="FL_ROUND_DOWN_BOX", labelsize=13, callback=button_cb,
}
local g = fl.Group{
  190, 10, 75, 120, box="FL_THIN_UP_FRAME"
}
fl.Round_Button{
  190, 10, 70, 30, "radio &1",
  tooltip="Radio button, only one button is set at a time, in the corresponding group.",
  type="FL_RADIO_BUTTON", down_box="FL_ROUND_DOWN_BOX",
  callback=button_cb,
}
fl.Round_Button{
  190, 40, 70, 30, "radio &2",
  tooltip="Radio button, only one button is set at a time, in the corresponding group.",
  type="FL_RADIO_BUTTON", down_box="FL_ROUND_DOWN_BOX",
  callback=button_cb,
}
fl.Round_Button{
  190, 70, 70, 30, "radio &3",
  tooltip="Radio button, only one button is set at a time, in the corresponding group.",
  type="FL_RADIO_BUTTON", down_box="FL_ROUND_DOWN_BOX",
  callback=button_cb,
}
fl.Round_Button{
  190, 100, 70, 30, "radio &4",
  tooltip="Radio button, only one button is set at a time, in the corresponding group.",
  type="FL_RADIO_BUTTON", down_box="FL_ROUND_DOWN_BOX",
  callback=button_cb,
}
g:end_group()
local g2 = fl.Group{
  275, 10, 90, 120,
  box="FL_THIN_UP_BOX",
}
fl.Button{
  285, 20, 20, 20, "radio",
  tooltip="Custum look button, only one button is set at a time, in the corresponding group.",
  type="FL_RADIO_BUTTON", selection_color=1, align=fl.ALIGN_RIGHT,
}
fl.Button{
  285, 45, 20, 20, "radio",
  tooltip="Custum look button, only one button is set at a time, in the corresponding group.",
  type="FL_RADIO_BUTTON", selection_color=1, align=fl.ALIGN_RIGHT,
}
fl.Button{
  285, 70, 20, 20, "radio",
  tooltip="Custum look button, only one button is set at a time, in the corresponding group.",
  type="FL_RADIO_BUTTON", selection_color=1, align=fl.ALIGN_RIGHT,
}
fl.Button{
  285, 95, 20, 20, "radio",
  tooltip="Custum look button, only one button is set at a time, in the corresponding group.",
  type="FL_RADIO_BUTTON", selection_color=1, align=fl.ALIGN_RIGHT,
}
g2:end_group()
cb_info = fl.Input{
  190, 148, 175, 62, "callback:",
  type="FL_MULTILINE_OUTPUT", textsize=12, align=fl.ALIGN_WRAP+fl.ALIGN_TOP_LEFT,
}
window:end_group()
window:show( arg )
fl.run()

