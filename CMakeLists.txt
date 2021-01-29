cmake_minimum_required(VERSION 3.17)

project(meta_test CXX C)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME}
    flatpointer.h
    flatfunction.h
    hlist.h
    generic.h
    main.cpp
)

target_compile_features(${PROJECT_NAME}
    PRIVATE cxx_constexpr
)
