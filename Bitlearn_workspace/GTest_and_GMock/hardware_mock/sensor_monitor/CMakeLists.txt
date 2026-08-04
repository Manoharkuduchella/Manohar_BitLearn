cmake_minimum_required(VERSION 3.16)

project(SensorMonitorTests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)

add_library(sensor_monitor
    src/TemperatureMonitor.cpp
)

target_include_directories(sensor_monitor PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

add_executable(sensor_monitor_tests
    tests/TemperatureSensorTest.cpp
)

target_include_directories(sensor_monitor_tests
    PRIVATE
        ${PROJECT_SOURCE_DIR}/mocks
)

target_link_libraries(sensor_monitor_tests
    PRIVATE
        sensor_monitor
        GTest::gtest
        GTest::gmock
        GTest::gtest_main
        pthread
)