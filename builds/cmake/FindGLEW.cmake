# FindGLEW.cmake
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
# Try to find GLEW include and library directories.
#
# If found, the following variables are set.
#
#   GLEW_INCLUDE_DIRS
#   GLEW_LIBRARY_DIRS
#   GLEW_LIBRARIES

find_package(PkgConfig QUIET)
pkg_check_modules(PC_GLEW QUIET GLEW)


#
set(GLEW_NAME glew)
find_path(
  GLEW_DIRS
  NAMES ${GLEW_NAME}
  HINTS ${DEPS_DIRS}
  NO_DEFAULT_PATH
)

if (GLEW_DIRS)
  set(GLEW_DIRS ${GLEW_DIRS}/${GLEW_NAME})

  set(GLEW_INCLUDE_DIRS ${GLEW_DIRS}/include)
  set(GLEW_LIBRARY_DIRS ${GLEW_DIRS}/lib)

  find_library(
    GLEW_LIBRARIES
    NAMES libGLEW.a
    HINTS ${GLEW_LIBRARY_DIRS}
    REQUIRED
    NO_DEFAULT_PATH
  )

  if (GLEW_LIBRARIES)
    include(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(
      GLEW
      REQUIRED_VARS GLEW_INCLUDE_DIRS GLEW_LIBRARIES
      FOUND_VAR GLEW_FOUND
      VERSION_VAR GLEW_VERSION)
  endif()
endif() #GLEW_DIRS


mark_as_advanced(
  GLEW_INCLUDE_DIRS
  GLEW_LIBRARY_DIRS
  GLEW_LIBRARIES)


#[[
if (GLEW_FOUND)
  message(STATUS "GLEW_VERSION: ${GLEW_VERSION}")

  message(STATUS "GLEW_DIRS: ${GLEW_DIRS}")

  message(STATUS "GLEW_INCLUDE_DIRS: ${GLEW_INCLUDE_DIRS}")
  message(STATUS "GLEW_LIBRARY_DIRS: ${GLEW_LIBRARY_DIRS}")
  message(STATUS "GLEW_LIBRARIES: ${GLEW_LIBRARIES}")

  include_directories(${GLEW_INCLUDE_DIRS})

  link_directories(${GLEW_LIBRARY_DIRS})
  target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES})
endif ()
]]