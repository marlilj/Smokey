# cmake_minimum_required(VERSION 3.0)
# project(write_example)
# add_executable(${PROJECT_NAME} write_example.cpp)
# target_include_directories(${PROJECT_NAME} PUBLIC ../../libcanio/include include)
# target_link_libraries(${PROJECT_NAME} canio)
# target_link_directories(${PROJECT_NAME} PUBLIC ../../libcanio/build/)

set(CMAKE_THREAD_PREFER_PTHREAD ON)
# find_package(Threads REQUIRED)

cmake_minimum_required (VERSION 3.5.1)

project(write_example LANGUAGES CXX)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Link runTests with what we want to test and the GTest and pthread library
add_executable(${PROJECT_NAME}
    write_example.cpp
    ../../libcanio/src/canio.cpp
#    ../../src//smokey_module.cpp
    # smokey_test.cpp
)

target_link_directories(${PROJECT_NAME}
  PUBLIC ../../libcanio/build/
)

target_include_directories(${PROJECT_NAME}
  PUBLIC ../../libcanio/include include
)

target_link_libraries(${PROJECT_NAME}
  # canio
  gtest
  Threads::Threads
)

add_library(caniolib
  SHARED ../../libcanio/src/canio.cpp
)

add_test(NAME write_example_gtest COMMAND ${PROJECT_NAME})