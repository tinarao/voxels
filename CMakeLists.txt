cmake_minimum_required(VERSION 3.30)
project(untitled1)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled1 main.cpp)
find_package(raylib CONFIG REQUIRED)
target_link_libraries(untitled1 PRIVATE raylib)