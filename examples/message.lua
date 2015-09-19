#!/usr/bin/env lua

local fl = require( "fltk4lua" )
local fmt = string.format

fl.args( arg )
fl.get_system_colors()

fl.message( fmt( "Spelling check successful, %d errors found with %g%% confidence",
                 1002, 100*(15/77.0) ) )
fl.alert( fmt( [[
Quantum fluctuations in the space-time continuum detected,
you have %g seconds to comply.
"In physics, spacetime is any mathematical model that combines
space and time into a single construct called the space-time
continuum. Spacetime is usually interpreted with space being
three-dimensional and time playing the role of the
fourth dimension." - Wikipedia]], 10.0 ) )

print( "fl_choice returned "..fl.choice( fmt( "Do you really want to %s?", "continue" ),
                                         "No", "Yes" ) )

print( "fl_choice returned "..fl.choice( "Choose one of the following:",
                                        "choice0", "choice1", "choice2" ) )
print( "fl_input returned "..tostring( fl.input( fmt( "Please enter a string for '%s':", "testing" ),
                                                 "this is the default value" ) ) )
print( "fl_password returned \""..tostring( fl.password( fmt( "Enter %s's password:", "somebody" ) ) ).."\"" )

