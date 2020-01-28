cmake_minimum_required(VERSION 3.14)
project(routing)

set(CMAKE_CXX_STANDARD 17)

if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    set(CMAKE_C_COMPILER "emcc")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/../frontend/shared")
endif ()

add_definitions(-std=c++17)
include_directories(include)


add_executable(
    routing main.cpp
    distance-matrix/distance-matrix.h distance-matrix/distance-matrix.cpp
    timetable/timetable.h
    timetable/event.h timetable/event.cpp
    timetable/place.h timetable/place.cpp)

if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    set_target_properties(routing PROPERTIES LINK_FLAGS
        "-O3 -s WASM=1 -s MODULARIZE=1 -s LINKABLE=1 -s ENVIRONMENT='web' -s EXPORTED_FUNCTIONS=\"['_main', '_foo']\" -s EXTRA_EXPORTED_RUNTIME_METHODS=\"['ccall', 'cwrap']\"")
endif ()
