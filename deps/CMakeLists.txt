cmake_minimum_required(VERSION 3.11)

#message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")


set(DEPS_SRCS
${CMAKE_CURRENT_SOURCE_DIR}/tinyxml2/tinyxml2.cpp
${CMAKE_CURRENT_SOURCE_DIR}/targa/targa.c
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(${PROJECT_NAME} PRIVATE ${DEPS_SRCS})

