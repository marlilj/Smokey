cmake_minimum_required(VERSION 3.0)
project(canio)
add_library(${PROJECT_NAME} SHARED include/canio.hpp src/canio.cpp)