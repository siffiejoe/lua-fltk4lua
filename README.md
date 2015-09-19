#          fltk4lua -- Lua Binding to the Fast Light ToolKit         #

##                           Introduction                           ##

[FLTK][1] is a small C++ GUI toolkit portable to the MS Windows,
Linux, and Mac OSX operating systems. **fltk4lua** is a binding to
this C++ toolkit, which allows you to create GUIs from within Lua
scripts.

  [1]:  http://www.fltk.org/


##                           Documentation                          ##

Unfortunately, there is no documentation for **fltk4lua**, yet. The
Lua API is very close to the C++ API, so you can use the [official
FLTK documentation][2], and look at the examples or the source code.

In general there are the following differences between Lua API and C++
API (assuming you did a `local fl = require( "fltk4lua" )` at the top
of your Lua source file):

*   The prefixes of classes and functions have been removed, so use
    *   `fl.message()` instead of `fl_message()`
    *   `fl.run()` instead of `Fl::run()`
    *   `fl.Box()` instead of `new Fl_Box()`
    *   `fl.ALIGN_CENTER` instead of `FL_ALIGN_CENTER` (but see below).
*   Some `enum`s or preprocessor macros are translated to strings:
    *   `"FL_UP_BOX"` instead of `FL_UP_BOX`.
*   The remaining `enum`s/macros are available as userdata, so that
    you can combine them using bitwise operators (in Lua 5.3) or the
    following alternative operators:
    *   `local a = fl.ALIGN_TOP + fl.ALIGN_LEFT` instead of `Fl_Align
        a = FL_ALIGN_TOP | FL_ALIGN_LEFT;`
    *   `local a = b - fl.ALIGN_LEFT` instead of `Fl_Align a = b &
        (~FL_ALIGN_LEFT);` and
    *   `if a( fl.ALIGN_TOP ) then` instead of `if( a & FL_ALIGN_TOP )`.
*   C++ method calls are translated to Lua properties whenever
    possible, so use
    *   `b.box = "FL_UP_BOX"` instead of `b->box( FL_UP_BOX );` and
    *   `local bt = b.box` instead of `Fl_Boxtype bt = b->box();`.
*   Integers used as boolean values are translated to real `boolean`s.
*   `nil` is translated to `NULL` if `NULL` is allowed.
*   Output parameters end up as (multiple) return values.

  [2]:  http://www.fltk.org/doc-1.3/index.html


##                              Contact                             ##

Philipp Janda, siffiejoe(a)gmx.net

Comments and feedback are always welcome.


##                              License                             ##

`fltk4lua` is *copyrighted free software* distributed under the MIT
license (the same license as Lua 5.1). The full license text follows:

    fltk4lua (c) 2015 Philipp Janda

    Permission is hereby granted, free of charge, to any person obtaining
    a copy of this software and associated documentation files (the
    "Software"), to deal in the Software without restriction, including
    without limitation the rights to use, copy, modify, merge, publish,
    distribute, sublicense, and/or sell copies of the Software, and to
    permit persons to whom the Software is furnished to do so, subject to
    the following conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHOR OR COPYRIGHT HOLDER BE LIABLE FOR ANY
    CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
    SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

