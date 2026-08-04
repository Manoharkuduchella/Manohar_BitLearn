cmake_minimum_required(VERSION 3.16)

project(UartLoggerTests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)

add_library(logger
    src/logger.cpp
)

target_include_directories(logger PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

add_executable(uart_logger_tests
    tests/logger_test.cpp
)

target_include_directories(uart_logger_tests PRIVATE
    ${PROJECT_SOURCE_DIR}/mocks
)

target_link_libraries(uart_logger_tests PRIVATE
    logger
    GTest::gtest
    GTest::gmock
    GTest::gtest_main
    pthread
)