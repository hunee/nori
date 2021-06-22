# FindGLFW.cmake
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
# Try to find GLFW include and library directories.
#
# If found, the following variables are set.
#
#   GLFW_INCLUDE_DIRS
#   GLFW_DEPS_DIRS
#   GLFW_LIBRARY_DIRS
#   GLFW_LIBRARIES

find_package(PkgConfig QUIET)
pkg_check_modules(PC_GLFW QUIET GLFW)


#
set(GLFW_NAME glfw)

find_path(GLFW_DIRS
  NAMES ${GLFW_NAME}
  HINTS ${DEPS_DIRS}
  NO_DEFAULT_PATH
)

if (GLFW_DIRS)
  set(GLFW_DIRS ${GLFW_DIRS}/${GLFW_NAME})

  set(GLFW_INCLUDE_DIRS ${GLFW_DIRS}/include)
  set(GLFW_DEPS_DIRS ${GLFW_DIRS}/deps)
  set(GLFW_LIBRARY_DIRS ${GLFW_DIRS}/build/src)

  find_library(
    GLFW_LIBRARIES
    NAMES libglfw3.a
    HINTS ${GLFW_LIBRARY_DIRS}
    REQUIRED
    NO_DEFAULT_PATH
  )

  if (GLFW_LIBRARIES)
    include(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(
      GLFW
      REQUIRED_VARS GLFW_INCLUDE_DIRS GLFW_LIBRARIES
      FOUND_VAR GLFW_FOUND
      VERSION_VAR GLFW_VERSION)
  endif()
endif() #GLFW_DIRS


mark_as_advanced(
  GLFW_INCLUDE_DIRS
  GLFW_DEPS_DIRS
  GLFW_LIBRARY_DIRS
  GLFW_LIBRARIES)


#[[
if (GLFW_FOUND)
  message(STATUS "GLFW_VERSION: ${GLFW_VERSION}")

  message(STATUS "GLFW_DIRS: ${GLFW_DIRS}")

  message(STATUS "GLFW_INCLUDE_DIRS: ${GLFW_INCLUDE_DIRS}")
  message(STATUS "GLFW_DEPS_DIRS: ${GLFW_DEPS_DIRS}")
  message(STATUS "GLFW_LIBRARY_DIRS: ${GLFW_LIBRARY_DIRS}")

  include_directories(${GLFW_INCLUDE_DIRS})
  include_directories(${GLFW_DEPS_DIRS})

  link_directories(${GLFW_LIBRARY_DIRS})
  target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARIES})
endif ()
]]