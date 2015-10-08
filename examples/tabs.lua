#!/usr/bin/env lua

local fl = require( "fltk4lua" )
local window = fl.Window{
  642, 340, "Comparison of Fl_Tab (left) vs. Fl_Wizard (right)"
}
local wizard -- forward declaration

local function cb_button1()
  fl.message( "Test to see if this modal window prevents you from "..
              "changing the tabs. It should." )
end
local function cb_test()
  fl.message( "Make sure you cannot change the tabs while this "..
              "modal window is up" )
end
local function cb_0()
  wizard.value = wizard:child( 0 )
end
local function cb_1()
  wizard:prev()
end
local function cb_2()
  wizard:next()
end
local function cb_3()
  local last = wizard.children-1
  wizard.value = wizard:child( last )
end
local function cb_cancel()
  os.exit( 1, true )
end
local function cb_ok()
  --os.exit( 0, true ) -- bad style!
  window:hide()
end

do
  fl.Box{
    95, 0, 130, 35, "class Fl_Tabs",
    labeltype="FL_ENGRAVED_LABEL", labelfont=1,
  }
  local tabs = fl.Tabs{
    10, 35, 300, 205,
    tooltip="the various index cards test different aspects of the Fl_Tabs widget",
    selection_color=4, labelcolor=fl.BACKGROUND2_COLOR,
  }
  do
    local o = fl.Group{
      10, 60, 300, 180, "Label&1",
      tooltip="this Tab tests correct keyboard navigation between text input fields",
      selection_color=1,
    }
    fl.Input{
      60, 80, 240, 40, "input:",
      tooltip="This is the first input field",
    }
    fl.Input( 60, 120, 240, 30, "input2:" )
    fl.Input( 60, 150, 240, 80, "input3:" )
    o:end_group()
    fl.Group.current().resizable = o
  end
  do
    local o = fl.Group{
      10, 60, 300, 180, "tab&2",
      tooltip="tab2 tests among other things the cooperation of modal windows and tabs",
      selection_color=2
    }
    o:hide()
    fl.Button{
      20, 90, 100, 30, "button1",
      callback=cb_button1,
    }
    fl.Input( 140, 130, 100, 30, "input in box2" )
    fl.Button( 30, 170, 260, 30, "This is stuff inside the Fl_Group \"tab2\"" )
    fl.Button{
      30, 200, 260, 30, "Test event blocking by modal window",
      callback=cb_test,
    }
    o:end_group()
  end
  do
    local o = fl.Group{
      10, 60, 300, 180, "tab&3",
      tooltip="tab3 checks for correct keyboard navigation",
      selection_color=3,
    }
    o:hide()
    fl.Button( 20, 90, 60, 80, "button2" )
    fl.Button( 80, 90, 60, 80, "button" )
    fl.Button( 140, 90, 60, 80, "button" )
    o:end_group()
  end
  do
    local o = fl.Group{
      10, 60, 300, 180, "&tab4",
      tooltip="this tab shows the issue of indicating a selected "..
              "tab if the tab layouts are very similar",
      selection_color=5, labeltype="FL_ENGRAVED_LABEL", labelfont=2,
    }
    o:hide()
    fl.Button( 20, 80, 60, 110, "button2" )
    fl.Button( 80, 80, 60, 110, "button" )
    fl.Button( 140, 80, 60, 110, "button" )
    o:end_group()
  end
  do
    local o = fl.Group{
      10, 60, 300, 180, "@fileprint  &print",
      tooltip="tab5 verifies if visibility requests are handled correctly",
    }
    o:hide()
    fl.Button{
      20, 75, 60, 80, "button2",
      tooltip="button 2 has a different tooltip than tab5",
    }
    fl.Button( 90, 75, 60, 80, "button" )
    fl.Clock{
      160, 75, 100, 100,
      "Make sure this clock does not use processor time when this "..
      "tab is hidden or window is iconized",
      box="FL_OSHADOW_BOX", color=238, selection_color=fl.FOREGROUND_COLOR,
      labelfont=8, labelsize=10, align=fl.ALIGN_WRAP+fl.ALIGN_BOTTOM,
    }
    fl.Window{
      20, 175, 40, 55,
      box="FL_THIN_DOWN_BOX", color=173, selection_color=fl.BACKGROUND_COLOR,
      labeltype="FL_NORMAL_LABEL", labelfont=0, labelsize=14,
      labelcolor=fl.FOREGROUND_COLOR, align=fl.ALIGN_CENTER+fl.ALIGN_INSIDE,
      when=fl.WHEN_RELEASE,
    }:end_group()
    fl.Window{
      65, 175, 40, 55, "subwindows:",
      box="FL_THIN_DOWN_BOX", color=167, selection_color=fl.BACKGROUND_COLOR,
      labeltype="FL_NORMAL_LABEL", labelfont=0, labelsize=14,
      labelcolor=fl.FOREGROUND_COLOR, align=fl.ALIGN_TOP,
      when=fl.WHEN_RELEASE,
    }:end_group()
    fl.Window{
      110, 175, 40, 55,
      box="FL_THIN_DOWN_BOX", color=239, selection_color=fl.BACKGROUND_COLOR,
      labeltype="FL_NORMAL_LABEL", labelfont=0, labelsize=14,
      labelcolor=fl.FOREGROUND_COLOR, align=fl.ALIGN_CENTER+fl.ALIGN_INSIDE,
      when=fl.WHEN_RELEASE,
    }:end_group()
    o:end_group()
  end
  tabs:end_group()
  -- looks bad with a tiling window manager:
  --fl.Group.current().resizable = tabs
end
do
  fl.Box{
    410, 0, 130, 35, "class Fl_Wizard",
    labeltype="FL_ENGRAVED_LABEL", labelfont=1,
  }
  wizard = fl.Wizard( 325, 60, 300, 180 )
  do
    local o = fl.Group{
      325, 60, 300, 180, "Label1",
      tooltip="this Tab tests correct keyboard navigation between "..
              "text input fields",
      selection_color=1,
    }
    fl.Input{
      375, 80, 240, 40, "input:",
      tooltip="This is the first input field",
    }
    fl.Input( 375, 120, 240, 30, "input2:" )
    fl.Input( 375, 150, 240, 30, "input3:" )
    o:end_group()
    fl.Group.current().resizable = o
  end
  do
    local o = fl.Group{
      325, 60, 300, 180, "tab2",
      tooltip="tab2 tests among other things the cooperation of modal windows and tabs",
      selection_color=2,
    }
    o:hide()
    fl.Button{
      335, 90, 100, 30, "button1",
      callback=cb_button1,
    }
    fl.Input( 455, 130, 100, 30, "input in box2" )
    fl.Button( 345, 170, 260, 30, "This is stuff inside the Fl_Group \"tab2\"" )
    fl.Button{
      345, 200, 260, 30, "Test event blocking by modal window",
      callback=cb_test,
    }
    o:end_group()
  end
  do
    local o = fl.Group{
      325, 60, 300, 180, "tab3",
      tooltip="tab3 checks for correct keyboard navigation",
      selection_color=3,
    }
    o:hide()
    fl.Button( 335, 90, 60, 80, "button2" )
    fl.Button( 395, 90, 60, 80, "button" )
    fl.Button( 455, 90, 60, 80, "button" )
    o:end_group()
  end
  do
    local o = fl.Group{
      325, 60, 300, 180, "tab4",
      tooltip="this tab shows the issue of indicating a selected "..
              "tab if the tab layouts are very similar",
      selection_color=5, labelfont=2,
    }
    o:hide()
    fl.Button( 335, 80, 60, 110, "button2" )
    fl.Button( 395, 80, 60, 110, "button" )
    fl.Button( 455, 80, 60, 110, "button" )
    o:end_group()
  end
  do
    local o = fl.Group{
      325, 60, 300, 180, "     tab5     ",
      tooltip="tab5 verifies if visibility requests are handled correctly",
      labeltype="FL_ENGRAVED_LABEL",
    }
    o:hide()
    fl.Button{
      335, 75, 60, 80, "button2",
      tooltip="button 2 has a different tooltip than tab5",
    }
    fl.Button( 405, 75, 60, 80, "button" )
    fl.Clock{
      475, 75, 100, 100,
      "Make sure this clock does not use processor time when this "..
      "tab is hidden or window is iconized",
      box="FL_OSHADOW_BOX", color=238, selection_color=fl.FOREGROUND_COLOR,
      labelfont=8, labelsize=10, align=fl.ALIGN_WRAP+fl.ALIGN_BOTTOM,
    }
    fl.Window{
      335, 175, 40, 55,
      box="FL_THIN_DOWN_BOX", color=173, selection_color=fl.BACKGROUND_COLOR,
      labeltype="FL_NORMAL_LABEL", labelfont=0, labelsize=14,
      labelcolor=fl.FOREGROUND_COLOR, align=fl.ALIGN_CENTER+fl.ALIGN_INSIDE,
      when=fl.WHEN_RELEASE,
    }:end_group()
    fl.Window{
      380, 175, 40, 55, "subwindows:",
      box="FL_THIN_DOWN_BOX", color=167, selection_color=fl.BACKGROUND_COLOR,
      labeltype="FL_NORMAL_LABEL", labelfont=0, labelsize=14,
      labelcolor=fl.FOREGROUND_COLOR, align=fl.ALIGN_TOP,
      when=fl.WHEN_RELEASE,
    }:end_group()
    fl.Window{
      425, 175, 40, 55,
      box="FL_THIN_DOWN_BOX", color=239, selection_color=fl.BACKGROUND_COLOR,
      labeltype="FL_NORMAL_LABEL", labelfont=0, labelsize=14,
      labelcolor=fl.FOREGROUND_COLOR, align=fl.ALIGN_CENTER+fl.ALIGN_INSIDE,
      when=fl.WHEN_RELEASE,
    }:end_group()
    o:end_group()
  end
  wizard:end_group()
end
do
  local o = fl.Group( 410, 245, 130, 25 )
  fl.Button{
    410, 245, 30, 25, "@|<",
    tooltip="go to first page [Home]",
    shortcut=fl.Home, callback=cb_0,
  }
  fl.Button{
    440, 245, 30, 25, "@<",
    tooltip="go to previous page [left arrow]",
    shortcut=fl.Left, callback=cb_1,
  }
  fl.Button{
    480, 245, 30, 25, "@>",
    tooltip="go to next page in wizard [right arrow]",
    shortcut=fl.Right, callback=cb_2,
  }
  fl.Button{
    510, 245, 30, 25, "@>|",
    tooltip="go to last page [End]",
    shortcut=fl.End, callback=cb_3,
  }
  o:end_group()
end
fl.Input( 60, 255, 130, 25, "inputA:" )
fl.Input( 60, 285, 250, 25, "inputB:" )
fl.Button{
  475, 295, 70, 30, "cancel",
  callback=cb_cancel,
}
fl.Return_Button{
  555, 295, 70, 30, "OK",
  callback=cb_ok,
}
window:end_group()
window:show( arg )
fl.run()

