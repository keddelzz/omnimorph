cmake_minimum_required(VERSION 3.17)

project(meta_test CXX C)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME}
    main.cpp
    hlist.h
        generic.h show.h)

target_compile_features(${PROJECT_NAME}
    PRIVATE cxx_constexpr
)
