#!/usr/bin/env lua

local fl = require( "fltk4lua" )
fl.args( arg )
local window = fl.Window( 480, 400, "browser.cxx" )
local field -- forward declaration
local browser = fl.Browser{
  0, 0, 480, 350, type="FL_MULTI_BROWSER",
}
-- You need to copy browser.cxx from the test sub-directory in the
-- FLTK source code here for this demo to work!
assert( browser:load( "examples/browser.cxx" ) )
browser.vposition = 0

local function show_cb( w, v )
  local line = tonumber( field.value )
  if not line then
    return fl.alert[[
Please enter a number in the text field
before clicking on the buttons.]]
  end
  if v == "top" then
    browser.topline = line
  elseif v == "bottom" then
    browser.bottomline = line
  elseif v == "middle" then
    browser.middleline = line
  else
    browser:make_visible( line )
  end
end
field = fl.Input{
  50, 350, 430, 25, "Line #:", type="FL_INT_INPUT",
  callback=show_cb,
}
fl.Button{
  0, 375, 80, 25, "Top", callback=show_cb, user_data="top",
}
fl.Button{
  80, 375, 80, 25, "Bottom", callback=show_cb, user_data="bottom",
}
fl.Button{
  160, 375, 80, 25, "Middle", callback=show_cb, user_data="middle",
}
fl.Button{
  240, 375, 80, 25, "Make Vis.", callback=show_cb,
}
local swap = fl.Button{
  320, 375, 80, 25, "Swap",
  tooltip="Swaps two selected lines\n(Use CTRL-click to select two lines)",
}
function swap:callback()
  local a, b = -1, -1
  for t = 1, browser.nitems do
    if browser:selected( t ) then
      if a < 0 then
        a = t
      else
        b = t
        break
      end
    end
  end
  if a > 0 and b > 0 then
    browser:swap( a, b )
  end
end
local sort = fl.Button{
  400, 375, 80, 25, "Sort",
}
function sort:callback()
  browser:sort( "FL_SORT_ASCENDING" )
end

window:end_group()
--window.resizable = browser -- looks bad with a tiling window manager
window:show( arg )
fl.run()

