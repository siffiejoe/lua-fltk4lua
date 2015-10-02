#!/usr/bin/env lua

local fl = require( "fltk4lua" )
local window = fl.Window( 420, 370 )
local the_group = fl.Group{
  25, 25, 375, 295, "activate()/deactivate() called on this Fl_Group",
  box="FL_ENGRAVED_FRAME", align=fl.ALIGN_TOP+fl.ALIGN_INSIDE,
}
fl.Button( 50, 50, 105, 25, "button" )
fl.Light_Button{
  50, 80, 105, 25, "light button",
  value=true, align=fl.ALIGN_CENTER+fl.ALIGN_INSIDE,
}
do
  local g = fl.Group{
    50, 130, 105, 125, "Child group", box="FL_DOWN_FRAME",
  }
  fl.Check_Button{
    50, 170, 105, 25, "red",
    type="FL_RADIO_BUTTON", down_box="FL_DIAMOND_DOWN_BOX",
    selection_color=1, labelcolor=1,
  }
  fl.Check_Button{
    50, 190, 105, 25, "green",
    type="FL_RADIO_BUTTON", down_box="FL_DIAMOND_DOWN_BOX",
    selection_color=2, labelcolor=2,
  }
  fl.Check_Button{
    50, 210, 105, 25, "blue",
    type="FL_RADIO_BUTTON", down_box="FL_DIAMOND_DOWN_BOX",
    selection_color=4, labelcolor=4,
  }
  fl.Check_Button{
    50, 230, 105, 25, "white",
    type="FL_RADIO_BUTTON", down_box="FL_DIAMOND_DOWN_BOX",
    selection_color=55, labelcolor=55,
  }
  fl.Check_Button{
    50, 130, 105, 25, "check", down_box="FL_DOWN_BOX",
  }
  fl.Round_Button{
    50, 150, 105, 25, "round", down_box="FL_ROUND_DOWN_BOX",
  }
  g:end_group()
end
fl.Slider{
  165, 50, 24, 205, "Fl_Slider", value=0.5
}
fl.Input{
  195, 50, 195, 30, value="Fl_Input",
}
local mb = fl.Menu_Button( 245, 90, 130, 30, "menu" )
for i = 1, 5 do
  -- add() will replace existing menu items with the same name, so we
  -- rename after adding ...
  local i = mb:add( "XXX" )
  mb:menuitem_setp( i, "text", "item" )
  mb:menuitem_setp( i, "labelsize", 14 )
end
fl.Value_Output{
  245, 130, 130, 30, "value:",
  maximum=10000, step=1, textfont=5, textsize=24, textcolor=4,
}
fl.Box{
  245, 170, 140, 50, "Fl_Box",
  box="FL_EMBOSSED_FRAME", labeltype="FL_SHADOW_LABEL",
  labelfont=3, labelsize=38,
}
fl.Scrollbar{
  40, 275, 180, 20, "scrollbar", type="FL_HORIZONTAL",
}
fl.Roller( 235, 230, 25, 65, "roller" )
fl.Dial( 275, 235, 50, 50, "dial" )
fl.Clock( 335, 235, 50, 50, "clock" )
the_group:end_group()
--window.resizable = the_group -- looks bad with a tiling window manager
local ab = fl.Button{
  25, 330, 185, 25, "active", type="FL_RADIO_BUTTON", value=1,
}
function ab:callback()
  the_group:activate()
end
local ib = fl.Button{
  220, 330, 180, 25, "inactive", type="FL_RADIO_BUTTON"
}
function ib:callback()
  the_group:deactivate()
end
window:end_group()
window:show( arg )
fl.run()

