cmake_minimum_required(VERSION 3.20)
project(MaxwellFEM)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(region)
add_subdirectory(elements)
add_subdirectory(basics)
add_subdirectory(mesh)