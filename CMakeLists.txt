cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)

project(RC)

find_package(Eigen3 3.3 REQUIRED)

add_executable(${PROJECT_NAME} rotation_cube.cc)
add_executable(${PROJECT_NAME}_DONUT rotation_donut.cc)

add_executable(${PROJECT_NAME}_EIGEN rotation_cube_eigen.cc)
target_link_libraries(${PROJECT_NAME}_EIGEN Eigen3::Eigen)