#!/usr/bin/env lua

local dir = "examples"
local dirsep = package.config:sub( 1, 1 )
local exe, i = arg[ 0 ], -1
while arg[ i ] do
  exe, i = arg[ i ], i - 1
end

local fl = require( "fltk4lua" )
local window = fl.Window( 400, 400 )
local fbrowser = fl.File_Browser( 0, 0, 400, 400, "Select Example:" )
fbrowser.filter = "*.lua"
fbrowser.type = "FL_SELECT_BROWSER"
function fbrowser:callback()
  local fname = self:text( self.value )
  print( self.value, fname )
  self:deactivate()
  fl.check()
  if not fname:match( "[/\\]$" ) then
    print( os.execute( exe.." \""..dir..dirsep..fname.."\"" ) )
  end
  fl.check()
  self:activate()
end
assert( fbrowser:load( dir, "fl_alphasort" ) )
window:end_group()
window:show( arg )
fl.run()

