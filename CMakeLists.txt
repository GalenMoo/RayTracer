cmake_minimum_required(VERSION 3.11.3)

set(CMAKE_CXX_STANDARD 17)


file(GLOB SOURCES src/*.cpp)

add_definitions(-std=c++17)
set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")


include_directories(include)

project(raytracer)

add_executable(raytracer ${SOURCES})