set(CMAKE_THREAD_PREFER_PTHREAD ON)
# find_package(Threads REQUIRED)

cmake_minimum_required (VERSION 3.5.1)

project(smokey_input_handler LANGUAGES CXX)


add_definitions(-std=c++17)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Link runTests with what we want to test and the GTest and pthread library
add_executable(${PROJECT_NAME}
    main.cpp
    src/input_handler_get_input.cpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC ../../lib/libcanencoder/include
  PUBLIC ../../lib/libcanio/include
  PUBLIC include
)

target_link_directories(${PROJECT_NAME}
  PUBLIC ../../lib/libcanio/build/
  PUBLIC ../../lib/libcanencoder/build/
)

target_link_libraries(${PROJECT_NAME}
  canio
  canencoder
  gtest
  Threads::Threads
  ncurses
)

add_test(NAME smokey_input_handler_gtest COMMAND ${PROJECT_NAME})