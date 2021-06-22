# FindPNG.cmake
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
# Try to find PNG include and library directories.
#
# If found, the following variables are set.
#
#   PNG_INCLUDE_DIRS
#   PNG_LIBRARY_DIRS
#   PNG_LIBRARIES

find_package(PkgConfig QUIET)
pkg_check_modules(PC_PNG QUIET PNG)


#
set(PNG_NAME libpng-1.6.37)
find_path(
  PNG_DIRS
  NAMES ${PNG_NAME}
  HINTS ${DEPS_DIRS}
  NO_DEFAULT_PATH
)

if (PNG_DIRS)
  set(PNG_DIRS ${PNG_DIRS}/${PNG_NAME})

  set(PNG_INCLUDE_DIRS ${PNG_DIRS})
  set(PNG_LIBRARY_DIRS ${PNG_DIRS}/build)

  find_library(
    PNG_LIBRARIES
    NAMES libpng.a
    HINTS ${PNG_LIBRARY_DIRS}
    REQUIRED
    NO_DEFAULT_PATH
  )

  if (PNG_LIBRARIES)
    include(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(
      PNG
      REQUIRED_VARS PNG_INCLUDE_DIRS PNG_LIBRARIES
      FOUND_VAR PNG_FOUND
      VERSION_VAR PNG_VERSION)
  endif()
endif()

mark_as_advanced(
  PNG_INCLUDE_DIRS
  PNG_LIBRARY_DIRS
  PNG_LIBRARIES)


#[[
if (PNG_FOUND)
  message(STATUS "PNG_VERSION: ${PNG_VERSION}")

  message(STATUS "PNG_DIRS: ${PNG_DIRS}")

  message(STATUS "PNG_INCLUDE_DIRS: ${PNG_INCLUDE_DIRS}")
  message(STATUS "PNG_LIBRARY_DIRS: ${PNG_LIBRARY_DIRS}")
  message(STATUS "PNG_LIBRARIES: ${PNG_LIBRARIES}")

  include_directories(${PNG_INCLUDE_DIRS})

  link_directories(${PNG_LIBRARY_DIRS})
  target_link_libraries(${PROJECT_NAME} ${PNG_LIBRARIES})
endif ()
]]