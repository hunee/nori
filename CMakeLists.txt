cmake_minimum_required(VERSION 3.11)
project(nori VERSION 0.1.0)

#
message(STATUS "CMAKE_VERSION: ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION}.${CMAKE_TWEAK_VERSION}")
#message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")


# Icon
if (WIN32)
  set(ICON glfw.rc)
elseif (APPLE)
  set(ICON glfw.icns)
endif()


#
# add_executable
#
#add_executable(boing WIN32 MACOSX_BUNDLE boing.c ${ICON} ${GLAD_GL})
add_executable(${PROJECT_NAME}
  WIN32 MACOSX_BUNDLE
  ${ICON}
)


# include_directories
target_include_directories(${PROJECT_NAME} PRIVATE /usr/local/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)


#
add_subdirectory(deps)
add_subdirectory(src)



#
# CMAKE_CXX_STANDARD
#[[
set(CMAKE_CXX_STANDARD 20 CACHE STRING "C++ standard version to use (default is 11)")

message(STATUS "Require C++${CMAKE_CXX_STANDARD}")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
]]

#
# CMAKE_BUILD_TYPE
#
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message(STATUS "CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}")

#
# CMAKE_CXX_FLAGS
#
if(MSVC)
  #message(STATUS "MSVC")

elseif(${CMAKE_CXX_COMPILER_ID} MATCHES AppleClang)
  #message(STATUS "AppleClang")

  #USE_STB or USE_FT2
  #USE_GLEW or USE_GLAD

  # -DUSE_GLFW
  set(CMAKE_CXX_FLAGS "-std=c++2a -DUSE_GLFW")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -O0 -g -DDEBUG")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2")
  set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS} -Os")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS} -Og -g")

elseif(${CMAKE_CXX_COMPILER_ID} MATCHES GNU)
  #message(STATUS "GNU")
  #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++2a")

else()
  message(STATUS "OTHER")

endif()


# CMAKE_CXX_FLAGS
if (${CMAKE_BUILD_TYPE} MATCHES Debug)
  message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS_DEBUG}")
elseif (${CMAKE_BUILD_TYPE} MATCHES Release)
  message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS_RELEASE}")
elseif (${CMAKE_BUILD_TYPE} MATCHES MinSizeRel)
  message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS_MINSIZEREL}")
elseif (${CMAKE_BUILD_TYPE} MATCHES RelWithDebInfo)
  message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
else()
  message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
endif()


#
# target_link_libraries
#
target_link_libraries(${PROJECT_NAME} stdc++)


# MacOS
if (APPLE)
  target_link_libraries(${PROJECT_NAME} objc)
  target_link_libraries(${PROJECT_NAME} "-framework Foundation" "-framework Cocoa" "-framework IOKit" "-framework OpenGL")
endif()

#target_link_libraries(program "-framework your_frame_work_name")
#set_target_properties(program PROPERTIES LINK_FLAGS "-Wl,-F/Library/Frameworks")


#
# Find dependencies
#

include(CheckIncludeFile)

# Add local cmake modules
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/builds/cmake)

#message(STATUS "PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")


set(DEPS_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/deps)

# git submodule add --name stb https://github.com/nothings/stb stb
# git submodule add --name tinyxml2 https://github.com/leethomason/tinyxml2 tinyxml2

#
# GLFW
#
# $ git submodule add --name glfw https://github.com/glfw/glfw deps/glfw
# $ mkdir build; cd build; cmake ../; make

find_package(GLFW REQUIRED)
if(GLFW_FOUND)
  include_directories(${GLFW_INCLUDE_DIRS})
  include_directories(${GLFW_DEPS_DIRS})

  link_directories(${GLFW_LIBRARY_DIRS})
  target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARIES})

  target_sources(${PROJECT_NAME} PRIVATE ${GLFW_DEPS_DIRS}/glad_gl.c ${GLFW_DEPS_DIRS}/glad_vulkan.c)
endif()


#
# jsoncpp
#
# $ git submodule add --name jsoncpp https://github.com/open-source-parsers/jsoncpp deps/jsoncpp
# $ mkdir build; cd build; cmake ../; make

find_package(JSONCPP REQUIRED)
if(JSONCPP_FOUND)
  include_directories(${JSONCPP_INCLUDE_DIRS})

  link_directories(${JSONCPP_LIBRARY_DIRS})
  target_link_libraries(${PROJECT_NAME} ${JSONCPP_LIBRARIES})
endif()


#
# freetype
#
# $ git submodule add --name freetype https://github.com/freetype/freetype deps/freetype
# $ mkdir build; cd build; cmake ../; make

find_package(FT2 REQUIRED)
if (FT2_FOUND)
  include_directories(${FT2_INCLUDE_DIRS})
  link_directories(${FT2_LIBRARY_DIRS})

  target_link_libraries(${PROJECT_NAME} ${FT2_LIBRARIES})
endif ()



#
# libpng
#
# $ curl -O https://nchc.dl.sourceforge.net/project/libpng/libpng16/1.6.37/libpng-1.6.37.tar.xz
# $ mkdir build; cd build; cmake ../; make

find_package(PNG REQUIRED)
if (PNG_FOUND)
  #message(STATUS "PNG_VERSION: ${PNG_VERSION_STRING}")

  #message(STATUS "PNG_INCLUDE_DIRS: ${PNG_INCLUDE_DIRS}")
  #message(STATUS "PNG_LIBRARIES: ${PNG_LIBRARIES}")
  #message(STATUS "PNG_DEFINITIONS: ${PNG_DEFINITIONS}")

  include_directories(${PNG_INCLUDE_DIRS})
  target_link_libraries(${PROJECT_NAME} ${PNG_LIBRARIES})

  add_definitions(${PNG_DEFINITIONS})
endif ()


#
# zlib
#
# $ curl -O https://nchc.dl.sourceforge.net/project/libpng/zlib/1.2.11/zlib-1.2.11.tar.xz
# $ mkdir build; cd build; cmake ../; make

find_package(ZLIB REQUIRED)
if (ZLIB_FOUND)
  #message(STATUS "ZLIB_VERSION: ${ZLIB_VERSION_STRING}")

  #message(STATUS "ZLIB_INCLUDE_DIRS: ${ZLIB_INCLUDE_DIRS}")
  #message(STATUS "ZLIB_LIBRARIES: ${ZLIB_LIBRARIES}")

  include_directories(${ZLIB_INCLUDE_DIRS})
  target_link_libraries(${PROJECT_NAME} ${ZLIB_LIBRARIES})
endif ()


#
# BZip2
#
# $ git submodule add --name bzip2 git://sourceware.org/git/bzip2.git deps/bzip2
# or
# $ curl -O https://www.sourceware.org/pub/bzip2/bzip2-latest.tar.gz
#
# mkdir build; cd build; cmake ../

find_package(BZip2 REQUIRED)
if (BZIP2_FOUND)
  #message(STATUS "BZIP2_VERSION: ${BZIP2_VERSION_STRING}")

  #message(STATUS "BZIP2_INCLUDE_DIR: ${BZIP2_INCLUDE_DIR}")
  #message(STATUS "BZIP2_LIBRARIES: ${BZIP2_LIBRARIES}")

  include_directories(${BZIP2_INCLUDE_DIR}) # not BZIP2_INCLUDE_DIRS
  target_link_libraries(${PROJECT_NAME} ${BZIP2_LIBRARIES})

endif ()



#
# fbxsdk
# https://www.autodesk.com/developer-network/platform-technologies/fbx-sdk-2020-2
#
# $ curl -O https://www.autodesk.com/content/dam/autodesk/www/adn/fbx/2020-2/fbx20202_fbxsdk_clang_mac.pkg.tgz

find_package(FBXSDK REQUIRED)
if (FBXSDK_FOUND)
  include_directories(${FBXSDK_INCLUDE_DIRS})

  link_directories(${FBXSDK_LIBRARY_DIRS})
  target_link_libraries(${PROJECT_NAME} ${FBXSDK_LIBRARIES})
endif ()



#
# lua
#
# $ git submodule add --name lua https://github.com/lua/lua deps/lua
# $ make a

find_package(LUA REQUIRED)
if (LUA_FOUND)
  include_directories(${LUA_INCLUDE_DIRS})

  link_directories(${LUA_LIBRARY_DIRS})
  target_link_libraries(${PROJECT_NAME} ${LUA_LIBRARIES})
endif ()



#
# PYTHON
#
find_package(Python REQUIRED COMPONENTS Interpreter Development)
if (Python_FOUND)
  #message(STATUS "Python_VERSION: ${Python_VERSION}")

  #message(STATUS "Python_INCLUDE_DIRS: ${Python_INCLUDE_DIRS}")
  #message(STATUS "Python_LIBRARY_DIRS: ${Python_LIBRARY_DIRS}")
  #message(STATUS "Python_RUNTIME_LIBRARY_DIRS: ${Python_RUNTIME_LIBRARY_DIRS}")
  #message(STATUS "Python_LIBRARIES: ${Python_LIBRARIES}")

  include_directories(${Python_INCLUDE_DIRS})
  link_directories(${Python_LIBRARY_DIRS})

  target_link_libraries(${PROJECT_NAME} ${Python_LIBRARIES})
endif()



#[[
#
#
# ASIO STANDALONE
# https://think-async.com/Asio/
#
#
find_path(Asio_INCLUDE_DIRS
    asio
)

if(Asio_INCLUDE_DIRS)
    message(STATUS "Asio_INCLUDE_DIRS: ${Asio_INCLUDE_DIRS}")

    include_directories(${Asio_INCLUDE_DIRS})

    add_definitions(-DASIO_STANDALONE)
endif()
]]


#[[
#
# BOOST
# https://www.boost.org
#
#
set(Boost_USE_STATIC_LIBS       ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS        OFF) # ignore debug libs and
set(Boost_USE_RELEASE_LIBS      ON)  # only find release libs
set(Boost_USE_MULTITHREADED     ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

find_package(Boost REQUIRED COMPONENTS atomic chrono regex date_time system filesystem thread graph program_options)
if(Boost_FOUND)
  message(STATUS "Boost_VERSION: ${Boost_VERSION}")

  message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
  message(STATUS "Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}")
  message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")

  include_directories(${Boost_INCLUDE_DIRS})
  link_directories(${Boost_LIBRARY_DIRS})

  add_definitions(${Boost_DEFINITIONS})
  #add_definitions( -DBOOST_ALL_NO_LIB )
  add_definitions(${Boost_LIB_DIAGNOSTIC_DEFINITIONS})

  add_definitions(-DBoost_ASIO_STANDALONE)
  add_definitions(-DBOOST_ASIO_NO_DEPRECATED)

  target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} pthread)

endif()
]]


#
# GLEW
#
# $ git submodule add --name glew https://github.com/nigels-com/glew deps/glew
# $ make extensions
# $ make

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
  include_directories(${GLEW_INCLUDE_DIRS})

  link_directories(${GLEW_LIBRARY_DIRS})
  target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES})
endif ()



#
# COPY
#
#
set(COPY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Resources")
set(DESTINATION_DIR "${CMAKE_CURRENT_SOURCE_DIR}/build/${PROJECT_NAME}.app/Contents/Resources")

message(STATUS "\n-- COPY ${COPY_DIR} -> ${DESTINATION_DIR}")
file(COPY ${COPY_DIR}/
    DESTINATION ${DESTINATION_DIR}/
)

