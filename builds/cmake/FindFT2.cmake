# FindFT2.cmake
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
#   FT2_INCLUDE_DIRS
#   FT2_LIBRARY_DIRS
#   FT2_LIBRARIES

find_package(PkgConfig QUIET)
pkg_check_modules(PC_FT2 QUIET FT2)


#
set(FT2_NAME freetype)
find_path(
  FT2_DIRS
  NAMES ${FT2_NAME}
  HINTS ${DEPS_DIRS}
  NO_DEFAULT_PATH
)

if (FT2_DIRS)
  set(FT2_DIRS ${FT2_DIRS}/${FT2_NAME})

  set(FT2_INCLUDE_DIRS ${FT2_DIRS}/include)
  set(FT2_LIBRARY_DIRS ${FT2_DIRS}/build)

  find_library(
    FT2_LIBRARIES
    NAMES libfreetype.a
    HINTS ${FT2_LIBRARY_DIRS}
    REQUIRED
    NO_DEFAULT_PATH
  )

  if (FT2_LIBRARIES)
    include(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(
      FT2
      REQUIRED_VARS FT2_INCLUDE_DIRS FT2_LIBRARIES
      FOUND_VAR FT2_FOUND
      VERSION_VAR FT2_VERSION)
  endif()
endif()


mark_as_advanced(
  FT2_INCLUDE_DIRS
  FT2_LIBRARY_DIRS
  FT2_LIBRARIES)


#[[
if (FT2_FOUND)
  message(STATUS "FT2_VERSION: ${FT2_VERSION}")

  message(STATUS "FT2_DIRS: ${FT2_DIRS}")

  message(STATUS "FT2_INCLUDE_DIRS: ${FT2_INCLUDE_DIRS}")
  message(STATUS "FT2_LIBRARY_DIRS: ${FT2_LIBRARY_DIRS}")

  message(STATUS "FT2_LIBRARIES: ${FT2_LIBRARIES}")

  include_directories(${FT2_INCLUDE_DIRS})

  link_directories(${FT2_LIBRARY_DIRS})
  target_link_libraries(${PROJECT_NAME} ${FT2_LIBRARIES})
endif ()
]]