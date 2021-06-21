cmake_minimum_required(VERSION 3.11)
project(nori VERSION 0.1.0)

#
message(STATUS "CMAKE_VERSION: ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION}.${CMAKE_TWEAK_VERSION}")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")



#
# include_directories
#

#
include_directories(/usr/local/include)

#
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/deps)

#
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/engine)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/GL/glad)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/GL/os)




#
# deps src
#
set(DEPS_SRC_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/deps)

set(DEPS_SRCS
${DEPS_SRC_DIRS}/tinyxml2/tinyxml2.cpp
${DEPS_SRC_DIRS}/targa/targa.c
${DEPS_SRC_DIRS}/glfw/deps/glad_gl.c
${DEPS_SRC_DIRS}/glfw/deps/glad_vulkan.c
${DEPS_SRC_DIRS}/glfw/deps/glad_vulkan.c

)



#
# src
#
set(SRC_DIR src)

set(SRCS

#osver
${SRC_DIR}/engine/os/getosver_osx.mm

#core
${SRC_DIR}/engine/core/Application.cpp

#ext
${SRC_DIR}/engine/asset/ext/lua.cpp
${SRC_DIR}/engine/asset/ext/fbx.cpp

#gl
${SRC_DIR}/engine/renderer/GL/GL_ext.cpp
${SRC_DIR}/engine/renderer/GL/GL_state.cpp

${SRC_DIR}/engine/ui/picker.cpp

#python
${SRC_DIR}/engine/script/python/Py_Application.cpp
${SRC_DIR}/engine/script/python/Py_GL.cpp
${SRC_DIR}/engine/script/python/Py_ext.cpp
${SRC_DIR}/engine/script/python/Py_component.cpp
${SRC_DIR}/engine/script/python/Py_node.cpp



#src    
${SRC_DIR}/GLFW.cpp    
${SRC_DIR}/main.cpp

)


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
    ${DEPS_SRCS}
    ${SRCS}
    ${ICON}
)



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

message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")

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
# deps
#
set(DEPS_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/deps)


#include(CheckIncludeFile)

# git submodule add --name stb https://github.com/nothings/stb stb
# git submodule add --name tinyxml2 https://github.com/leethomason/tinyxml2 tinyxml2


#
# GLFW
#
#[[
```bash
$ git submodule add --name glfw https://github.com/glfw/glfw deps/glfw

$ mkdir build; cd build; cmake ../; make
```
]]

set(GLFW_NAME glfw)
find_path(
    GLFW_DIRS 
    NAMES ${GLFW_NAME}
    HINTS ${DEPS_DIRS}
    NO_DEFAULT_PATH
)

if (GLFW_DIRS)
    set(GLFW_DIRS ${GLFW_DIRS}/${GLFW_NAME})
    
    set(GLFW_INCLUDE_DIRS ${GLFW_DIRS}/include)
    set(GLFW_DEPS_DIRS ${GLFW_DIRS}/deps)
    set(GLFW_LIBRARY_DIRS ${GLFW_DIRS}/build/src)

    message(STATUS "GLFW_DIRS: ${GLFW_DIRS}")

    message(STATUS "GLFW_INCLUDE_DIRS: ${GLFW_INCLUDE_DIRS}")
    message(STATUS "GLFW_DEPS_DIRS: ${GLFW_DEPS_DIRS}")
    message(STATUS "GLFW_LIBRARY_DIRS: ${GLFW_LIBRARY_DIRS}")    

    find_library(
        GLFW_LIBRARIES
        NAMES libglfw3.a
        HINTS ${GLFW_LIBRARY_DIRS}
        REQUIRED
        NO_DEFAULT_PATH
    )

    if(GLFW_LIBRARIES)
        message(STATUS "GLFW_LIBRARIES: ${GLFW_LIBRARIES}")        

        include_directories(${GLFW_INCLUDE_DIRS})
        include_directories(${GLFW_DEPS_DIRS})

        link_directories(${GLFW_LIBRARY_DIRS})
        target_link_libraries(${PROJECT_NAME} ${GLFW_LIBRARIES})    
    endif() #GLFW_LIBRARIES
endif() #GLFW_DIRS


#
# jsoncpp
# 
#[[
```bash
$ git submodule add --name jsoncpp https://github.com/open-source-parsers/jsoncpp deps/jsoncpp

$ mkdir build; cd build; cmake ../; make
```
]]

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

    message(STATUS "JSONCPP_DIRS: ${JSONCPP_DIRS}")

    message(STATUS "JSONCPP_INCLUDE_DIRS: ${JSONCPP_INCLUDE_DIRS}")
    message(STATUS "JSONCPP_LIBRARY_DIRS: ${JSONCPP_LIBRARY_DIRS}")    

    find_library(
        JSONCPP_LIBRARIES
        NAMES libjsoncpp.a
        HINTS ${JSONCPP_LIBRARY_DIRS}
        REQUIRED
        NO_DEFAULT_PATH
    )

    if(JSONCPP_LIBRARIES)
        message(STATUS "JSONCPP_LIBRARIES: ${JSONCPP_LIBRARIES}")        

        include_directories(${JSONCPP_INCLUDE_DIRS})

        link_directories(${JSONCPP_LIBRARY_DIRS})
        target_link_libraries(${PROJECT_NAME} ${JSONCPP_LIBRARIES})    
    endif() #JSONCPP_LIBRARIES
endif() #JSONCPP_DIRS


#
# freetype
#
#[[
```bash
$ git submodule add --name freetype https://github.com/freetype/freetype deps/freetype
$ mkdir build; cd build; cmake ../; make
```
]]

set(FREETYPE_NAME freetype)
find_path(
    FREETYPE_DIRS 
    NAMES ${FREETYPE_NAME}
    HINTS ${DEPS_DIRS}
    NO_DEFAULT_PATH
)

if (FREETYPE_DIRS)
    set(FREETYPE_DIRS ${FREETYPE_DIRS}/${FREETYPE_NAME})
    
    set(FREETYPE_INCLUDE_DIRS ${FREETYPE_DIRS}/include)
    set(FREETYPE_LIBRARY_DIRS ${FREETYPE_DIRS}/build)

    message(STATUS "FREETYPE_DIRS: ${FREETYPE_DIRS}")

    message(STATUS "FREETYPE_INCLUDE_DIRS: ${FREETYPE_INCLUDE_DIRS}")
    message(STATUS "FREETYPE_LIBRARY_DIRS: ${FREETYPE_LIBRARY_DIRS}")    

    find_library(
        FREETYPE_LIBRARIES
        NAMES libfreetype.a
        HINTS ${FREETYPE_LIBRARY_DIRS}
        REQUIRED
        NO_DEFAULT_PATH
    )

    if(FREETYPE_LIBRARIES)
        message(STATUS "FREETYPE_LIBRARIES: ${FREETYPE_LIBRARIES}")        

        include_directories(${FREETYPE_INCLUDE_DIRS})

        link_directories(${FREETYPE_LIBRARY_DIRS})
        target_link_libraries(${PROJECT_NAME} ${FREETYPE_LIBRARIES})    

    endif() #FREETYPE_LIBRARIES
endif() #FREETYPE_DIRS


#
# libpng
#
#[[
```bash
$ curl -O https://nchc.dl.sourceforge.net/project/libpng/libpng16/1.6.37/libpng-1.6.37.tar.xz
$ mkdir build; cd build; cmake ../; make
```
]]

#[[
set(LIBPNG_NAME libpng-1.6.37)
find_path(
    LIBPNG_DIRS 
    NAMES ${LIBPNG_NAME}
    HINTS ${DEPS_DIRS}
    NO_DEFAULT_PATH
)

if (LIBPNG_DIRS)
    set(LIBPNG_DIRS ${LIBPNG_DIRS}/${LIBPNG_NAME})
    
    set(LIBPNG_INCLUDE_DIRS ${LIBPNG_DIRS})
    set(LIBPNG_LIBRARY_DIRS ${LIBPNG_DIRS}/build)

    message(STATUS "LIBPNG_DIRS: ${LIBPNG_DIRS}")

    message(STATUS "LIBPNG_INCLUDE_DIRS: ${LIBPNG_INCLUDE_DIRS}")
    message(STATUS "LIBPNG_LIBRARY_DIRS: ${LIBPNG_LIBRARY_DIRS}")    

    find_library(
        LIBPNG_LIBRARIES
        NAMES libpng.a
        HINTS ${LIBPNG_LIBRARY_DIRS}
        REQUIRED
        NO_DEFAULT_PATH
    )

    if(LIBPNG_LIBRARIES)
        message(STATUS "LIBPNG_LIBRARIES: ${LIBPNG_LIBRARIES}")        

        include_directories(${LIBPNG_INCLUDE_DIRS})

        link_directories(${LIBPNG_LIBRARY_DIRS})
        target_link_libraries(${PROJECT_NAME} ${LIBPNG_LIBRARIES})    
    endif() #LIBPNG_LIBRARIES
endif() #LIBPNG_DIRS
]]

find_package(PNG REQUIRED)
if (PNG_FOUND)
    message(STATUS "PNG_VERSION: ${PNG_VERSION_STRING}")

    message(STATUS "PNG_INCLUDE_DIRS: ${PNG_INCLUDE_DIRS}")
    message(STATUS "PNG_LIBRARIES: ${PNG_LIBRARIES}")
    message(STATUS "PNG_DEFINITIONS: ${PNG_DEFINITIONS}")

    include_directories(${PNG_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${PNG_LIBRARIES})

    add_definitions(${PNG_DEFINITIONS})
endif ()


#
# zlib
#
#[[
```bash
$ curl -O https://nchc.dl.sourceforge.net/project/libpng/zlib/1.2.11/zlib-1.2.11.tar.xz
$ mkdir build; cd build; cmake ../; make
```
]]

#[[
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

    message(STATUS "ZLIB_DIRS: ${ZLIB_DIRS}")

    message(STATUS "ZLIB_INCLUDE_DIRS: ${ZLIB_INCLUDE_DIRS}")
    message(STATUS "ZLIB_LIBRARY_DIRS: ${ZLIB_LIBRARY_DIRS}")    

    find_library(
        ZLIB_LIBRARIES
        NAMES libz.a
        HINTS ${ZLIB_LIBRARY_DIRS}
        REQUIRED
        NO_DEFAULT_PATH
    )

    if(ZLIB_LIBRARIES)
        message(STATUS "ZLIB_LIBRARIES: ${ZLIB_LIBRARIES}")        

        include_directories(${ZLIB_INCLUDE_DIRS})

        link_directories(${ZLIB_LIBRARY_DIRS})
        target_link_libraries(${PROJECT_NAME} ${ZLIB_LIBRARIES})    
    endif() #ZLIB_LIBRARIES
endif() #ZLIB_DIRS
]]

find_package(ZLIB REQUIRED)
if (ZLIB_FOUND)
    message(STATUS "ZLIB_VERSION: ${ZLIB_VERSION_STRING}")

    message(STATUS "ZLIB_INCLUDE_DIRS: ${ZLIB_INCLUDE_DIRS}")
    message(STATUS "ZLIB_LIBRARIES: ${ZLIB_LIBRARIES}")

    include_directories(${ZLIB_INCLUDE_DIRS})

    target_link_libraries(${PROJECT_NAME} ${ZLIB_LIBRARIES})
    
endif ()


#
# BZip2
#
#[[
```bash
$ git submodule add --name bzip2 git://sourceware.org/git/bzip2.git deps/bzip2
# or 
$ curl -O https://www.sourceware.org/pub/bzip2/bzip2-latest.tar.gz

# mkdir build; cd build; cmake ../
```
]]

find_package(BZip2 REQUIRED)
if (BZIP2_FOUND)
    message(STATUS "BZIP2_VERSION: ${BZIP2_VERSION_STRING}")

    message(STATUS "BZIP2_INCLUDE_DIR: ${BZIP2_INCLUDE_DIR}")
    message(STATUS "BZIP2_LIBRARIES: ${BZIP2_LIBRARIES}")

    include_directories(${BZIP2_INCLUDE_DIR}) # not BZIP2_INCLUDE_DIRS    
    target_link_libraries(${PROJECT_NAME} ${BZIP2_LIBRARIES})

endif ()



#
# fbxsdk
# https://www.autodesk.com/developer-network/platform-technologies/fbx-sdk-2020-2
#
#[[
```bash
$ curl -O https://www.autodesk.com/content/dam/autodesk/www/adn/fbx/2020-2/fbx20202_fbxsdk_clang_mac.pkg.tgz
```bash
]]

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

    message(STATUS "FBXSDK_DIRS: ${FBXSDK_DIRS}")

    message(STATUS "FBXSDK_INCLUDE_DIRS: ${FBXSDK_INCLUDE_DIRS}")
    message(STATUS "FBXSDK_LIBRARY_DIRS: ${FBXSDK_LIBRARY_DIRS}")    

    find_library(
        FBXSDK_LIBRARIES
        NAMES libfbxsdk.a
        HINTS ${FBXSDK_LIBRARY_DIRS}
        REQUIRED
        NO_DEFAULT_PATH
    )

    if(FBXSDK_LIBRARIES)
        message(STATUS "FBXSDK_LIBRARIES: ${FBXSDK_LIBRARIES}")        

        include_directories(${FBXSDK_INCLUDE_DIRS})

        link_directories(${FBXSDK_LIBRARY_DIRS})
        target_link_libraries(${PROJECT_NAME} ${FBXSDK_LIBRARIES})    
    endif() #FBXSDK_LIBRARIES
endif() #FBXSDK_DIRS


#
# lua
#
#[[
```bash
$ git submodule add --name lua https://github.com/lua/lua deps/lua

$ make a
```
]]

#set(LUA_NAME lua-5.4.1)
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

    message(STATUS "LUA_DIRS: ${LUA_DIRS}")

    message(STATUS "LUA_INCLUDE_DIRS: ${LUA_INCLUDE_DIRS}")
    message(STATUS "LUA_LIBRARY_DIRS: ${LUA_LIBRARY_DIRS}")    

    find_library(
        LUA_LIBRARIES
        NAMES liblua.a
        HINTS ${LUA_LIBRARY_DIRS}
        REQUIRED
        NO_DEFAULT_PATH
    )

    if(LUA_LIBRARIES)
        message(STATUS "LUA_LIBRARIES: ${LUA_LIBRARIES}")        

        include_directories(${LUA_INCLUDE_DIRS})

        link_directories(${LUA_LIBRARY_DIRS})
        target_link_libraries(${PROJECT_NAME} ${LUA_LIBRARIES})    
    endif() #LUA_LIBRARIES
endif() #LUA_DIRS


#
# PYTHON
#
find_package(Python REQUIRED COMPONENTS Interpreter Development)
if (Python_FOUND)
    message(STATUS "Python_VERSION: ${Python_VERSION}")

    message(STATUS "Python_INCLUDE_DIRS: ${Python_INCLUDE_DIRS}")
    message(STATUS "Python_LIBRARY_DIRS: ${Python_LIBRARY_DIRS}")
    #message(STATUS "Python_RUNTIME_LIBRARY_DIRS: ${Python_RUNTIME_LIBRARY_DIRS}")
    message(STATUS "Python_LIBRARIES: ${Python_LIBRARIES}")

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
#[[
```bash
$ git submodule add --name glew https://github.com/nigels-com/glew deps/glew

$ make extensions
$ make
```
]]

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

    message(STATUS "GLEW_DIRS: ${GLEW_DIRS}")

    message(STATUS "GLEW_INCLUDE_DIRS: ${GLEW_INCLUDE_DIRS}")
    message(STATUS "GLEW_LIBRARY_DIRS: ${GLEW_LIBRARY_DIRS}")    

    find_library(
        GLEW_LIBRARIES
        NAMES libGLEW.a
        HINTS ${GLEW_LIBRARY_DIRS}
        REQUIRED
        NO_DEFAULT_PATH
    )

    if(GLEW_LIBRARIES)
        message(STATUS "GLEW_LIBRARIES: ${GLEW_LIBRARIES}")        

        include_directories(${GLEW_INCLUDE_DIRS})

        link_directories(${GLEW_LIBRARY_DIRS})
        target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES})    
    endif() #GLEW_LIBRARIES
endif() #GLEW_DIRS



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

