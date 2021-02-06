  
cmake_minimum_required(VERSION 3.17)

project(omnimorph C CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME}
    main.cpp
)

target_compile_features(${PROJECT_NAME}
    PRIVATE cxx_constexpr
)
