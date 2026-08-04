cmake_minimum_required(VERSION 3.16)

project(GTest_FirmwareTest)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)


add_library(calculator
    src/Calculator.cpp
)

target_include_directories(calculator PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

add_executable(
    firmware_tests
    tests/CalculatorTest.cpp
)

target_link_libraries(
    firmware_tests
    calculator
    GTest::gtest
    GTest::gtest_main
    pthread
)