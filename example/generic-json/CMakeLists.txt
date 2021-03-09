project(generic-json C CXX)

set(CMAKE_CXX_STANDARD 20)

set(${PROJECT_NAME}_Types
    ../common/Fid.h
    ../common/Vec2i.h
    ../common/Nested.h
    Individual.h
    Test.h
)

foreach(file in ${${PROJECT_NAME}_Types})
    if(NOT ${file} STREQUAL "in")
        add_custom_command(
            OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${file}.generic
            COMMAND ${OMNIMORPH_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/${file} ${CMAKE_CURRENT_SOURCE_DIR}/${file}.generic
        )
        list(APPEND ${PROJECT_NAME}_Reprs ${CMAKE_CURRENT_SOURCE_DIR}/${file}.generic)
    endif()
endforeach()

add_executable(${PROJECT_NAME}
    ${${PROJECT_NAME}_Types}
    ${${PROJECT_NAME}_Reprs}

    # I dont want to reimplement these!
    ../../src/data/String.cpp
    ../../src/data/StringBuilder.cpp
    ../../src/data/List.cpp

    json/Value.cpp
    json/Array.cpp
    json/Object.cpp
    json/Show.cpp

    main.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE ${OMNIMORPH_INSTALL_DIR}/include
)
