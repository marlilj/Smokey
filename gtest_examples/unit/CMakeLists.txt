set(CMAKE_THREAD_PREFER_PTHREAD ON)
find_package(Threads REQUIRED)

cmake_minimum_required (VERSION 3.5.1)

project(vehicle_modes_provider_test LANGUAGES CXX)

add_executable(${PROJECT_NAME}
    main_test.cpp
    ../../src/interface_handlers/storage_handler.cpp
    storagehandler_test.cpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    ../../include/interface_handlers/
)

target_link_libraries(${PROJECT_NAME}
  vehiclemodesprovider_service_stub
  gtest
  mock_csp_ps
  csp_common
  Threads::Threads
)

add_test(NAME gtest_vehicle_modes_provider_test COMMAND ${PROJECT_NAME})
