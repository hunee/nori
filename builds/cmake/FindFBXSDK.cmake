# FindFBXSDK.cmake
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
# Try to find FBXSDK include and library directories.
#
# If found, the following variables are set.
#
#   FBXSDK_INCLUDE_DIRS
#   FBXSDK_LIBRARY_DIRS
#   FBXSDK_LIBRARIES

find_package(PkgConfig QUIET)
pkg_check_modules(PC_FBXSDK QUIET FBXSDK)


#
set(FBXSDK_NAME fbxsdk-2020.0.1)
find_path(
  FBXSDK_DIRS
  NAMES ${FBXSDK_NAME}
  HINTS ${DEPS_DIRS}
  NO_DEFAULT_PATH
)

if (FBXSDK_DIRS)
  set(FBXSDK_DIRS ${FBXSDK_DIRS}/${FBXSDK_NAME})

  set(FBXSDK_INCLUDE_DIRS ${FBXSDK_DIRS}/include)
  set(FBXSDK_LIBRARY_DIRS ${FBXSDK_DIRS}/lib/clang/release)

  find_library(
    FBXSDK_LIBRARIES
    NAMES libfbxsdk.a
    HINTS ${FBXSDK_LIBRARY_DIRS}
    REQUIRED
    NO_DEFAULT_PATH
  )

  if (FBXSDK_LIBRARIES)
    include(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(
      FBXSDK
      REQUIRED_VARS FBXSDK_INCLUDE_DIRS FBXSDK_LIBRARIES
      FOUND_VAR FBXSDK_FOUND
      VERSION_VAR FBXSDK_VERSION)
  endif()
endif() #FBXSDK_DIRS


mark_as_advanced(
  FBXSDK_INCLUDE_DIRS
  FBXSDK_LIBRARY_DIRS
  FBXSDK_LIBRARIES)


#[[
if (FBXSDK_FOUND)
  message(STATUS "FBXSDK_VERSION: ${FBXSDK_VERSION}")

  message(STATUS "FBXSDK_DIRS: ${FBXSDK_DIRS}")

  message(STATUS "FBXSDK_INCLUDE_DIRS: ${FBXSDK_INCLUDE_DIRS}")
  message(STATUS "FBXSDK_LIBRARY_DIRS: ${FBXSDK_LIBRARY_DIRS}")
  message(STATUS "FBXSDK_LIBRARIES: ${FBXSDK_LIBRARIES}")

  include_directories(${FBXSDK_INCLUDE_DIRS})

  link_directories(${FBXSDK_LIBRARY_DIRS})
  target_link_libraries(${PROJECT_NAME} ${FBXSDK_LIBRARIES})
endif ()
]]
