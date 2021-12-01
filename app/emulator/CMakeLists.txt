set(CMAKE_THREAD_PREFER_PTHREAD ON)
# find_package(Threads REQUIRED)

cmake_minimum_required (VERSION 3.5.1)

project(smokey_emulator LANGUAGES CXX)


add_definitions(-std=c++17)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Link runTests with what we want to test and the GTest and pthread library
add_executable(${PROJECT_NAME}
    main.cpp
    src/emulator.cpp
    src/emulator_data.cpp
)


target_include_directories(${PROJECT_NAME}
  PUBLIC ../../lib/libcanio/include
  PUBLIC ../input_handler/include
  PUBLIC include
  PUBLIC ../../lib/libcanencoder/include
)

target_link_directories(${PROJECT_NAME}
  PUBLIC ../../lib/libcanencoder/build/
  PUBLIC ../../lib/libcanio/build/
)

target_link_libraries(${PROJECT_NAME}
  canencoder
  canio
  gtest
  Threads::Threads
  ncurses
)

add_test(NAME smokey_emulator_gtest COMMAND ${PROJECT_NAME})