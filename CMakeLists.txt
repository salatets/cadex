cmake_minimum_required(VERSION 3.1)

project(Curves VERSION 0.1
               DESCRIPTION "Test project for CADEX"
               LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)

add_executable(test main.cpp curve.h curve.ipp)
