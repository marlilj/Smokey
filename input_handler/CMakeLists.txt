set(CMAKE_THREAD_PREFER_PTHREAD ON)
# find_package(Threads REQUIRED)

cmake_minimum_required (VERSION 3.5.1)

project(input_handler LANGUAGES CXX)


add_definitions(-std=c++11)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Link runTests with what we want to test and the GTest and pthread library
add_executable(${PROJECT_NAME}
    src/input_handler.cpp
    src/mock_key_input.cpp
    src/input_handler_get_input.cpp
    ../../can_encoder/src/interface_from_input_handler.cpp
)

target_link_libraries(${PROJECT_NAME}
  gtest
  Threads::Threads
  ncurses
)

add_test(NAME input_handler_gtest COMMAND ${PROJECT_NAME})