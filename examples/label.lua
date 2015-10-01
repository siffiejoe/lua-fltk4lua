#!/usr/bin/env lua

local fl = require( "fltk4lua" )

-- blast.xpm is in the test/pixmaps sub-directory in the FLTK source
-- code. You'll need to copy it to this directory for this demo to
-- work correctly!
local img = fl.Shared_Image.get( "examples/blast.xpm" )
local window = fl.Window( 400, 400 )
local text -- forward declaration

local input = fl.Input{
  50, 375, 350, 25,
  value="The quick brown fox jumped over the lazy dog.",
  when=fl.WHEN_CHANGED
}
function input:callback()
  text.label = self.value
  window:redraw()
end

local sizes = fl.Value_Slider{
  50, 350, 350, 25, "Size:",
  type="FL_HORIZONTAL", align=fl.ALIGN_LEFT, step=1, value=14,
}
sizes:bounds( 1, 64 )
function sizes:callback()
  text.labelsize = self.value
  window:redraw()
end

local fonts = fl.Value_Slider{
  50, 325, 350, 25, "Font:",
  type="FL_HORIZONTAL", align=fl.ALIGN_LEFT, step=1, value=0,
}
fonts:bounds( 0, 15 )
function fonts:callback()
  text.labelfont = self.value
  window:redraw()
end

local g = fl.Group( 50, 275, 350, 50 )
local imageb = fl.Button{
  50, 275, 50, 25, "image", type="FL_TOGGLE_BUTTON",
}
function imageb:callback()
  if self.value then
    text.image = img
  else
    text.image = nil
  end
  window:redraw()
end
local buttons = {
  fl.Button{
    100, 275, 50, 25, "I - T", type="FL_TOGGLE_BUTTON",
    user_data=fl.ALIGN_TEXT_OVER_IMAGE,
  },
  fl.Button{
    150, 275, 50, 25, "I | T", type="FL_TOGGLE_BUTTON",
    user_data=fl.ALIGN_IMAGE_NEXT_TO_TEXT,
  },
  fl.Button{
    200, 275, 50, 25, "back", type="FL_TOGGLE_BUTTON",
    user_data=fl.ALIGN_IMAGE_BACKDROP,
  },
  fl.Button{
    50, 300, 50, 25, "left", type="FL_TOGGLE_BUTTON",
    user_data=fl.ALIGN_LEFT,
  },
  fl.Button{
    100, 300, 50, 25, "right", type="FL_TOGGLE_BUTTON",
    user_data=fl.ALIGN_RIGHT,
  },
  fl.Button{
    150, 300, 50, 25, "top", type="FL_TOGGLE_BUTTON",
    user_data=fl.ALIGN_TOP,
  },
  fl.Button{
    200, 300, 50, 25, "bottom", type="FL_TOGGLE_BUTTON",
    user_data=fl.ALIGN_BOTTOM,
  },
  fl.Button{
    250, 300, 50, 25, "inside", type="FL_TOGGLE_BUTTON",
    user_data=fl.ALIGN_INSIDE,
  },
  fl.Button{
    300, 300, 50, 25, "wrap", type="FL_TOGGLE_BUTTON",
    user_data=fl.ALIGN_WRAP,
  },
  fl.Button{
    350, 300, 50, 25, "clip", type="FL_TOGGLE_BUTTON",
    user_data=fl.ALIGN_CLIP,
  },
}
local function button_cb()
  local a = fl.ALIGN_CENTER -- 0
  for _,b in ipairs( buttons ) do
    if b.value then
      a = a + b.user_data
    end
  end
  text.align = a
  window:redraw()
end
for _,b in ipairs( buttons ) do
  b.callback = button_cb
end
g.resizable = buttons[ 8 ]
g:end_group()

local c = fl.Choice( 50, 250, 200, 25 )
local function choice_cb( self, v )
  if v == "FL_SYMBOL_LABEL" then
    v = "FL_NORMAL_LABEL"
    if not input.value:match( "^@" ) then
      input.value = "@->"
      text.label = "@->"
    end
  end
  text.labeltype = v
  window:redraw()
end
local labels = {
  "FL_NORMAL_LABEL", "FL_SYMBOL_LABEL", "FL_SHADOW_LABEL",
  "FL_ENGRAVED_LABEL", "FL_EMBOSSED_LABEL",
}
for _,v in ipairs( labels ) do
  c:add( v, 0, choice_cb, v )
end
c.value = 0

text = fl.Box{
  100, 75, 200, 100, input.value,
  box="FL_ENGRAVED_BOX", align=fl.ALIGN_CENTER,
}
window.resizable = text
window:end_group()
window:show( arg )
fl.run()

