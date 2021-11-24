cmake_minimum_required (VERSION 3.5.1)

project(canencoder LANGUAGES CXX)

add_library(${PROJECT_NAME} SHARED src/can_encoder.cpp
    src/interface_from_input_handler.cpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC ../libcanio/include/
  PUBLIC ../../app/input_handler/include/
  PUBLIC .
)

target_link_directories(${PROJECT_NAME}
  PUBLIC ../../lib/libcanio/build/
)

target_link_libraries(${PROJECT_NAME}
  canio
)