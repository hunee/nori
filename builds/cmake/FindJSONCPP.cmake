# FindJSONCPP.cmake
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
# Try to find JSONCPP include and library directories.
#
# If found, the following variables are set.
#
#   JSONCPP_INCLUDE_DIRS
#   JSONCPP_LIBRARY_DIRS
#   JSONCPP_LIBRARIES

find_package(PkgConfig QUIET)
pkg_check_modules(PC_JSONCPP QUIET JSONCPP)


#
set(JSONCPP_NAME jsoncpp)
find_path(
  JSONCPP_DIRS
  NAMES ${JSONCPP_NAME}
  HINTS ${DEPS_DIRS}
  NO_DEFAULT_PATH
)

if (JSONCPP_DIRS)
  set(JSONCPP_DIRS ${JSONCPP_DIRS}/${JSONCPP_NAME})

  set(JSONCPP_INCLUDE_DIRS ${JSONCPP_DIRS}/include)
  set(JSONCPP_LIBRARY_DIRS ${JSONCPP_DIRS}/build/lib)

  find_library(
    JSONCPP_LIBRARIES
    NAMES libjsoncpp.a
    HINTS ${JSONCPP_LIBRARY_DIRS}
    REQUIRED
    NO_DEFAULT_PATH
  )

  if (JSONCPP_LIBRARIES)
    include(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(
      JSONCPP
      REQUIRED_VARS JSONCPP_INCLUDE_DIRS JSONCPP_LIBRARIES
      FOUND_VAR JSONCPP_FOUND
      VERSION_VAR JSONCPP_VERSION)
  endif()
endif()


mark_as_advanced(
  JSONCPP_INCLUDE_DIRS
  JSONCPP_LIBRARY_DIRS
  JSONCPP_LIBRARIES)


#[[
if (JSONCPP_FOUND)
  message(STATUS "JSONCPP_VERSION: ${JSONCPP_VERSION}")

  message(STATUS "JSONCPP_DIRS: ${JSONCPP_DIRS}")

  message(STATUS "JSONCPP_INCLUDE_DIRS: ${JSONCPP_INCLUDE_DIRS}")
  message(STATUS "JSONCPP_LIBRARY_DIRS: ${JSONCPP_LIBRARY_DIRS}")

  message(STATUS "JSONCPP_LIBRARIES: ${JSONCPP_LIBRARIES}")

  include_directories(${JSONCPP_INCLUDE_DIRS})

  link_directories(${JSONCPP_LIBRARY_DIRS})
  target_link_libraries(${PROJECT_NAME} ${JSONCPP_LIBRARIES})
endif ()
]]