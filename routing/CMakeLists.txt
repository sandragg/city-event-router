cmake_minimum_required(VERSION 3.14)
project(routing)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        routing main.cpp
        distance-matrix/distance-matrix.h distance-matrix/distance-matrix.cpp
        timetable/timetable.h
        timetable/event.h timetable/event.cpp
        timetable/place.h timetable/place.cpp)