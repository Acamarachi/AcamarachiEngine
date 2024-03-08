cmake_minimum_required(VERSION 3.11)
project(AcamarachiEngine VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_executable(AcamarachiEngine ${CMAKE_SOURCE_DIR}/src/main.cpp)