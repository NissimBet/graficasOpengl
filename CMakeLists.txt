cmake_minimum_required(VERSION 3.16)
project(graficasOpengl)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_VERBOSE_MAKEFILE ON)
set(SDL2_PATH "${PROJECT_SOURCE_DIR}\\x86_64-w64-mingw32")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

if(WIN32)
    include_directories(${PROJECT_SOURCE_DIR}/glew-2.1.0/include)
else()
    find_package(GLEW REQUIRED)
    include_directories(${GLEW_INCLUDE_DIRS})
endif()

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB SOURCES src/*.cpp)


add_executable(graficasOpengl main.cpp ${SOURCES})
target_link_libraries(graficasOpengl ${SDL2_LIBRARY})

if(WIN32)
    target_link_libraries(graficasOpengl ${PROJECT_SOURCE_DIR}/glew-2.1.0/lib/Release/x64/glew32.lib ${PROJECT_SOURCE_DIR}/glew-2.1.0/lib/Release/x64/glew32.lib Opengl32.lib)
else()
    target_link_libraries(graficasOpengl -lGLEW -lGL)
endif()
