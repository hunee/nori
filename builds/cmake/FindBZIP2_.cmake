# FindBZIP2.cmake
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
# Try to find BZIP2 include and library directories.
#
# If found, the following variables are set.
#
#   BZIP2_INCLUDE_DIRS
#   BZIP2_LIBRARY_DIRS
#   BZIP2_LIBRARIES

find_package(PkgConfig QUIET)
pkg_check_modules(PC_BZIP2 QUIET BZIP2)


#
set(BZIP2_NAME bzip2)
find_path(
  BZIP2_DIRS
  NAMES ${BZIP2_NAME}
  HINTS ${DEPS_DIRS}
  NO_DEFAULT_PATH
)

if (BZIP2_DIRS)
  set(BZIP2_DIRS ${BZIP2_DIRS}/${BZIP2_NAME})

  set(BZIP2_INCLUDE_DIRS ${BZIP2_DIRS})
  set(BZIP2_LIBRARY_DIRS ${BZIP2_DIRS}/build)

  find_library(
    BZIP2_LIBRARIES
    NAMES libBZIP2.a
    HINTS ${BZIP2_LIBRARY_DIRS}
    REQUIRED
    NO_DEFAULT_PATH
  )

  if (BZIP2_LIBRARIES)
    include(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(
      BZIP2
      REQUIRED_VARS BZIP2_INCLUDE_DIRS BZIP2_LIBRARIES
      FOUND_VAR BZIP2_FOUND
      VERSION_VAR BZIP2_VERSION)
  endif()
endif()


mark_as_advanced(
  BZIP2_INCLUDE_DIRS
  BZIP2_LIBRARY_DIRS
  BZIP2_LIBRARIES)


#[[
if (BZIP2_FOUND)
  message(STATUS "BZIP2_VERSION: ${BZIP2_VERSION}")

  message(STATUS "BZIP2_DIRS: ${BZIP2_DIRS}")

  message(STATUS "BZIP2_INCLUDE_DIRS: ${BZIP2_INCLUDE_DIRS}")
  message(STATUS "BZIP2_LIBRARY_DIRS: ${BZIP2_LIBRARY_DIRS}")
  message(STATUS "BZIP2_LIBRARIES: ${BZIP2_LIBRARIES}")

  include_directories(${BZIP2_INCLUDE_DIRS})

  link_directories(${BZIP2_LIBRARY_DIRS})
  target_link_libraries(${PROJECT_NAME} ${BZIP2_LIBRARIES})
endif ()
]]