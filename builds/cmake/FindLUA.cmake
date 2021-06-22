# FindLUA.cmake
#
# Copyright (C) 2019-2021 by
# David Turner, Robert Wilhelm, and Werner Lemberg.
#
# Written by Werner Lemberg <wl@gnu.org>
#
# This file is part of the FreeType project, and may only be used, modified,
# and distributed under the terms of the FreeType project license,
# LICENSE.TXT.  By continuing to use, modify, or distribute this file you
# indicate that you have read the license and understand and accept it
# fully.
#
#
# Try to find LUA include and library directories.
#
# If found, the following variables are set.
#
#   LUA_INCLUDE_DIRS
#   LUA_LIBRARY_DIRS
#   LUA_LIBRARIES

find_package(PkgConfig QUIET)
pkg_check_modules(PC_LUA QUIET LUA)


set(LUA_NAME lua)
find_path(
  LUA_DIRS
  NAMES ${LUA_NAME}
  HINTS ${DEPS_DIRS}
  NO_DEFAULT_PATH
)

if (LUA_DIRS)
  set(LUA_DIRS ${LUA_DIRS}/${LUA_NAME})

  set(LUA_INCLUDE_DIRS ${LUA_DIRS})
  set(LUA_LIBRARY_DIRS ${LUA_DIRS})

  find_library(
    LUA_LIBRARIES
    NAMES liblua.a
    HINTS ${LUA_LIBRARY_DIRS}
    REQUIRED
    NO_DEFAULT_PATH
  )

  if (LUA_LIBRARIES)
    include(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(
      LUA
      REQUIRED_VARS LUA_INCLUDE_DIRS LUA_LIBRARIES
      FOUND_VAR LUA_FOUND
      VERSION_VAR LUA_VERSION)
  endif()
endif() #LUA_DIRS


mark_as_advanced(
  LUA_INCLUDE_DIRS
  LUA_LIBRARY_DIRS
  LUA_LIBRARIES)


#[[
if (LUA_FOUND)
  message(STATUS "LUA_VERSION: ${LUA_VERSION}")

  message(STATUS "LUA_DIRS: ${LUA_DIRS}")

  message(STATUS "LUA_INCLUDE_DIRS: ${LUA_INCLUDE_DIRS}")
  message(STATUS "LUA_LIBRARY_DIRS: ${LUA_LIBRARY_DIRS}")
  message(STATUS "LUA_LIBRARIES: ${LUA_LIBRARIES}")

  include_directories(${LUA_INCLUDE_DIRS})

  link_directories(${LUA_LIBRARY_DIRS})
  target_link_libraries(${PROJECT_NAME} ${LUA_LIBRARIES})
endif ()
]]