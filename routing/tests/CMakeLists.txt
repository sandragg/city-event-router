set(Catch2_DIR ${CMAKE_MODULE_PATH}/lib/cmake/Catch2)

find_package(Catch2)

if (Catch2_FOUND)
    file(GLOB_RECURSE TEST_SOURCE_FILES "../src/*.test.cpp")
    add_executable(
        Routing_tests
        test_main.cpp
        ${TEST_SOURCE_FILES})
    target_link_libraries(Routing_tests Catch2::Catch2)

    include(CTest)
    include(Catch)
    catch_discover_tests(Routing_tests)
endif ()
