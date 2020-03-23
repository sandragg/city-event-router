cmake_minimum_required(VERSION 3.15)
project(Routing VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    set(CMAKE_C_COMPILER "emcc")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/../frontend/shared")
endif ()

add_definitions(-std=c++17)

add_executable(
    Routing
    main.cpp
    distance-matrix/distance-matrix.cpp
    route-context/route-context.cpp
    tracer/tracer.cpp
    timetable/event.cpp
    timetable/place.cpp)

if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    set_target_properties(routing PROPERTIES LINK_FLAGS
        "-O3 -s WASM=1 -s MODULARIZE=1 -s LINKABLE=1 -s ENVIRONMENT='web' -s EXPORTED_FUNCTIONS=\"['_main', '_foo']\" -s EXTRA_EXPORTED_RUNTIME_METHODS=\"['ccall', 'cwrap']\"")
endif ()

configure_file(RoutingConfig.h.in RoutingConfig.h)
target_include_directories(Routing PUBLIC "${PROJECT_BINARY_DIR}")
