cmake_minimum_required(VERSION 3.16)
project(graficasOpengl)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_VERBOSE_MAKEFILE ON)

find_package(SDL2 REQUIRED)
link_directories(${SDL2_LIBRARY_DIRS})
include_directories(${SDL2_INCLUDE_DIR})

find_package(assimp CONFIG REQUIRED)
link_directories(${ASSIMP_LIBRARY_DIRS})
include_directories(${ASSIMP_INCLUDE_DIRS})

find_package(GLEW REQUIRED)
link_directories(${GLEW_LIBRARY_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})

find_package(glm)
include_directories(${GLM_INCLUDE_DIRS})

include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(graficasOpengl main.cpp ${SOURCES})

if (MSVC)
    file(GLOB SHADERS ${PROJECT_SOURCE_DIR}/shaders/*.glsl)
    target_link_libraries(graficasOpengl ${SDL2_LIBRARY} ${GLEW_LIBRARIES} ${ASSIMP_LIBRARIES} opengl32)
    foreach(filename ${SHADERS})
        get_filename_component( Filename ${filename} NAME)
        message(STATUS "${Filename}-${filename}")
        configure_file(${filename} ${CMAKE_CURRENT_BINARY_DIR}/shaders/${Filename} COPYONLY)
    endforeach()
else()
    target_link_libraries(graficasOpengl -lGLEW -lGL -lSDL2 -lassimp)
endif ()

