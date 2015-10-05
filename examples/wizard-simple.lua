#!/usr/bin/env lua

local fl = require( "fltk4lua" )
local win = fl.Window( 400, 300, "Example Wizard" )
local wiz = fl.Wizard( 0, 0, 400, 300 )

local function back_cb()
  wiz:prev()
end
local function next_cb()
  wiz:next()
end
local function done_cb()
  win:hide()
end

do
  local g = fl.Group( 0, 0, 400, 300 )
  local n = fl.Button( 290, 265, 100, 25, "Next @->" )
  n.callback = next_cb
  local o = fl.Input( 10, 30, 400-20, 300-80, "Welcome" )
  o.type = "FL_MULTILINE_OUTPUT"
  o.labelsize = 20
  o.align = fl.ALIGN_TOP + fl.ALIGN_LEFT
  o.value = "This is First page"
  g:end_group()
end
do
  local g = fl.Group( 0, 0, 400, 300 )
  local n = fl.Button( 290, 265, 100, 25, "Next @->" )
  n.callback = next_cb
  local b = fl.Button( 180, 265, 100, 25, "@<- Back" )
  b.callback = back_cb
  local o = fl.Input( 10, 30, 400-20, 300-80, "Terms And Conditions" )
  o.type = "FL_MULTILINE_OUTPUT"
  o.labelsize = 20
  o.align = fl.ALIGN_TOP + fl.ALIGN_LEFT
  o.value = "This is the Second page"
  g:end_group()
end
do
  local g = fl.Group( 0, 0, 400, 300 )
  local d = fl.Button( 290, 265, 100, 25, "Finish" )
  d.callback = done_cb
  local b = fl.Button( 180, 265, 100, 25, "@<- Back" )
  b.callback = back_cb
  local o = fl.Input( 10, 30, 400-20, 300-80, "Finish" )
  o.type = "FL_MULTILINE_OUTPUT"
  o.labelsize = 20
  o.align = fl.ALIGN_TOP + fl.ALIGN_LEFT
  o.value = "This is the Last page"
  g:end_group()
end
wiz:end_group()
win:end_group()
win:show( arg )
fl.run()

