cmake_minimum_required(VERSION 3.5.1)
project(smokey_lab LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)

add_definitions(-std=c++14)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Link runTests with what we want to test and the GTest and pthread library
add_executable(${PROJECT_NAME}
    input_handler/src/input_handler.cpp
    # input_handler/src/mock_key_input.cpp
    input_handler/src/input_handler_get_input.cpp
    can_encoder/src/interface_from_input_handler.cpp
    # can_encoder/src/can_encoder.cpp
    # can_decoder/src/can_decoder.cpp
    # emulator/src/emulator.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC libcanio/include include)
target_link_libraries(${PROJECT_NAME}
  canio
  gtest
  Threads::Threads
  ncurses
)
target_link_directories(${PROJECT_NAME} PUBLIC libcanio/build/)

add_test(NAME smokey_input_handler_gtest COMMAND ${PROJECT_NAME})