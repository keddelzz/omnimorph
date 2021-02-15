  
cmake_minimum_required(VERSION 3.17)

project(omnimorph C CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME}
    cpp/FilePosition.cpp
    cpp/FileRange.cpp
    cpp/Lexeme.cpp
    cpp/TokenType.cpp
    cpp/Token.cpp
    cpp/FileUtils.cpp
    cpp/ScannerDriver.cpp
    cpp/CppScanner.cpp
    cpp/CppParser.cpp
    main.cpp
)

target_compile_features(${PROJECT_NAME}
    PRIVATE cxx_constexpr
)
