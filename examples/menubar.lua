#!/usr/bin/env lua

local unpack = table.unpack or unpack

local fl = require( "fltk4lua" )
local WIDTH=700
local window = fl.Window( WIDTH, 400 )
function window:callback()
  print( "window callback called" )
  self:hide()
end

local hugemenu = {}

local function quit_cb()
  --os.exit( 0, true ) -- bad style
  window:hide()
end

local menutable = {
  { "foo", nil, nil, nil, fl.MENU_INACTIVE },
  { "&File", nil, nil, nil, fl.SUBMENU },
    { "&Open", fl.ALT+'o', nil, nil, fl.MENU_INACTIVE },
    { "&Close" },
    { "&Quit", fl.ALT+'q', quit_cb, nil, fl.MENU_DIVIDER },
    { "shortcut", 'a' },
    { "shortcut", fl.SHIFT+'a' },
    { "shortcut", fl.CTRL+'a' },
    { "shortcut", fl.CTRL+fl.SHIFT+'a' },
    { "shortcut", fl.ALT+'a' },
    { "shortcut", fl.ALT+fl.SHIFT+'a' },
    { "shortcut", fl.ALT+fl.CTRL+'a' },
    { "shortcut", fl.ALT+fl.SHIFT+fl.CTRL+'a', nil, nil, fl.MENU_DIVIDER },
    { "shortcut", '\r' --[[ fl.Enter ]] },
    { "shortcut", fl.CTRL+fl.Enter, nil, nil, fl.MENU_DIVIDER },
    { "shortcut", fl.F1 },
    { "shortcut", fl.SHIFT+fl.F1 },
    { "shortcut", fl.CTRL+fl.F1 },
    { "shortcut", fl.SHIFT+fl.CTRL+fl.F1 },
    { "shortcut", fl.ALT+fl.F1 },
    { "shortcut", fl.ALT+fl.SHIFT+fl.F1 },
    { "shortcut", fl.ALT+fl.CTRL+fl.F1 },
    { "shortcut", fl.ALT+fl.SHIFT+fl.CTRL+fl.F1, nil, nil, fl.MENU_DIVIDER },
    { "&Submenus", fl.ALT+'S', nil, "Submenu1", fl.SUBMENU },
      { "A very long menu item" },
      { "&submenu", fl.CTRL+'S', nil, "Submenu2", fl.SUBMENU },
        { "item 1" },
        { "item 2" },
        { "item 3" },
        { "item 4" },
        {},
      { "after submenu" },
      {},
    {},
  { "&Edit", fl.F2, nil, nil, fl.SUBMENU },
    { "Undo", fl.ALT+'z' },
    { "Redo", fl.ALT+'r', nil, nil, fl.MENU_DIVIDER },
    { "Cut", fl.ALT+'x' },
    { "Copy", fl.ALT+'c' },
    { "Paste", fl.ALT+'v' },
    { "Inactive", fl.ALT+'d', nil, nil, fl.MENU_INACTIVE },
    { "Clear", nil, nil, nil, fl.MENU_DIVIDER },
    { "Invisible", fl.ALT+'e', nil, nil, fl.MENU_INVISIBLE },
    { "Preferences" },
    { "Size" },
    {},
  { "&Checkbox", fl.F3, nil, nil, fl.SUBMENU },
    { "&Alpha", fl.F2, nil, 1, fl.MENU_TOGGLE },
    { "&Beta", nil, nil, 2, fl.MENU_TOGGLE },
    { "&Gamma", nil, nil, 3, fl.MENU_TOGGLE },
    { "&Delta", nil, nil, 4, fl.MENU_TOGGLE+fl.MENU_VALUE },
    { "&Epsilon", nil, nil, 5, fl.MENU_TOGGLE },
    { "&Pi", nil, nil, 6, fl.MENU_TOGGLE },
    { "&Mu", nil, nil, 7, fl.MENU_TOGGLE+fl.MENU_DIVIDER },
    { "Red", nil, nil, 1, fl.MENU_TOGGLE, nil, nil, nil, 1 },
    { "Black", nil, nil, 1, fl.MENU_TOGGLE+fl.MENU_DIVIDER },
    { "00", nil, nil, 1, fl.MENU_TOGGLE },
    { "000", nil, nil, 1, fl.MENU_TOGGLE },
    {},
  { "&Radio", nil, nil, nil, fl.SUBMENU },
    { "&Alpha", nil, nil, 1, fl.MENU_RADIO },
    { "&Beta", nil, nil, 2, fl.MENU_RADIO },
    { "&Gamma", nil, nil, 3, fl.MENU_RADIO },
    { "&Delta", nil, nil, 4, fl.MENU_RADIO+fl.MENU_VALUE },
    { "&Epsilon", nil, nil, 5, fl.MENU_RADIO },
    { "&Pi", nil, nil, 6, fl.MENU_RADIO },
    { "&Mu", nil, nil, 7, fl.MENU_RADIO+fl.MENU_DIVIDER },
    { "Red", nil, nil, 1, fl.MENU_RADIO },
    { "Black", nil, nil, 1, fl.MENU_RADIO+fl.MENU_DIVIDER },
    { "00", nil, nil, 1, fl.MENU_RADIO },
    { "000", nil, nil, 1, fl.MENU_RADIO },
    {},
  { "&Font", nil, nil, nil, fl.SUBMENU },
    { "Normal", nil, nil, nil, nil, nil, nil, 14 },
    { "Bold", nil, nil, nil, nil, nil, "FL_HELVETICA_BOLD", 14 },
    { "Italic", nil, nil, nil, nil, nil, "FL_HELVETICA_ITALIC", 14 },
    { "BoldItalic", nil, nil, nil, nil, nil, "FL_HELVETICA_BOLD_ITALIC", 14 },
    { "Small", nil, nil, nil, nil, nil, "FL_HELVETICA_BOLD_ITALIC", 10 },
    { "Emboss", nil, nil, nil, nil, "FL_EMBOSSED_LABEL" },
    { "Engrave", nil, nil, nil, nil, "FL_ENGRAVED_LABEL" },
    { "Shadow", nil, nil, nil, nil, "FL_SHADOW_LABEL" },
    { "@->", nil, nil, nil, nil, "FL_NORMAL_LABEL" },
    {},
  { "&International", nil, nil, nil, fl.SUBMENU },
    { "Sharp Ess", 223 },
    { "A Umlaut", 196 },
    { "a Umlaut", 228 },
    { "Euro currency", fl.COMMAND+8364 },
    { "the &\195\188 Umlaut" },
    { "the capital &\195\156" },
    { "convert \194\165 to &\194\163" },
    { "convert \194\165 to &\226\130\172" },
    { "Hangul character Sios &\227\133\133" },
    { "Hangul character Cieuc", 12616 },
    {},
  { "E&mpty", nil, nil, nil, fl.SUBMENU },
    {},
  { "&Inactive", nil, nil, nil, fl.MENU_INACTIVE+fl.SUBMENU },
    { "A very long menu item" },
    { "A very long menu item" },
    {},
  { "Invisible", nil, nil, nil, fl.MENU_INVISIBLE+fl.SUBMENU },
    { "A very long menu item" },
    { "A very long menu item" },
    {},
  { "&Huge", nil, nil, hugemenu, fl.SUBMENU }, -- fake SUBMENU_POINTER support!
  { "button", fl.F4, nil, nil, fl.MENU_TOGGLE },
  {}
}

local pulldown = {
  { "Red", fl.ALT+'r' },
  { "Green", fl.ALT+'g' },
  { "Blue", fl.ALT+'b' },
  { "Strange", fl.ALT+'s', nil, nil, fl.MENU_INACTIVE },
  { "&Charm", fl.ALT+'c' },
  { "Truth", fl.ALT+'t' },
  { "Beauty", fl.ALT+'b' },
}

for i = 1, 99 do
  hugemenu[ i ] = { "item "..(i-1) }
end

-- a function that takes a literal menu specification like in the
-- c++ code
local function Menu( m, t, stack, n_stack )
  stack, n_stack = stack or {}, n_stack or 0
  local flag_stack = {}
  for _,v in ipairs( t ) do
    local label, sc, cb, ud, flg, lt, lf, ls, lc = unpack( v )
    if label == nil or label == 0 then
      n_stack = n_stack - 1
      local flags = flag_stack[ #flag_stack ]
      if flags then
        m:menuitem_setp( flags[ 1 ], "flags", flags[ 2 ] )
        flag_stack[ #flag_stack ] = nil
      end
    else
      local i
      -- use a temporary name and rename later, because m:add()
      -- replaces existing menu items with the same name
      stack[ n_stack+1 ] = "++abc++"
      local path = table.concat( stack, "/", 1, n_stack+1 )
      if flg and flg( fl.SUBMENU ) then
        -- add a dummy menu entry and remove it later to create the
        -- submenu implicitly. explicit submenu creation is disabled
        -- for m:add() because of a bug in FLTK.
        i = m:add( path.."/++xyz++" )
        m:remove( i )
        i = m:find_index( path )
        if type( ud ) ~= "table" then
          m:menuitem_setp( i, "user_data", ud )
          n_stack = n_stack + 1
          stack[ n_stack ] = label
        else -- fake FL_SUBMENU_POINTER support
          m:menuitem_setp( i, "label", label )
          stack[ n_stack+1 ] = label
          Menu( m, ud, stack, n_stack+1 )
        end
        m:menuitem_setp( i, "shortcut", sc or 0 )
        m:menuitem_setp( i, "callback", cb )
        -- apply FL_MENU_INVISIBLE flag later
        m:menuitem_setp( i, "flags", flg-fl.MENU_INVISIBLE )
        flag_stack[ #flag_stack+1 ] = { i, flg }
      else
        i = m:add( path, sc, cb, ud, flg )
      end
      m:menuitem_setp( i, "label", label )
      if lt then
        m:menuitem_setp( i, "labeltype", lt )
      end
      if lf then
        m:menuitem_setp( i, "labelfont", lf )
      end
      if ls then
        m:menuitem_setp( i, "labelsize", ls )
      end
      if lc then
        m:menuitem_setp( i, "labelcolor", lc )
      end
    end
  end
end

local function test_cb( self )
  local m = self.value
  if not m then
    print( "NULL" )
  else
    local lb = self:menuitem_getp( m, "label" )
    local sc = self:menuitem_getp( m, "shortcut" )
    if sc-sc ~= sc then -- test for 0
      print( lb.." - "..fl.shortcut_label( sc ) )
    else
      print( lb )
    end
  end
end

local menubar = fl.Menu_Bar( 0, 0, WIDTH, 30 )
menubar.callback = test_cb
Menu( menubar, menutable )

local mb1 = fl.Menu_Button( 100, 100, 120, 25, "&menubutton" )
Menu( mb1, pulldown )
mb1.tooltip = "this is a menu button"
mb1.callback = test_cb

local ch = fl.Choice( 300, 100, 80, 25, "&choice:" )
Menu( ch, pulldown )
ch.tooltip = "this is a choice menu"
ch.callback = test_cb
ch.value = 0

local mb2 = fl.Menu_Button( 0, 0, WIDTH, 400, "&popup" )
mb2.type = "POPUP3"
mb2.box = "FL_NO_BOX"
Menu( mb2, menutable )
mb2:remove( 1 ) -- delete the "File" submenu
mb2.callback = test_cb

local b = fl.Box( 200, 200, 200, 100, "Press right button\nfor a pop-up menu" )
window.resizable = mb2
window:size_range( 300, 400, 0, 400 )
window:end_group()
window:show( arg )
fl.run()

