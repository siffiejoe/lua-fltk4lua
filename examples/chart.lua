#!/usr/bin/env lua

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
  type=chart_types[ 1 ], color=fl.WHITE,
  autosize=true, box="FL_ROUNDED_BOX",
}
chart1:add( 10, "item 1", fl.BLUE )
chart1:add( 25, "item 2", fl.RED )
chart1:add( 35, "item 3", fl.GREEN )
chart1:add( 5, "item 4", fl.CYAN )
chart1:add( 20, "item 5", fl.YELLOW )
choice.user_data = chart1

math.randomseed( os.time() )
local values = {}
for i = 1, 10 do
  values[ i ] = math.random( 10, 100 )
end

local retb = fl.Return_Button( 50, 140, 180, 20, "Step" )
function retb:callback( chart )
  table.remove( values, 1 )
  values[ #values+1 ] = math.random( 10, 100 )
  chart:clear()
  for _,v in ipairs( values ) do
    chart:add( v, nil, fl.BLUE )
  end
  chart:redraw()
end
local chart2 = fl.Chart{
  10, 180, 480, 110, "Chart 2",
  type="FL_LINE_CHART", color=fl.WHITE,
  box="FL_ROUNDED_BOX",
}
chart2:bounds( 0, 100 )
for _,v in ipairs( values ) do
  chart2:add( v, nil, fl.BLUE )
end
retb.user_data = chart2

window:end_group()
window:show( arg )
fl.run()

