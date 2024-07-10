cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)

project(RC)

add_executable(${PROJECT_NAME} rotation_cube.cc)
add_executable(${PROJECT_NAME}_DONUT rotation_donut.cc)