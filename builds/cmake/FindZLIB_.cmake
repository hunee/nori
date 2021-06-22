# FindZLIB.cmake
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
# Try to find ZLIB include and library directories.
#
# If found, the following variables are set.
#
#   ZLIB_INCLUDE_DIRS
#   ZLIB_LIBRARY_DIRS
#   ZLIB_LIBRARIES

find_package(PkgConfig QUIET)
pkg_check_modules(PC_ZLIB QUIET ZLIB)


#
set(ZLIB_NAME zlib-1.2.11)
find_path(
  ZLIB_DIRS
  NAMES ${ZLIB_NAME}
  HINTS ${DEPS_DIRS}
  NO_DEFAULT_PATH
)

if (ZLIB_DIRS)
  set(ZLIB_DIRS ${ZLIB_DIRS}/${ZLIB_NAME})

  set(ZLIB_INCLUDE_DIRS ${ZLIB_DIRS})
  set(ZLIB_LIBRARY_DIRS ${ZLIB_DIRS}/build)

  find_library(
    ZLIB_LIBRARIES
    NAMES libz.a
    HINTS ${ZLIB_LIBRARY_DIRS}
    REQUIRED
    NO_DEFAULT_PATH
  )

  if (ZLIB_LIBRARIES)
    include(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(
      ZLIB
      REQUIRED_VARS ZLIB_INCLUDE_DIRS ZLIB_LIBRARIES
      FOUND_VAR ZLIB_FOUND
      VERSION_VAR ZLIB_VERSION)
  endif()
endif() #ZLIB_DIRS

#
mark_as_advanced(
  ZLIB_INCLUDE_DIRS
  ZLIB_LIBRARY_DIRS
  ZLIB_LIBRARIES)


#[[
if (ZLIB_FOUND)
  message(STATUS "ZLIB_VERSION: ${ZLIB_VERSION}")

  message(STATUS "ZLIB_DIRS: ${ZLIB_DIRS}")

  message(STATUS "ZLIB_INCLUDE_DIRS: ${ZLIB_INCLUDE_DIRS}")
  message(STATUS "ZLIB_LIBRARY_DIRS: ${ZLIB_LIBRARY_DIRS}")
  message(STATUS "ZLIB_LIBRARIES: ${ZLIB_LIBRARIES}")

  include_directories(${ZLIB_INCLUDE_DIRS})

  link_directories(${ZLIB_LIBRARY_DIRS})
  target_link_libraries(${PROJECT_NAME} ${ZLIB_LIBRARIES})
endif ()
]]