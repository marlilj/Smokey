cmake_minimum_required(VERSION 3.5.1)
project(canio)
add_library(${PROJECT_NAME} STATIC include/canio.hpp src/canio.cpp)