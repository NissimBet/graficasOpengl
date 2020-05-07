cmake_minimum_required(VERSION 3.16)
project(graficasOpengl)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_VERBOSE_MAKEFILE ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(graficasOpengl main.cpp ${SOURCES})

if (WIN32)
    file(GLOB DLLS ${PROJECT_SOURCE_DIR}/dlls/*.dll)
    foreach(filename ${DLLS})
        get_filename_component( Filename ${filename} NAME)
        message(STATUS "${Filename}-${filename}")
        configure_file(${filename} ${CMAKE_CURRENT_BINARY_DIR}/${Filename} COPYONLY)
    endforeach()

    file(GLOB SHADERS ${PROJECT_SOURCE_DIR}/shaders/*.glsl)
    foreach(filename ${SHADERS})
        get_filename_component( Filename ${filename} NAME)
        message(STATUS "${Filename}-${filename}")
        configure_file(${filename} ${CMAKE_CURRENT_BINARY_DIR}/shaders/${Filename} COPYONLY)
    endforeach()
endif ()

if(WIN32)
    target_link_libraries(graficasOpengl -L${PROJECT_SOURCE_DIR}/libs -lopengl32 -lglu32 -lfreeglut -lglew32 -lopengl32)
else()
    target_link_libraries(graficasOpengl -lopengl32 -lglu32 -lfreeglut -glew32 -lGL)
endif()
