set(CMAKE_THREAD_PREFER_PTHREAD ON)
# find_package(Threads REQUIRED)

cmake_minimum_required (VERSION 3.5.1)

project(smokey_test LANGUAGES CXX)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Link runTests with what we want to test and the GTest and pthread library
add_executable(${PROJECT_NAME}
    main_test.cpp
#    ../../src//smokey_module.cpp
    smokey_test.cpp
)

target_link_libraries(${PROJECT_NAME}
  gtest
  Threads::Threads
)

add_test(NAME smokey_gtest COMMAND ${PROJECT_NAME})