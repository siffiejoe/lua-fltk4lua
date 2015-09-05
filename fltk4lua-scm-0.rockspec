package = "fltk4lua"
version = "scm-0"
source = {
  url = "..."
}
description = {
  summary = "Lua binding to FLTK, the Fast Light ToolKit",
  detailed = "Lua binding to FLTK, the Fast Light ToolKit",
  homepage = "...",
  license = "MIT"
}
dependencies = {
  "lua >= 5.1, < 5.4",
  "luarocks-fetch-gitrec",
}
external_dependencies = {
  FLTK = {
    program = "fltk-config"
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
  }
}

