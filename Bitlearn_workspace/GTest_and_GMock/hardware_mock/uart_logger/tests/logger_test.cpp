#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "logger.hpp"
#include "mock_uart.hpp"

using ::testing::Return;

TEST(LoggerTest, SendSuccess)
{
    MockUart mock;

    EXPECT_CALL(mock, send("hello"))
        .WillOnce(Return(true));

    Logger logger(&mock);

    EXPECT_TRUE(logger.log("hello"));

}

TEST(LoggerTest, SendFailure)
{
    MockUart mock;

    EXPECT_CALL(mock, send("hello"))
        .WillOnce(::testing::Return(false));

    Logger logger(&mock);

    EXPECT_TRUE(logger.log("hello"));

}

TEST(LoggerTest, SendCalledOnce)
{
    MockUart mock;

    EXPECT_CALL(mock, send("hello"))
        .Times(1)
        .WillOnce(::testing::Return(true));

    Logger logger(&mock);

    EXPECT_TRUE(logger.log("hello"));

}