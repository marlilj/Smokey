cmake_minimum_required(VERSION 3.5.1)
project(Smokey LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME}
#${CMAKE_CURRENT_SOURCE_DIR}/src/level.cpp
# ${CMAKE_CURRENT_SOURCE_DIR}/src/import_playingfield.cpp
${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)


target_include_directories(${PROJECT_NAME}
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)
