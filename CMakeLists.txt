cmake_minimum_required(VERSION 3.17)

project(omnimorph C CXX)
set(CMAKE_CXX_STANDARD 20)

include(GNUInstallDirs)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/install)

set(${PROJECT_NAME}_CLI_HEADERS
    api/HList.h
    api/Representation.h
    api/Generic.h
    api/predicates/DependentVoid.h
    api/predicates/ExistsMember.h
    api/predicates/ExistsOperator.h
    api/predicates/StdStreamable.h

    src/data/types.h
    src/data/IterationDecision.h
    src/data/String.h
    src/data/StringBuilder.h
    src/data/List.h
    src/data/Utils.h
    src/data/ScopeGuard.h

    src/cpp/FilePosition.h
    src/cpp/FileRange.h
    src/cpp/Lexeme.h
    src/cpp/TokenType.h
    src/cpp/Token.h
    src/cpp/FileUtils.h
    src/cpp/ScannerDriver.h
    src/cpp/CppScanner.h
    src/cpp/Lookahead.h
    src/cpp/Ast.h
    src/cpp/CppParser.h

    src/gg/Omnimorph.h
)

set(${PROJECT_NAME}_CLI_SOURCES
    src/data/String.cpp
    src/data/StringBuilder.cpp
    src/data/List.cpp
    src/data/Utils.cpp

    src/cpp/FilePosition.cpp
    src/cpp/FileRange.cpp
    src/cpp/Lexeme.cpp
    src/cpp/TokenType.cpp
    src/cpp/Token.cpp
    src/cpp/FileUtils.cpp
    src/cpp/ScannerDriver.cpp
    src/cpp/CppScanner.cpp
    src/cpp/Lookahead.cpp
    src/cpp/Ast.cpp
    src/cpp/CppParser.cpp

    src/gg/Omnimorph.cpp
    src/main.cpp
)

add_executable(${PROJECT_NAME}
    ${${PROJECT_NAME}_CLI_HEADERS}
    ${${PROJECT_NAME}_CLI_SOURCES}
)
target_compile_features(${PROJECT_NAME}
    PRIVATE cxx_constexpr
)

INSTALL(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/api/
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${PROJECT_NAME}
    FILES_MATCHING PATTERN "*.h*"
)

set(OMNIMORPH_INSTALL_DIR ${CMAKE_INSTALL_PREFIX})
set(OMNIMORPH_WORKINGDIR ${CMAKE_CURRENT_BINARY_DIR})
set(OMNIMORPH_EXECUTABLE ${OMNIMORPH_WORKINGDIR}/${PROJECT_NAME}.exe)
install(FILES
    ${OMNIMORPH_EXECUTABLE}
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
)

set(COMMON_EXAMPLE_FLAGS "EXCLUDE_FROM_ALL")

add_subdirectory(example/generic-printer ${COMMON_EXAMPLE_FLAGS})
add_subdirectory(example/generic-stdprint ${COMMON_EXAMPLE_FLAGS})
add_subdirectory(example/generic-clear ${COMMON_EXAMPLE_FLAGS})
add_subdirectory(example/generic-json ${COMMON_EXAMPLE_FLAGS})
