set(DOXYGEN_EXECUTABLE "${CMAKE_MODULE_PATH}/bin/doxygen")

find_package(Doxygen)

if (Doxygen_FOUND)
    configure_file(Doxyfile.in Doxyfile)
    add_custom_target(doc COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
endif ()
