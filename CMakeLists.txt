cmake_minimum_required(VERSION 3.1)

project(Curves VERSION 0.1
               DESCRIPTION "Test project for CADEX"
               LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)

add_executable(test main.cpp)
target_include_directories(test PUBLIC include)

add_library(curve SHARED include/curve.h include/curve.ipp)
set_target_properties(curve PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(test PUBLIC curve) 
