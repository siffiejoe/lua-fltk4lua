package = "fltk4lua"
version = "scm-0"
source = {
  url = "gitrec+https://github.com/siffiejoe/lua-fltk4lua.git"
}
description = {
  summary = "Lua binding to FLTK, the Fast Light ToolKit",
  detailed = "Lua binding to FLTK, the Fast Light ToolKit",
  homepage = "https://github.com/siffiejoe/lua-fltk4lua/",
  license = "MIT+LGPL"
}
supported_platforms = { "unix", "windows" }
dependencies = {
  "lua >= 5.1, < 5.5",
  "luarocks-fetch-gitrec",
  "luarocks-build-cpp",
}
external_dependencies = {
  platforms = {
    windows = {
      FLTK = {
        header = "FL/Fl",
        library = "fltk"
      }
    },
    unix = {
      FLTK = {
        program = "fltk-config"
      }
    }
  }
}
build = {
  type = "make",
  variables = {
    DLL_INSTALL_DIR = "$(LIBDIR)",
    LUA_INCDIR = "$(LUA_INCDIR)",
    FLTK_CONFIG = "$(FLTK_BINDIR)/fltk-config",
    CXX = "g++",
    CFLAGS = "$(CFLAGS)",
    LIBFLAG = "$(LIBFLAG)",
    LIB_EXTENSION = "$(LIB_EXTENSION)",
  },
  copy_directories = {
    "doc", "examples"
  },
  platforms = {
    windows = {
      type = "cpp",
      modules = {
        ["fltk4lua"] = {
          sources = {
            "src/fltk4lua.cxx",
            "src/f4l_enums.cxx",
            "src/f4l_ask.cxx",
            "src/f4l_image.cxx",
            "src/f4l_shared_image.cxx",
            "src/f4l_widget.cxx",
            "src/f4l_box.cxx",
            "src/f4l_button.cxx",
            "src/f4l_chart.cxx",
            "src/f4l_clock.cxx",
            "src/f4l_group.cxx",
            "src/f4l_browserx.cxx",
            "src/f4l_browser.cxx",
            "src/f4l_file_browser.cxx",
            "src/f4l_check_browser.cxx",
            "src/f4l_input_choice.cxx",
            "src/f4l_color_chooser.cxx",
            "src/f4l_pack.cxx",
            "src/f4l_scroll.cxx",
            "src/f4l_spinner.cxx",
            "src/f4l_tabs.cxx",
            "src/f4l_tile.cxx",
            "src/f4l_window.cxx",
            "src/f4l_wizard.cxx",
            "src/f4l_input.cxx",
            "src/f4l_menu.cxx",
            "src/f4l_choice.cxx",
            "src/f4l_menu_bar.cxx",
            "src/f4l_menu_button.cxx",
            "src/f4l_progress.cxx",
            "src/f4l_valuator.cxx",
            "src/f4l_adjuster.cxx",
            "src/f4l_counter.cxx",
            "src/f4l_dial.cxx",
            "src/f4l_roller.cxx",
            "src/f4l_slider.cxx",
            "src/f4l_value_input.cxx",
            "src/f4l_value_output.cxx",
            "moon/moon.c",
            "compat-5.3/c-api/compat-5.3.c",
          },
          defines = {
            "MOON_PREFIX=f4lx",
            "COMPAT53_PREFIX=f4lx",
            "WIN32",
            "NDEBUG",
            "_CRT_SECURE_NO_WARNINGS"
          },
          libraries = {
            "fltk_images",
            "fltk_jpeg",
            "fltk_png",
            "fltk_z",
            "fltk",
            "advapi32",
            "comctl32",
            "gdi32",
            "ole32",
            "shell32",
            "user32",
            "uuid",
          },
          incdirs = {
            "$(FLTK_INCDIR)",
            "moon",
            "compat-5.3/c-api"
          },
          libdirs = { "$(FLTK_LIBDIR)" }
        }
      }
    }
  }
}

