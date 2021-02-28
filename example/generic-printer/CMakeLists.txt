project(generic-printer C CXX)

set(CMAKE_CXX_STANDARD 20)

set(${PROJECT_NAME}_Types
    Vec2i.h
)

foreach(file in ${${PROJECT_NAME}_Types})
    if(NOT ${file} STREQUAL "in")
        add_custom_command(
            OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${file}.generic
            COMMAND ${OMNIMORPH_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/${file} ${CMAKE_CURRENT_BINARY_DIR}/${file}.generic
        )
        list(APPEND ${PROJECT_NAME}_Reprs ${CMAKE_CURRENT_BINARY_DIR}/${file}.generic)
    endif()
endforeach()

add_executable(${PROJECT_NAME}
    ${${PROJECT_NAME}_Types}
    ${${PROJECT_NAME}_Reprs}
    main.cpp
)
