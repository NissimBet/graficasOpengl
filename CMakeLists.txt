cmake_minimum_required(VERSION 3.16)
project(graficasOpengl)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(SDL2_PATH "${PROJECT_SOURCE_DIR}\\x86_64-w64-mingw32")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/glew-2.1.0/include)

add_executable(graficasOpengl main.cpp)
target_link_libraries(graficasOpengl ${SDL2_LIBRARY} ${PROJECT_SOURCE_DIR}/glew-2.1.0/lib/Release/x64/glew32.lib ${PROJECT_SOURCE_DIR}/glew-2.1.0/lib/Release/x64/glew32.lib Opengl32.lib)
