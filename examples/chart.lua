#!/usr/bin/env lua

math.randomseed( os.time() )
local fl = require( "fltk4lua" )
local window = fl.Window( 500, 320 )

local chart_types = {
  "FL_BAR_CHART", "FL_FILLED_CHART", "FL_HORBAR_CHART",
  "FL_LINE_CHART", "FL_PIE_CHART", "FL_SPECIALPIE_CHART",
  "FL_SPIKE_CHART"
}
local choice = fl.Choice( 50, 75, 190, 20, "Type:" )
for _,v in ipairs( chart_types ) do
  choice:add( v )
end
choice.value = 0
function choice:callback( chart )
  chart.type = chart_types[ self.value+1 ]
  chart:redraw()
end
local chart1 = fl.Chart{
  250, 10, 230, 150, "Chart 1",
  type=chart_types[ 1 ], box="FL_ROUNDED_BOX", color=fl.WHITE,
}
chart1:add( 10, "item 1", fl.BLUE )
chart1:add( 25, "item 2", fl.RED )
chart1:add( 35, "item 3", fl.GREEN )
chart1:add( 5, "item 4", fl.CYAN )
chart1:add( 20, "item 5", fl.YELLOW )
choice.user_data = chart1

local retb = fl.Return_Button( 50, 140, 180, 20, "Step" )
function retb:callback( chart )
  chart:add( math.random( 10, 100 ), nil, fl.BLUE )
end
local chart2 = fl.Chart{
  10, 180, 480, 110, "Chart 2",
  type="FL_FILLED_CHART", box="FL_ROUNDED_BOX", color=fl.WHITE,
  autosize=false, maxsize=10,
}
chart2:bounds( 0, 100 )
for i = 1, 3 do
  retb:callback( chart2 )
end
retb.user_data = chart2

window:end_group()
window:show( arg )
fl.run()

