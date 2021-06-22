cmake_minimum_required(VERSION 3.11)

#message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")


set(SRCS

#osver
${CMAKE_CURRENT_SOURCE_DIR}/os/getosver_osx.mm

#core
${CMAKE_CURRENT_SOURCE_DIR}/core/Application.cpp

#ext
${CMAKE_CURRENT_SOURCE_DIR}/asset/ext/lua.cpp
${CMAKE_CURRENT_SOURCE_DIR}/asset/ext/fbx.cpp

#gl
${CMAKE_CURRENT_SOURCE_DIR}/renderer/GL/GL_ext.cpp
${CMAKE_CURRENT_SOURCE_DIR}/renderer/GL/GL_state.cpp

${CMAKE_CURRENT_SOURCE_DIR}/ui/picker.cpp

#python
${CMAKE_CURRENT_SOURCE_DIR}/script/python/Py_Application.cpp
${CMAKE_CURRENT_SOURCE_DIR}/script/python/Py_GL.cpp
${CMAKE_CURRENT_SOURCE_DIR}/script/python/Py_ext.cpp
${CMAKE_CURRENT_SOURCE_DIR}/script/python/Py_component.cpp
${CMAKE_CURRENT_SOURCE_DIR}/script/python/Py_node.cpp


#src
${CMAKE_CURRENT_SOURCE_DIR}/GLFW.cpp
${CMAKE_CURRENT_SOURCE_DIR}/main.cpp

)


target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(${PROJECT_NAME} PRIVATE ${SRCS})

