cmake_minimum_required(VERSION 3.13)
project(fabricaVehiculos)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")
find_package(Threads)

set(CMAKE_CXX_STANDARD 14)

add_executable(fabricaVehiculos main.cpp)