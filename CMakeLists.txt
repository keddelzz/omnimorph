cmake_minimum_required(VERSION 3.17)

project(omnimorph C CXX)

set(OMNIMORPH_WORKINGDIR ${CMAKE_CURRENT_BINARY_DIR}/src/)
set(OMNIMORPH_EXECUTABLE ${CMAKE_CURRENT_BINARY_DIR}/src/${PROJECT_NAME}.exe)

add_subdirectory(src)
add_subdirectory(example)
