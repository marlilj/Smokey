set(CMAKE_THREAD_PREFER_PTHREAD ON)
# find_package(Threads REQUIRED)

cmake_minimum_required (VERSION 3.5.1)

project(can_encoder LANGUAGES CXX)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Link runTests with what we want to test and the GTest and pthread library
add_executable(${PROJECT_NAME}
    src/CANEncoder.cpp
    src/InterfaceFromInputHandler.cpp
    # ../../input_handler/src/InterfaceToCANEncoder.cpp
)

target_link_libraries(${PROJECT_NAME}
  gtest
  Threads::Threads
)

add_test(NAME can_encoder_gtest COMMAND ${PROJECT_NAME})