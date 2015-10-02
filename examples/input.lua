#!/usr/bin/env lua

local fl = require( "fltk4lua" )
fl.args( arg )
fl.get_system_colors()
local window = fl.Window( 400, 420 )

local function input_cb( self )
  print( ("Callback for %s '%s'"):format( self.label, self.value ) )
end
local input = {
  fl.Input{
    70, 10, 300, 30, "Normal:",
    tooltip="Normal input field",
    when=fl.WHEN_NEVER, callback=input_cb,
  },
  fl.Input{
    70, 45, 300, 30, "Float:", type="FL_FLOAT_INPUT",
    tooltip="Input field for floating-point number (F1)",
    when=fl.WHEN_NEVER, callback=input_cb,
    shortcut=fl.F1
  },
  fl.Input{
    70, 80, 300, 30, "Int:", type="FL_INT_INPUT",
    tooltip="Input field for integer number (F2)",
    when=fl.WHEN_NEVER, callback=input_cb,
    shortcut=fl.F2,
  },
  fl.Input{
    70, 115, 300, 30, "&Secret:", type="FL_SECRET_INPUT",
    tooltip="Input field for password (Alt-S)",
    when=fl.WHEN_NEVER, callback=input_cb,
  },
  fl.Input{
    70, 150, 300, 100, "&Multiline:", type="FL_MULTILINE_INPUT",
    tooltip="Input field for short text with newlines (Alt-M)",
    wrap=true, when=fl.WHEN_NEVER, callback=input_cb,
  },
}

local when = fl.WHEN_NEVER
local function toggle_cb( self, w )
  if self.value then
    when = when + w
  else
    when = when - w
  end
  for _,v in ipairs( input ) do
    v.when = when
  end
end
fl.Button{
  10, 255, 200, 25, "FL_WHEN_CHANGED", type="FL_TOGGLE_BUTTON",
  tooltip="Do callback each time the text changes",
  callback=toggle_cb, user_data=fl.WHEN_CHANGED,
}
fl.Button{
  10, 280, 200, 25, "FL_WHEN_RELEASE", type="FL_TOGGLE_BUTTON",
  tooltip="Do callback when widget loses focus",
  callback=toggle_cb, user_data=fl.WHEN_RELEASE,
}
fl.Button{
  10, 305, 200, 25, "FL_WHEN_ENTER_KEY", type="FL_TOGGLE_BUTTON",
  tooltip="Do callback when user hits Enter key",
  callback=toggle_cb, user_data=fl.WHEN_ENTER_KEY,
}
fl.Button{
  10, 330, 200, 25, "FL_WHEN_NOT_CHANGED", type="FL_TOGGLE_BUTTON",
  tooltip="Do callback even if the text is not changed",
  callback=toggle_cb, user_data=fl.WHEN_NOT_CHANGED,
}
local b = fl.Button{
  10, 360, 200, 25, "&print changed()",
  tooltip="Print widgets that have changed() flag set",
}
function b:callback()
  for _,v in ipairs( input ) do
    if v.changed then
      v:clear_changed()
      print( ("%s '%s'"):format( v.label, v.value ) )
      -- XXX utf8 stuff?!
    end
  end
end

local b = fl.Light_Button{
  10, 385, 100, 25, " Tab Nav",
  tooltip="Control tab navigation for the multiline input field",
  user_data=input[ 5 ], value=input[ 5 ].tab_nav,
}
function b:callback( fmi )
  fmi.tab_nav = b.value
end

local b = fl.Light_Button{
  110, 385, 100, 25, " Arrow Nav",
  tooltip=[[
Control horizontal arrow key focus navigation behavior.
e.g. Fl::OPTION_ARROW_FOCUS]],
  value=fl.option( "OPTION_ARROW_FOCUS" ),
}
function b:callback()
  fl.option( "OPTION_ARROW_FOCUS", self.value )
end

local function color_cb( self, c )
  local c2 = fl.color_chooser( nil, fl.get_color( c ) )
  if c2 then
    fl.set_color( c, fl.get_color( c2 ) )
    self.labelcolor = fl.contrast( fl.BLACK, c )
    fl.redraw()
  end
end
fl.Button{
  220, 255, 120, 25, "color", color=input[ 1 ].color,
  callback=color_cb, user_data=fl.BACKGROUND2_COLOR,
  tooltip="Color behind the text",
}
fl.Button{
  220, 280, 120, 25, "selection_color", color=input[ 1 ].selection_color,
  labelcolor=fl.contrast( fl.BLACK, input[ 1 ].selection_color ),
  callback=color_cb, user_data=fl.SELECTION_COLOR,
  tooltip="Color behind selected text",
}
fl.Button{
  220, 305, 120, 25, "textcolor", color=input[ 1 ].textcolor,
  labelcolor=fl.contrast( fl.BLACK, input[ 1 ].textcolor ),
  callback=color_cb, user_data=fl.FOREGROUND_COLOR,
  tooltip="Color of the text",
}

window:end_group()
window:show( arg )
fl.run()

