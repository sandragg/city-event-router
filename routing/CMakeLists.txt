# Project info

cmake_minimum_required(VERSION 3.15)
project(Routing VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# Emscripten configuration (TODO revise)

if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    set(CMAKE_C_COMPILER "emcc")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/../frontend/shared")
endif ()

add_executable(
    Routing
    main.cpp
    src/draft-1.cpp
    src/distance-matrix/distance-matrix.cpp
    src/route-context/route-context.cpp
    src/timetable/event.cpp
    src/timetable/place.cpp
    src/models/custom-settings.cpp
    src/tracer/tracer-impl.cpp
    src/tree/list-of-siblings/list-of-siblings-impl.cpp
    src/tree/iterators/iterators-impl.cpp)

if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    set_target_properties(routing PROPERTIES LINK_FLAGS
        "-O3 -s WASM=1 -s MODULARIZE=1 -s LINKABLE=1 -s ENVIRONMENT='web' -s EXPORTED_FUNCTIONS=\"['_main', '_foo']\" -s EXTRA_EXPORTED_RUNTIME_METHODS=\"['ccall', 'cwrap']\"")
endif ()


# Installation

configure_file(RoutingConfig.h.in RoutingConfig.h)
target_include_directories(Routing PUBLIC "${PROJECT_BINARY_DIR}")

set(PROJECT_RELEASE_DIR ${PROJECT_SOURCE_DIR}/release)

install(TARGETS Routing
        DESTINATION ${PROJECT_RELEASE_DIR}/bin)

install(FILES "${PROJECT_BINARY_DIR}/RoutingConfig.h"
        DESTINATION ${PROJECT_RELEASE_DIR}/include)


# Documentation

add_subdirectory(docs)
