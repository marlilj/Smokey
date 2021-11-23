cmake_minimum_required (VERSION 3.5.1)
add_definitions(-std=c++14)
project( smokey_lab )


add_subdirectory(
  app/emulator)

add_subdirectory(
  app/input_handler)

add_subdirectory(lib/libcanio)

add_subdirectory(lib/libcanencoder)

# Require out-of-source builds

file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/input_handler/CMakeLists.txt" LOC_PATH)
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/emulator/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()
