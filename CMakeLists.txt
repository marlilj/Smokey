cmake_minimum_required (VERSION 3.5.1)
add_definitions(-std=c++17)
project( smokey_lab )

add_subdirectory(app)

add_subdirectory(lib)


# Require out-of-source builds

file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/input_handler/CMakeLists.txt" LOC_PATH)
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/emulator/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()